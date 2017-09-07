/*
@author: truonglx
@des: Check Time.
*/

#ifndef TimeChecker_h_
#define TimeChecker_h_
#include "stm32f4xx.h"
#include "TimeUtil.h"
typedef struct DeltaTimeChecker
{
	int available;
	uint32_t timer;
	uint32_t deltaTime;
}DeltaTimeChecker;


typedef struct TimeDownCounter{
	uint32_t remain;
	uint32_t prevTime;
	int startFlag;
	
}TimeDownCounter;



int 	checkDeltaTimeChecker(DeltaTimeChecker *checker);
void 	initDeltaTimeChecker(DeltaTimeChecker *checker,uint32_t deltaTime);
void 	resetDeltaTimeChecker(DeltaTimeChecker *checker);
void  disableDeltaTimeChecker(DeltaTimeChecker *checker);
int 	isEnableDeltaTimeChecker(DeltaTimeChecker checker);
int 	getDeltaTimeChecker(DeltaTimeChecker checker);
int 	checkTimeAccuracy(DeltaTimeChecker *timeChecker,uint32_t deltaTime);

void initTimeDownCounter(TimeDownCounter *timeDown,uint32_t time);
int updateAndCheckEndTimeTimeDown(TimeDownCounter *timeDown);
void resetTimeDownCounter(TimeDownCounter *timeDown,u32 time);
void startTimeDownCounter(TimeDownCounter *timeDown);



#endif
