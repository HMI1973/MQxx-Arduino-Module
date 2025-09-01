#include "Arduino.h"
#include "MG811.h"

/////////////////////////////////////////////////////
// Private functions
bool MG811::init(int PIN){
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
bool MG811::isConnected(){
	if (readVs() >= MQ_NOT_CONNECTED_VOLTAGE){
		m_Status = MQ_NOTCONNECTED;
		return false;
	}
	return true;
}
//////////////////////////////////
// Read Digital PIN Value
int	MG811::read (){
	return analogRead(m_PIN);
}
//////////////////////////////////
// Read Digital PIN Value and convert it to Voltage
float MG811::readVs(){
	int raw_adc	= read();
	float VRL	= (float) raw_adc * 5 / 1023;

	return VRL;
}
//////////////////////////////////
// Read Device resistance
float MG811::readRs(){
	float VRL	= readVs();

	return (float) MG811_RL_VALUE * ((5 - VRL) / VRL);
}
/////////////////////////////////////////////////////
// Output:  Rs/Ro Ratio
float	MG811::readRsRo(){
	refresh();
	if(m_Status == MQ_READY)
		return (float) m_Rs / m_Ro;
	return -1;
}
//////////////////////////////////
// read sample data from sensor async 
float MG811::readSample(){
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
void MG811::resetSample(){
	m_Cal_PrevVal		 = 0;
	m_Cal_Counter		 = 0;
	m_Cal_Timer		 = millis();
}
//////////////////////////////////
// loop call to update the sensor details/status
void MG811::refresh(){
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
				m_Ro		 = sample / MG811_CLEAN_AIR_FACTOR;
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
int*	MG811::getVals	(){
	static int retVal[5];

	retVal[0] = read();
	retVal[1] = readPPM(GAS_CARBON_DIOXIDE);
	retVal[2] = readPPM(GAS_ETHANOL);
	retVal[3] = readPPM(GAS_CARBON_MONOXIDE);
	retVal[4] = readPPM(GAS_METHANE);

	return retVal;
}

/////////////////////////////////////////////////////
// Public functions
MG811::MG811(int PIN){
	init(PIN);
}
MG811::~MG811(){
}
/////////////////////////////////////////////////////
// check if sensor status = ready
bool MG811::isReady(){
	refresh();
	if(m_Status == MQ_READY) return true;
	return false;
}
/////////////////////////////////////////////////////
// Input:   gas_id      - target gas type
// Output:  ppm of the target gas or -1 if not define gas
// Remarks: This function uses different equations representing curves of each gas to calculate the ppm (parts per million) of the target gas.
int MG811::readPPM(int gas_id)
{ 
	float rs_ro_ratio	= readRsRo();
	float PPM		= -1;

	if ( rs_ro_ratio != -1 ){
		if ( gas_id == GAS_CARBON_DIOXIDE ) 
			PPM = pow(10,(-5.026 - 15.627 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_ETHANOL ) 
			PPM = pow(10,(-78.595 - 164.888 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_CARBON_MONOXIDE ) 
			PPM = pow(10,(-35.879 - 77.495 * log10(rs_ro_ratio)));
		if ( gas_id == GAS_METHANE ) 
			PPM = pow(10,(-240.914 - 496.974 * log10(rs_ro_ratio)));
        
		if (PPM >10000) PPM = 10000;
		if (PPM <    0) PPM =     0;
	}

	return PPM;
}
char*	MG811::print(){
	int *vals;

	refresh();
	if(m_Status == MQ_NOTCONNECTED)
		sprintf(m_buffer, "MG811: Not Connected!");	
	if(m_Status == MQ_PREHEAT)
		sprintf(m_buffer, "MG811: Preheat to get stable readings (%d)....", read ());
	if(m_Status == MQ_CALIBRATION)
		sprintf(m_buffer, "MG811: Calebration (Reading Ro)....");
	if(m_Status == MQ_READY){
		vals = getVals();
		sprintf(m_buffer, "MG811: Native= %d, CO2= %dppm, ETHANOL= %dppm, CO= %dppm, METHAN= %dppm",vals[0],vals[1],vals[2],vals[3],vals[4]);
	}

	return 	m_buffer;
}
