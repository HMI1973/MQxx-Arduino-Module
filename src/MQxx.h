#ifndef MQxx_h
#define MQxx_h

#include "Arduino.h"
#include "MQ_Common.h"

class MQxx{
	private:
	#define         MQxx_RL_VALUE			(1    )	//define the load resistance on the board, in kilo ohms
	#define         MQxx_CLEAN_AIR_FACTOR		(4.434) //RO_CLEAR_AIR_FACTOR = (Sensor resistance in clean air) / RO, which is derived from the chart in datasheet

	unsigned long	m_Cal_Timer;
	int 		m_Cal_Counter;
	float 		m_Cal_PrevVal;
	float           m_Ro;
	float		m_Rs;
	MQ_STATUS	m_Status;//-1 sensor is not available,0 in worm up, 1 in calibration
	int		m_PIN;
	char		m_buffer[110];

	bool 	init		(int PIN	);
	bool	isConnected	(		);
	int	read		(		);
	float	readVs		(		);
	float	readRs		(		);
	float	readRsRo	(		);
	float	readSample	(		);
	void	resetSample	(		);
	void 	refresh		(		);
	int*	getVals		(		);

	public:
		MQxx		(int PIN	);
		~MQxx		(		);
	bool	isReady		(		);
	int	readPPM		(int gas_id	);
	char*	print		(		);
};
#endif
