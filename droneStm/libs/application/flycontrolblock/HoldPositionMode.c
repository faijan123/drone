#include "GeneralFly.h"
#include "HoldPositionMode.h"

int holdPositionMode_EnableFlag;

void initHoldPositionMode(void){
	
}


void enableHoldPositionMode(void){
	holdPositionMode_EnableFlag=1;
}
int isEnableHoldPositionMode(void){
	return holdPositionMode_EnableFlag;
}
void disableHoldPositionMode(void){
	holdPositionMode_EnableFlag=0;
}

void updateHoldPositionMode(float *pwm){
	updateHoldPositionModeWithThr(getThrottle(),pwm);
}

void updateHoldPositionModeWithThr(float thr,float *pwms){
	Vector3D error;
	error=updateDataToQuadCore();
	calculatePwm(thr,error,pwms);
}


