#include "Timeout.h"

#include "SystemTime.h"


#define TIME_OUT_SENSI_MIL 1

#define TIME_OUT_SENSI_MIC 2



uint32_t timeout_getTimeBySensi(Timeout timeout);

uint32_t timeout_calDeltaBySensi(Timeout timeout);



void timeout_initMillis(Timeout *timeout,uint32_t duration){

	timeout_initMicros(timeout,duration*1000);
	timeout->sensi=TIME_OUT_SENSI_MIC;
}


void timeout_init_micros(Timeout *timeout,uint32_t duration){
	
	timeout->duration=duration;
	timeout->sensi=TIME_OUT_SENSI_MIL;
}
void timeout_start(Timeout *timeout){

	if(timeout->sensi==TIME_OUT_SENSI_MIC)
		timeout->startingTime=time_getMicros();
	else
		timeout->startingTime=time_getMillis();
}

int timeout_isTimeOut(Timeout *timeout){
	
	if(timeout->timeoutFlag)
		return timeout->timeoutFlag;
	
	uint32_t delta=timeout_calDeltaBySensi(*timeout);
	if(delta>timeout->duration)
		timeout->timeoutFlag=1;
	else
		timeout->timeoutFlag=0;
	return timeout->timeoutFlag;
	
}


/*--------------------------------------------------------------------------------*/





uint32_t timeout_getTimeBySensi(Timeout timeout){

	if(timeout.sensi==TIME_OUT_SENSI_MIC)
		return time_getMicros();
	return time_getMillis();
}

uint32_t timeout_calDeltaBySensi(Timeout timeout){
	
	uint32_t currentTime=timeout_getTimeBySensi(timeout);
	return time_calDeltaTimeBySensi(currentTime,timeout.startingTime,
		timeout.sensi==TIME_OUT_SENSI_MIL?TIME_SENSI_MIL:TIME_SENSI_MIC);
	
}