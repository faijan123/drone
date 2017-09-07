#include "AnalystControl.h"
#include "DroneController.h"
#include "TimeChecker.h"

#define THR_UPDATE_CONTROL 1200
#define THR_HOLD_ALTITUDE  1400
#define THR_HOLD_POSITION  1500

#define THR_TAKE_OFF   		 1200





int   checkHoldPositionControl(void);
int   checkHoldAltitudeControl(void);
int 	checkHoldAllControl(void);
int 	checkTakeOffControl(void);
int 	checkTurnOnControl(void);
int 	checkTurnOffControl(void);
int 	checkStartControl(void);

QuadState *pQuadState;
int debug_QuadOn;
float debug_thr;

int checkTurnOffCondition(float channel1,float channel2,float channel3,float channel4){
	return 	channel1<1100&&channel2<1100&&
					channel3<1100&&channel4<1100;
}

int checkTurnOnCondition(float channel1,float channel2,float channel3,float channel4){
	return 	channel1>1900&&channel2<1100&&
					channel3<1100&&channel4>1900;
}



int isQuadOn(){
	return *pQuadState!=OFF;
}

int isQuadOff(){
	return *pQuadState==OFF;
}

int checkTurnOffControl(){
	
	static DeltaTimeChecker timeChecker;
	if(isQuadOn()&&checkTurnOffCondition(getChannel1Value(),getChannel2Value(),getChannel3Value(),getChannel4Value())){
		if(checkTimeAccuracy(&timeChecker,1000000)){
			disableDeltaTimeChecker(&timeChecker);
			return 1;
		}
	}
	else if(isEnableDeltaTimeChecker(timeChecker))
		disableDeltaTimeChecker(&timeChecker);
	return 0;
}


int checkTurnOnControl(){
	static DeltaTimeChecker timeChecker;
	if(isQuadOff()&&checkTurnOnCondition(getChannel1Value(),getChannel2Value(),getChannel3Value(),getChannel4Value())){
			if(checkTimeAccuracy(&timeChecker,1000000)){
				disableDeltaTimeChecker(&timeChecker);
				return 1;
			}
	}
	else if(isEnableDeltaTimeChecker(timeChecker))
		disableDeltaTimeChecker(&timeChecker);
	return 0;
}




int checkStartControl(){
	debug_QuadOn=isQuadOn();
	debug_thr=getControlThrValue().value;
	return isQuadOn()&&getControlThrValue().value<THR_TAKE_OFF;
}





int  checkHoldPositionControl(void){
	return isQuadOn()&&getControlThrValue().value>THR_HOLD_POSITION&&
		(!getControlRollValue().availid&&getControlRollValue().value==0)&&
		(!getControlPitchValue().availid&&getControlPitchValue().value==0);
}

int  checkHoldAltitudeControl(void){
	return isQuadOn()&&getControlThrValue().value>THR_HOLD_ALTITUDE&&!getControlThrValue().availid;
}


int checkHoldAllControl(void){
	return checkHoldAltitudeControl()&&checkHoldPositionControl();
}


int checkTakeOffControl(void){
	debug_QuadOn=isQuadOn();
	debug_thr=getControlThrValue().value;
	return isQuadOn()&&getControlThrValue().value>THR_TAKE_OFF;
}


void initAnalystControl(QuadState *quadState){
	pQuadState=quadState;
}
FlyAction getFlyAction(){
	if(checkTurnOnControl())
		return TURN_ON;
	if(checkTurnOffControl())
		return TURN_OFF;
	if(checkHoldAllControl())
		return HOLD_ALL;
	if(checkHoldPositionControl())
		return HOLD_POSITION;
	if(checkHoldAltitudeControl())
		return HOLD_ALTITUDE;
	if(checkStartControl())
		return START;
	if(checkTakeOffControl())
		return TAKE_OFF;
	return NOTHING;
}

