/*
@author:truonglx,tecasoftandtech.
@des: Cai dat cac function cua che do bay co ban.
@link:
1. DroneController.h. Lay thong tin ve dieu khien.
2. Quadcore.h. UpdateQuadCore.
*/
#include "BasicFlyMode.h"
#include "GeneralFly.h"

int basicFlyMode_EnableFlag;

void enableBasicFlyMode(void){
	basicFlyMode_EnableFlag=1;
}

int isEnableBasicFlyMode(void){
	return basicFlyMode_EnableFlag;
}

void updateBasicFlyMode(float *pwms){
		
	Vector3D error;
	if(!isEnableBasicFlyMode())
		enableBasicFlyMode();
	updateControlToQuadCore();
	error=updateDataToQuadCore();
	calculatePwm(getThrottle(),error,pwms);
}

void disableBasicFlyMode(void){
	resetDataQuadcore();
}

