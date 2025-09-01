#include "Arduino.h"
#include "MQ4.h"

/////////////////////////////////////////////////////
// Private functions
bool MQ4::init(int PIN){
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
bool MQ4::isConnected(){
	if (readVs() >= MQ_NOT_CONNECTED_VOLTAGE){
		m_Status = MQ_NOTCONNECTED;
		return false;
	}
	return true;
}
//////////////////////////////////
// Read Digital PIN Value
int	MQ4::read (){
	return analogRead(m_PIN);
}
//////////////////////////////////
// Read Digital PIN Value and convert it to Voltage
float MQ4::readVs(){
	int raw_adc	= read();
	float VRL	= (float) raw_adc * 5 / 1023;

	return VRL;
}
//////////////////////////////////
// Read Device resistance
float MQ4::readRs(){
	float VRL	= readVs();

	return (float) MQ4_RL_VALUE * ((5 - VRL) / VRL);
}
/////////////////////////////////////////////////////
// Output:  Rs/Ro Ratio
float	MQ4::readRsRo (){
	refresh();
	if(m_Status == MQ_READY)
		return (float) m_Rs / m_Ro;
	return -1;
}
//////////////////////////////////
// read sample data from sensor async 
float MQ4::readSample(){
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
void MQ4::resetSample(){
	m_Cal_PrevVal		 = 0;
	m_Cal_Counter		 = 0;
	m_Cal_Timer		 = millis();
}
//////////////////////////////////
// loop call to update the sensor details/status
void MQ4::refresh(){
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
				m_Ro		 = sample / MQ4_CLEAN_AIR_FACTOR;
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
int*	MQ4::getVals	(){
	static int retVal[7];

	retVal[0] = read();
	retVal[1] = readPPM(GAS_LPG);
	retVal[2] = readPPM(GAS_METHANE);
	retVal[3] = readPPM(GAS_HYDROGEN);
	retVal[4] = readPPM(GAS_CARBON_MONOXIDE);
	retVal[5] = readPPM(GAS_ALCOHOL);
	retVal[6] = readPPM(GAS_SMOKE);

	return retVal;
}

/////////////////////////////////////////////////////
// Public functions
MQ4::MQ4(int PIN){
	init(PIN);
}
MQ4::~MQ4(){
}
/////////////////////////////////////////////////////
// check if sensor status = ready
bool MQ4::isReady(){
	refresh();
	if(m_Status == MQ_READY) return true;
	return false;
}
/////////////////////////////////////////////////////
// Input:   gas_id      - target gas type
// Output:  ppm of the target gas or -1 if not define gas
// Remarks: This function uses different equations representing curves of each gas to calculate the ppm (parts per million) of the target gas.
int MQ4::readPPM(int gas_id)
{ 
	float rs_ro_ratio	= readRsRo();
	float PPM		= -1;

	if ( rs_ro_ratio != -1 ){
		if ( gas_id == GAS_LPG ) 
			PPM = pow(10,( 3.541 -  3.674 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_METHANE ) 
			PPM = pow(10,( 2.802 -  3.267 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_HYDROGEN ) 
			PPM = pow(10,( 5.692 -  6.336 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_CARBON_MONOXIDE ) 
			PPM = pow(10,(14.725 - 19.804 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_ALCOHOL ) 
			PPM = pow(10,(12.054 - 16.633 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_SMOKE ) 
			PPM = pow(10,( 7.744 -  9.895 * log10(rs_ro_ratio)));
        
		if (PPM > 10000) PPM = 10000;
		if (PPM <     0) PPM =     0;
	}

	return PPM;
}
char*	MQ4::print(){
	int *vals;

	refresh();
	if(m_Status == MQ_NOTCONNECTED)
		sprintf(m_buffer, "MQ4: Not Connected!");	
	if(m_Status == MQ_PREHEAT)
		sprintf(m_buffer, "MQ4: preheat to get stable readings (%d)....", read ());
	if(m_Status == MQ_CALIBRATION)
		sprintf(m_buffer, "MQ4: Calebration (Reading Ro)....");
	if(m_Status == MQ_READY){
		vals = getVals();
		sprintf(m_buffer, "MQ4: Native= %d, LPG= %dppm, METHANE= %dppm, H= %dppm, CO= %dppm, ALCOHOL= %dppm, SMOKE= %dppm",vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	}

	return 	m_buffer;
}
