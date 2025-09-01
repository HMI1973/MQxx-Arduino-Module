#include "Arduino.h"
#include "MQ5.h"

/////////////////////////////////////////////////////
// Private functions
bool MQ5::init(int PIN){
	m_PIN		= PIN;
	m_Status	= MQ_NOTCONNECTED;
	m_Ro		= -1;
	m_Rs		= -1;
	m_Cal_PrevVal	=  0;
	m_Cal_Counter	=  0;
	pinMode(PIN, INPUT_PULLUP);
	refresh();
	return true;
}
//////////////////////////////////
// Check if device connected by measuring the read voltage, if too high means the device is not connected
bool MQ5::isConnected(){
	if (readVs() >= MQ_NOT_CONNECTED_VOLTAGE){
		m_Status = MQ_NOTCONNECTED;
		return false;
	}
	return true;
}
//////////////////////////////////
// Read Digital PIN Value
int	MQ5::read (){
	return analogRead(m_PIN);
}
//////////////////////////////////
// Read Digital PIN Value and convert it to Voltage
float MQ5::readVs(){
	int raw_adc	= read();
	float VRL	= (float) raw_adc * 5 / 1023;

	return VRL;
}
//////////////////////////////////
// Read Device resistance
float MQ5::readRs(){
	float VRL	= readVs();

	return (float) MQ5_RL_VALUE * ((5 - VRL) / VRL);
}
/////////////////////////////////////////////////////
// Output:  Rs/Ro Ratio
float	MQ5::readRsRo (){
	refresh();
	if(m_Status == MQ_READY)
		return (float) m_Rs / m_Ro;
	return -1;
}
//////////////////////////////////
// read sample data from sensor async 
float MQ5::readSample(){
	if(isConnected()){
		if(millis() - m_Cal_Timer >= MQ_READ_SAMPLE_INTERVAL){
			m_Cal_Timer		 = millis();
			m_Cal_PrevVal		+= readRs();
			m_Cal_Counter		+= 1;
			if(m_Cal_Counter > MQ_READ_SAMPLE_TIMES){
				float retVal	 = (float) m_Cal_PrevVal / MQ_READ_SAMPLE_TIMES;

				resetSample();
				return retVal;
			}
		}
	}
	return (float) -1;
}
//////////////////////////////////
//Reset Sampling data
void MQ5::resetSample(){
	m_Cal_PrevVal		 = 0;
	m_Cal_Counter		 = 0;
	m_Cal_Timer		 = millis();
}
//////////////////////////////////
// loop call to update the sensor details/status
void MQ5::refresh(){
	float sample;

	if(!isConnected()) return;
	switch (m_Status){
		case MQ_NOTCONNECTED:					// If first power up then check voltage reading, if high then the sensor is not connected
			m_Status	= MQ_PREHEAT;
			m_Cal_Timer	= millis();
			m_Cal_PrevVal	= read();
			break;
		case MQ_PREHEAT:					// Async wait for stable reading
			if(abs(read() - m_Cal_PrevVal)>1){
				m_Cal_Timer		= millis();
				m_Cal_PrevVal		= read();
			}else{
				if(millis() - m_Cal_Timer >= 1000 * MQ_PREHEAT_TIMER){
					m_Status	= MQ_CALIBRATION;
					resetSample();
				}
			}
			break;
		case MQ_CALIBRATION:					// now calculate Ro
			sample = readSample();
			if(sample!=-1){
				m_Ro		 = sample / MQ5_CLEAN_AIR_FACTOR;
				m_Status	 = MQ_READY;
			}
			break;
		case MQ_READY:					// default action 
		default:
			sample = readSample();
			if(sample!=-1)
				m_Rs		 = sample;
			break;
	}
}
/////////////////////////////////////////////////////
// Output:  array of 6 integer values represent the whole sensor readings
int*	MQ5::getVals	(){
	static int retVal[6];

	retVal[0] = read();
	retVal[1] = readPPM(GAS_HYDROGEN);
	retVal[2] = readPPM(GAS_LPG);
	retVal[3] = readPPM(GAS_METHANE);
	retVal[4] = readPPM(GAS_CARBON_MONOXIDE);
	retVal[5] = readPPM(GAS_ALCOHOL);

	return retVal;
}

/////////////////////////////////////////////////////
// Public functions
MQ5::MQ5(int PIN){
	init(PIN);
}
MQ5::~MQ5(){
}
/////////////////////////////////////////////////////
// check if sensor status = ready
bool MQ5::isReady(){
	refresh();
	if(m_Status == MQ_READY) return true;
	return false;
}
/////////////////////////////////////////////////////
// Input:   gas_id      - target gas type
// Output:  ppm of the target gas or -1 if not define gas
// Remarks: This function uses different equations representing curves of each gas to calculate the ppm (parts per million) of the target gas.
int MQ5::readPPM(int gas_id)
{ 
	float rs_ro_ratio	= readRsRo();
	float PPM		= -1;

	if ( rs_ro_ratio != -1 ){
		if ( gas_id == GAS_HYDROGEN ) 
			PPM = pow(10,( 3.323 -  3.893 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_LPG ) 
			PPM = pow(10,( 1.900 -  2.595 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_METHANE ) 
			PPM = pow(10,( 2.180 -  2.644 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_CARBON_MONOXIDE ) 
			PPM = pow(10,( 6.393 -  6.991 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_ALCOHOL ) 
			PPM = pow(10,( 4.716 -  4.439 * log10(rs_ro_ratio)));

		if (PPM > 10000) PPM = 10000;
		if (PPM <     0) PPM =     0;
	}

	return PPM;
}
char*	MQ5::print(){
	int *vals;

	refresh();
	if(m_Status == MQ_NOTCONNECTED)
		sprintf(m_buffer, "MQ5: Not Connected!");	
	if(m_Status == MQ_PREHEAT)
		sprintf(m_buffer, "MQ5: Preheat to get stable readings (%d)....", read ());
	if(m_Status == MQ_CALIBRATION)
		sprintf(m_buffer, "MQ5: Calebration (Reading Ro)....");
	if(m_Status == MQ_READY){
		vals = getVals();
		sprintf(m_buffer, "MQ5: Native= %d, H= %dppm, LPG= %dppm, METHANE= %dppm, CO= %dppm, ALCOHOL= %dppm",vals[0],vals[1],vals[2],vals[3],vals[4],vals[5]);
	}

	return 	m_buffer;
}
