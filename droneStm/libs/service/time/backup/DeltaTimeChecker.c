#include "TimeChecker.h"
#include "TcTime.h"

uint32_t compareWithCurrentTime(uint32_t timer){
	return getCurrentTime()-timer;
}

int checkTimeAccuracy(DeltaTimeChecker *timeChecker,uint32_t deltaTime){
	if(!isEnableDeltaTimeChecker(*timeChecker))
		initDeltaTimeChecker(timeChecker,deltaTime);
	return checkDeltaTimeChecker(timeChecker);
}


void initDeltaTimeChecker(DeltaTimeChecker *checker,uint32_t deltaTime){
	checker->deltaTime=deltaTime;
	resetDeltaTimeChecker(checker);
}


int checkDeltaTimeChecker(DeltaTimeChecker *checker){
	if(!isEnableDeltaTimeChecker(*checker))
		return 0;
	if(compareWithCurrentTime(checker->timer)>checker->deltaTime){
		resetDeltaTimeChecker(checker);
		return 1;
	}
	return 0;
}	


int getDeltaTimeChecker(DeltaTimeChecker checker){
	return compareWithCurrentTime(checker.timer);
}
void resetDeltaTimeChecker(DeltaTimeChecker *checker){
	checker->available=1;
	checker->timer=getCurrentTime();
}
void  disableDeltaTimeChecker(DeltaTimeChecker *checker){
	checker->available=0;
}


int isEnableDeltaTimeChecker(DeltaTimeChecker checker){
	return checker.available;
}

