/*
@author: truonglx,tecasoftandtech.
@des: Cai dat cac function cho che do hold altitude.
@link:
1. HoldAltitude.h
+ Giai thuat bay treo do cao
2. DroneController.h
+ Lay muc ga.
3. ImuBlock.h
+ Lay gia toc truc z.

/-------------------quanliversion---------------------/

Version(HoldAltitudeMode.h)=1.
Version(HoldAltitudeMode.c)=1.


*/


#include "HoldAltitude.h"
#include "DroneController.h"
#include "AltitudeBlock.h"
#include "GeneralFly.h"
#include "ImuBlock.h"


int holdAltitude_EnableFlag;


void enableHoldAltitudeMode(void){
	holdAltitude_EnableFlag=1;
	setNewAltitudeSp(getAltitudeFromAltitudeBlock());
}


float calNewThr(void){
	if(!holdAltitude_EnableFlag)
		enableHoldAltitudeMode();
	return getControlThrValue().value+updateHoldAltitude(getRealAccelZ(),getAltitudeFromAltitudeBlock());;
}




void initHoldAltitudeMode(void){
		initHoldAltitude();
}


int isEnableHoldAltitudeMode(void){
	return holdAltitude_EnableFlag;
}



void disableHoldAltitudeMode(void){
	disableHoldAltitude();
	holdAltitude_EnableFlag=0;
}


void updateHoldAltitudeMode(float *pwms){
	updateControlToQuadCore();
	calculatePwm(calNewThr(),updateDataToQuadCore(),pwms);
}


float updateHoldAltitudeModeWithOutPwm(){
	return calNewThr();
}
