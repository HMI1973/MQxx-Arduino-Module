#ifndef MQ7_h
#define MQ7_h

#include "Arduino.h"
#include "MQ_Common.h"

class MQ7{
	private:
	#define         MQ7_RL_VALUE			(1    )	//define the load resistance on the board, in kilo ohms
	#define         MQ7_CLEAN_AIR_FACTOR		(26.09) //RO_CLEAR_AIR_FACTOR = (Sensor resistance in clean air) / RO, which is derived from the chart in datasheet

	unsigned long	m_Cal_Timer;
	int 		m_Cal_Counter;
	float 		m_Cal_PrevVal;
	float           m_Ro;
	float		m_Rs;
	MQ_STATUS	m_Status;//-1 sensor is not available,0 in worm up, 1 in calibration
	int		m_PIN;
	char		m_buffer[120];

	bool 	init		(int PIN	);
	int	read		(		);
	bool	isConnected	(		);
	float	readVs		(		);
	float	readRs		(		);
	float	readRsRo	(		);
	float	readSample	(		);
	void	resetSample	(		);
	void 	refresh		(		);
	int*	getVals		(		);

	public:
		MQ7		(int PIN	);
		~MQ7		(		);
	bool	isReady		(		);
	int	readPPM		(int gas_id	);
	char*	print		(		);
};
#endif
