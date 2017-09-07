
/*
@author:truonglx,tecasoftandtech
@des: 
1. Danh cho che do bay co ban bao:
+ dieu khien cac goc bang tay.
+ dieu chinh do cao bang tay.
/---------------------quan li version-------------------/
Version(BasicFlyMode.h)=1.

*/
#ifndef BasicFlyMode_h_
#define BasicFlyMode_h_

void 	enableBasicFlyMode(void);
void 	updateBasicFlyMode(float *pwms);
void 	disableBasicFlyMode(void);
int 	isEnableBasicFlyMode(void);
#endif
