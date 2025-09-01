#include "src/mg811.h"
#include "src/mq135.h"
#include "src/mq8.h"
#include "src/mq7.h"
#include "src/mq6.h"
#include "src/mq5.h"
#include "src/mq4.h"
#include "src/mq3.h"
#include "src/mq2.h"

MQ2 *myMQ;

void setup()
{  
	Serial.begin(9600);
	delay(2000);
	myMQ = new MQ2(A3);
}
void loop()
{
	Serial.println(myMQ->print());
	//delay(100);                                   
}
