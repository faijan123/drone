#include "Delay.h"
#include "TcTime.h"

void delayMicros(uint32_t time){
	
	u32 anchor=getCurrentTime();
	while((getCurrentTime()-anchor)<time);
}


void delayMilis(uint32_t time){
	delayMicros(time*1000);
}
