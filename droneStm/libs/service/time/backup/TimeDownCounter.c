#include "TimeChecker.h"
#include "TcTime.h"
void initTimeDownCounter(TimeDownCounter *timeDown,uint32_t time){
	timeDown->remain=time;

}
int updateAndCheckEndTimeTimeDown(TimeDownCounter *timeDown){
	if(timeDown->startFlag&&timeDown->remain){
		uint32_t delta=getCurrentTime()-timeDown->prevTime;
		timeDown->remain=timeDown->remain>delta?(timeDown->remain-delta):0;
		timeDown->startFlag=0;
	}
	timeDown->prevTime=getCurrentTime();
	return timeDown->remain==0;
}

void resetTimeDownCounter(TimeDownCounter *timeDown,uint32_t time){
	timeDown->remain=time;
}

void startTimeDownCounter(TimeDownCounter *timeDown){
	timeDown->startFlag=1;
}
