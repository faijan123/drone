/*
@author: truonglx,tecasoftandtech.
@des: chuyen tiep cac action den cac che do phu hop. 
*/


#include "FlyControlBlock.h"
#include "DroneController.h"
#include "ArrayUtil.h"
#include "Constraint.h"
#include "AnalystControl.h"

#include "BasicFlyMode.h"
#include "HoldAltitudeMode.h"
#include "HoldPositionMode.h"
#include "GeneralFly.h"


QuadState quadState=OFF;
int debug_Action=NOTHING;
float debug_pwm0,debug_pwm1,debug_pwm2,debug_pwm3;


void initFlyControlBlock(void){
	initAnalystControl(&quadState);
	initGenralFly();
	initHoldAltitudeMode();
}

void updateQuadState(FlyAction action){
	
	if(action==TURN_OFF){
		quadState=OFF;
		return ;
	}
	
	if(action==TURN_ON){
		quadState=ON;
		return ;
	}
	
	if(action==START){
		quadState=STARTING;
		return ;
	}
	
	if(action==TAKE_OFF){
		quadState=FLYING;
		return;
	}

	
	if(action==HOLD_ALTITUDE){
		quadState=HOLDING_ALTITUDE;
		return ;
	}
	
	if(action==HOLD_POSITION){
		quadState=HOLDING_POSITION;
		return ;
	}
	
	if(action==HOLD_ALL){
		quadState=HOLDING_ALL;
		return ;
	}
	
}


void disableAllFlyMode(void){
	if(isEnableBasicFlyMode())
		disableBasicFlyMode();
	if(isEnableHoldAltitudeMode())
		disableHoldAltitudeMode();
	if(isEnableHoldPositionMode())
		disableHoldPositionMode();
}



void turnOnHoldAltitudeMode(){
	enableHoldAltitudeMode();
}


void turnOffHoldAltitudeMode(){
	disableHoldAltitudeMode();
}


void holdAltitude(float *pwms){
	if(isEnableHoldPositionMode())
		disableHoldAltitudeMode();
	updateHoldAltitudeMode(pwms);

}

void holdPosition(float *pwms){
	if(isEnableHoldAltitudeMode())
		disableHoldAltitudeMode();
	updateHoldPositionMode(pwms);
}

void holdAll(float *pwms){
	float thr=updateHoldAltitudeModeWithOutPwm();
	updateHoldPositionModeWithThr(thr,pwms);
}

void turnOn(float *pwms){
	resetFloatArray(pwms,4,1100);
	disableAllFlyMode();
}

void turnOff(float *pwms){
	resetFloatArray(pwms,4,1000);
	disableAllFlyMode();
}

void start(float *pwms){
	float thr=getThrottle();
	thr=thr>1100?thr:1100;
	resetFloatArray(pwms,4,thr);
	disableAllFlyMode();
}

void fly(float *pwms){
	updateBasicFlyMode(pwms);
	if(isEnableHoldAltitudeMode())
		disableHoldAltitudeMode();
	if(isEnableHoldPositionMode())
		disableHoldPositionMode();
}



void updateFlyControlBlock(float *pwmOut){
	
	updateQuadState(getFlyAction());
	if(quadState==HOLDING_ALTITUDE||quadState==HOLDING_ALL)
		quadState=FLYING;
	else if(quadState>=FLYING)
		quadState=FLYING;


	if(quadState==OFF)
		turnOff(pwmOut);
	else if(quadState==ON)
		turnOn(pwmOut);
	else if(quadState==STARTING)
		start(pwmOut);
	else if(quadState==FLYING)
		fly(pwmOut);
	else if(quadState==HOLDING_POSITION)
		holdPosition(pwmOut);
	else if(quadState==HOLDING_ALTITUDE)
		holdAltitude(pwmOut);
	else if(quadState==HOLDING_ALL)
		holdAll(pwmOut);
	
	debug_pwm0=pwmOut[0];
	debug_pwm1=pwmOut[1];
	debug_pwm2=pwmOut[2];
	debug_pwm3=pwmOut[3];
}




