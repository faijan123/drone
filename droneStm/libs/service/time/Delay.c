

#include "Delay.h"

#include "Timeout.h"

void delay_millis(uint32_t millis){
	
	Timeout timeout;
	timeout_initMillis(&timeout,millis);
	timeout_start(&timeout);
	while(!timeout_isTimeOut(&timeout));
	
}

void delay_micros(uint32_t micros){
	
	Timeout timeout;
	timeout_initMicros(&timeout,micros);
	timeout_start(&timeout);
	while(!timeout_isTimeOut(&timeout));
}