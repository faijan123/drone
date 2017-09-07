#ifndef TIMEOUT_H_
#define TIMEOUT_H_

#include "stm32f4xx.h"





typedef struct Timeout{
	
	uint32_t startingTime;
	uint32_t duration;
	int 		timeoutFlag;
	int 		sensi;
	
	
}Timeout;


void timeout_initMillis(Timeout *timeout,uint32_t millis);

void timeout_initMicros(Timeout *timeout,uint32_t micros);

void timeout_start(Timeout *timeout);

int timeout_isTimeOut(Timeout *timeout);


#endif
