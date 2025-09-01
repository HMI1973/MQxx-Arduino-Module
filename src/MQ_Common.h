#ifndef GAS_h
#define GAS_h

#define MQ_PREHEAT_TIMER		(5    )	// define how many seconds to test stable reading in the preheat operation before it moves to calibration (when sensor turn on it needs preheat period from 5-10 min to give stable reading)
#define MQ_READ_SAMPLE_INTERVAL		(50   ) // define the time interal(in milisecond) between each samples in 
#define MQ_READ_SAMPLE_TIMES		(10   ) // define how many samples you are going to take in normal operation
#define	MQ_NOT_CONNECTED_VOLTAGE	(4.8  ) // define the voltage that indicate sensor is not connected, if voltage lower than that value then sensor connected
enum MQ_STATUS {MQ_NOTCONNECTED, MQ_PREHEAT, MQ_CALIBRATION, MQ_READY};
enum GAS {GAS_CARBON_DIOXIDE, GAS_CARBON_MONOXIDE, GAS_ALCOHOL, GAS_AMMONIUM, GAS_TOLUENE, GAS_ACETONE, GAS_HYDROGEN, GAS_LPG, GAS_METHANE, GAS_SMOKE, GAS_PROPANE, GAS_BENZENE, GAS_HEXANE, GAS_ETHANOL};

#endif
