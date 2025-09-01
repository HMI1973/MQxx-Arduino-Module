#include "Arduino.h"
#include "MQ2.h"

/////////////////////////////////////////////////////
// Private functions
bool MQ2::init(int PIN){
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
bool MQ2::isConnected(){
	if (readVs() >= MQ_NOT_CONNECTED_VOLTAGE){
		m_Status = MQ_NOTCONNECTED;
		return false;
	}
	return true;
}
//////////////////////////////////
// Native Read Digital PIN Value
int	MQ2::read (){
	return analogRead(m_PIN);
}
//////////////////////////////////
// Native Read Digital PIN Value and convert to voltage
float MQ2::readVs(){
	int raw_adc	= read();
	float VRL	= (float) raw_adc * 5 / 1023;

	return VRL;
}
//////////////////////////////////
// Read Device resistance
float MQ2::readRs(){
	float VRL	= readVs();

	return (float) MQ2_RL_VALUE * ((5 - VRL) / VRL);
}
/////////////////////////////////////////////////////
// Output:  Rs/Ro Ratio
float	MQ2::readRsRo(){
	refresh();
	if(m_Status == MQ_READY)
		return (float) m_Rs / m_Ro;
	return -1;
}
//////////////////////////////////
// read sample data from sensor async 
float MQ2::readSample(){
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
void MQ2::resetSample(){
	m_Cal_PrevVal		 = 0;
	m_Cal_Counter		 = 0;
	m_Cal_Timer		 = millis();
}
//////////////////////////////////
// loop call to update the sensor details/status
void MQ2::refresh(){
	float sample;

	if(!isConnected()) return;
	switch (m_Status){
		case MQ_NOTCONNECTED:					// If conected and status = notconnected then move to preheat
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
					m_Status	= MQ_CALIBRATION;	// Move to calibration
					resetSample();
				}
			}
			break;
		case MQ_CALIBRATION:					// now calculate Ro
			sample = readSample();
			if(sample!=-1){
				m_Ro		 = sample / MQ2_CLEAN_AIR_FACTOR;
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
int*	MQ2::getVals	(){
	static int retVal[8];

	retVal[0] = read();
	retVal[1] = readPPM(GAS_HYDROGEN);
	retVal[2] = readPPM(GAS_LPG);
	retVal[3] = readPPM(GAS_METHANE);
	retVal[4] = readPPM(GAS_CARBON_MONOXIDE);
	retVal[5] = readPPM(GAS_ALCOHOL);
	retVal[6] = readPPM(GAS_SMOKE);
	retVal[7] = readPPM(GAS_PROPANE);

	return retVal;
}

/////////////////////////////////////////////////////
// Public functions
MQ2::MQ2(int PIN){
	init(PIN);
}
MQ2::~MQ2(){
}
/////////////////////////////////////////////////////
// check if sensor status = ready
bool MQ2::isReady(){
	refresh();
	if(m_Status == MQ_READY) return true;
	return false;
}
/////////////////////////////////////////////////////
// Input:   gas_id      - target gas type
// Output:  ppm of the target gas or -1 if not define gas
// Remarks: This function uses different equations representing curves of each gas to calculate the ppm (parts per million) of the target gas.
int MQ2::readPPM(int gas_id)
{ 
	float rs_ro_ratio	= readRsRo();
	float PPM		= -1;

	if ( rs_ro_ratio != -1 ){
		if ( gas_id == GAS_HYDROGEN ) 
			PPM = pow(10,(3.003 - 2.139 * log10(rs_ro_ratio)));
		else if ( gas_id == GAS_LPG ) 
			PPM = pow(10,(2.748 - 2.085 * log10(rs_ro_ratio)));
		else if ( gas_id == GAS_METHANE ) 
			PPM = pow(10,(3.595 - 2.613 * log10(rs_ro_ratio)));
		else if ( gas_id == GAS_CARBON_MONOXIDE ) 
			PPM = pow(10,(4.374 - 2.877 * log10(rs_ro_ratio)));
		else if ( gas_id == GAS_ALCOHOL ) 
			PPM = pow(10,(3.479 - 2.684 * log10(rs_ro_ratio)));
		else if ( gas_id == GAS_SMOKE ) 
			PPM = pow(10,(3.507 - 2.219 * log10(rs_ro_ratio)));
		else if ( gas_id == GAS_PROPANE ) 
			PPM = pow(10,(2.815 - 2.096 * log10(rs_ro_ratio)));
        
		if (PPM > 10000) PPM = 10000;
		if (PPM <     0) PPM =     0;
	}

	return PPM;
}
char*	MQ2::print(){
	int *vals;

	refresh();
	if(m_Status == MQ_NOTCONNECTED)
		sprintf(m_buffer, "MQ2: Not Connected!");	
	if(m_Status == MQ_PREHEAT)
		sprintf(m_buffer, "MQ2: Preheat to get stable readings (%d)....", read ());
	if(m_Status == MQ_CALIBRATION)
		sprintf(m_buffer, "MQ2: Calebration (Reading Ro)....");
	if(m_Status == MQ_READY){
		vals = getVals();
		sprintf(m_buffer, "MQ2: Native= %d, H= %dppm, LPG= %dppm, METHANE= %dppm, CO= %dppm, ALCOHOL= %dppm, SMOKE %dppm, PROPANE= %dppm",vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6],vals[7]);
	}

	return 	m_buffer;
}
