#ifndef TimeoutChecker_h_
#define TimeoutChecker_h_

#include "stm32f4xx.h"
typedef struct TimeoutChecker{
	int remainTime;
	u32 prevTime;
}TimeoutChecker;

void resetTimeoutChecker(TimeoutChecker *timeoutchecker);
int updateTimeoutChecker(TimeoutChecker *timeoutchecker);
int isTimeout(TimeoutChecker *timeoutchecker);



#endif