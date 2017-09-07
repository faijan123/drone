/*
@author:truonglx
@des: cai dat cac function GeneralFly.h

/-------------------------------------quan li version----------------------/
Version(GeneralFly.h)=1.
Version(GeneralFly.c)=1.




*/
#include "GeneralFly.h"
#include "DroneController.h"
#include "Quadcore.h"
#include "EulerBlock.h"
#include "ImuBlock.h"
#include "ArrayUtil.h"
#include "Constraint.h"




Vector3D debug_quadCoreResult;// Khong xoa.Thuong xuyen debug.
void initGenralFly(void){
	initQuadCore();
}
void updateControlToQuadCore(void){
	ControlValue rollControl,pitchControl,yawControl;
	rollControl=getControlRollValue();
	pitchControl=getControlPitchValue();
	yawControl=getControlYawValue();
	if(rollControl.availid)
		changeSetPointRoll(rollControl.value);
	if(pitchControl.availid)
		changeSetPointPitch(pitchControl.value);
	if(yawControl.availid)
		changeSetPointYaw(yawControl.value);
}




Vector3D updateDataToQuadCore(void){
	return debug_quadCoreResult=updateQuadCore(getEuler(),getGyro());
}



void resetDataQuadcore(void){
	resetQuadCore();
}

void calculatePwm(float thr,Vector3D error,float *pwms){
	resetFloatArray(pwms,4,thr);
	pwms[0]+=	 error.roll-error.pitch+error.yaw;
	pwms[1]+=	-error.roll+error.pitch+error.yaw;
	pwms[2]+=	-error.roll-error.pitch-error.yaw;
	pwms[3]+=	 error.roll+error.pitch-error.yaw;
	for(int i=0;i<4;i++)
		pwms[i]=constraintFloatValues(pwms[i],1100,1900);
}

float getThrottle(void){
	return getControlThrValue().value>1100?getControlThrValue().value:1100;
}


