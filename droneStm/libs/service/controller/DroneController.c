#include "DroneController.h"
#include "SBusReader.h"
#include "Mapper.h"
#include "TcTime.h"
#include "TimeChecker.h"
#include "math.h"
#include "stdio.h"

#define DELTA_CONTROL_ANGLE 2  // delta deg control
#define DELTA_CONTROL_THR   15

#define ON 	1
#define OFF 0
#define MAX_ANGLE 45.0f
#define MIN_THR   1000
#define MAX_THR   2000
#define MIN_ADC_CONTROL 1000
#define MAX_ADC_CONTROL 2000

SBusData 					mSBusData;
DroneControlData 	droneController;
ControlValue 			thr,roll,pitch,yaw;

int onFlag=0;
int runCalibrateProgramFlag=0;



void updateControlAngle(ControlValue *controlValue,uint16_t rawValue){
	float value=mapUint16ToFloat(rawValue,MIN_ADC_CONTROL,MAX_ADC_CONTROL,-MAX_ANGLE,MAX_ANGLE);
	if(fabs(value)<DELTA_CONTROL_ANGLE)
		value=0;
	controlValue->value=value;
	if(fabs(value)>DELTA_CONTROL_ANGLE)
	{
		controlValue->timeReceiveControl=getCurrentTime();
		controlValue->availid=1;
	}
	else if((getCurrentTime()-controlValue->timeReceiveControl)>DELTA_TIME_ACCURACY)
		controlValue->availid=0;
}

void updateThrControl(ControlValue *controlValue,uint16_t rawValue)
{
	float value=mapUint16ToFloat(rawValue,MIN_ADC_CONTROL,MAX_ADC_CONTROL,MIN_THR,MAX_THR);
	if(fabs(controlValue->value-value)>DELTA_CONTROL_THR)
	{
		controlValue->value=value;
		controlValue->timeReceiveControl=getCurrentTime();
		controlValue->availid=1;
	}
	else if((getCurrentTime()-controlValue->timeReceiveControl)>DELTA_TIME_ACCURACY)
		controlValue->availid=0;
}

SBusData debugSBusData;
SBusData mapperSBusDataToSignalTarget(SBusData sBusData)
{
	debugSBusData=sBusData;
	sBusData.channel1=mapUint16ToUint16(sBusData.channel1,330,1670,1000,2000);
	sBusData.channel2=mapUint16ToUint16(sBusData.channel2,1670,330,1000,2000);
	sBusData.channel3=mapUint16ToUint16(sBusData.channel3,1670,330,1000,2000);
	sBusData.channel4=mapUint16ToUint16(sBusData.channel4,330,1670,1000,2000);
	return sBusData;
}




int checkRunGyroCalibrationCondition(SBusData sBusData){
	return sBusData.channel1>1900&&sBusData.channel2>1900&&
					sBusData.channel3>1900&&sBusData.channel4>1900;
}


void checkRunGyroCalibrationProgram(SBusData data){
	static DeltaTimeChecker timeChecker;
	
	if(checkRunGyroCalibrationCondition(data)){
		if(checkTimeAccuracy(&timeChecker,1000000)){
			runCalibrateProgramFlag=1;
			disableDeltaTimeChecker(&timeChecker);
		}
	}
	else if(isEnableDeltaTimeChecker(timeChecker))
			disableDeltaTimeChecker(&timeChecker);
}





void 	initDroneController(void){
	initSBusReader();
}



void updateDroneController(void){
	
	int res;
	res=readDataViaSBus(&mSBusData);
	if(!res)
		return ;
	mSBusData=mapperSBusDataToSignalTarget(mSBusData);
	checkRunGyroCalibrationProgram(mSBusData);
	updateControlAngle(&roll,mSBusData.channel1);
	updateControlAngle(&pitch,mSBusData.channel2);
	updateControlAngle(&yaw,mSBusData.channel4);
	updateThrControl(&thr,mSBusData.channel3);
}





void resetController(){
	onFlag=0;
	runCalibrateProgramFlag=0;
}
int isTurnOnDrone(void){
	return onFlag;
}
int 	isTurnOffDrone(void){
	return !onFlag;
}

ControlValue getControlRollValue(void){
	return roll;
}

ControlValue getControlPitchValue(void){
	return pitch;
}
ControlValue getControlYawValue(void){
	return yaw;
}
ControlValue getControlThrValue(void){
	return thr;
}





float getChannel1Value(){
	return mSBusData.channel1;
}

float getChannel2Value(){
	return mSBusData.channel2;
}

float getChannel3Value(){
	return mSBusData.channel3;
}

float getChannel4Value(){
	return mSBusData.channel4;
}

int 	isRunCalibrateProgram(void){
	return runCalibrateProgramFlag;
}

void enableController(){
	enableSBusReader();
}
void disableController(){
	disableSBusReader();
}
