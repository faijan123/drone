#include "main.h"
#include "Ublox.h"
#include "Printer.h"
#include "BarometerMs5611.h"
#include <math.h>
#include <stdlib.h>
#include "UbxSender.h"
#include "UbloxConfig.h"
#include "Filter.h"
#include "String.h"
#include "UbloxConfig.h"
#include "UbxReceiver.h"






void startCalibrate(void){
	disableController();
	initGyroCalibrationProgram();
	startGyroCalibrationProgram();
	if(isInitAltitudeBlock()){
		initAltitudeCalibraionProgram();
		startAltitudeCalibrationProgram();
	}
	enableController();
}



int checkAndStartCalibrate(){
	if(!isRunCalibrateProgram())
		return 0;
	startCalibrate();
	return 1;
}

void reset(){
	resetController();
	resetImuBlock();
	initDeltaTimeChecker(&timeCheckerMainLoop,FREQUENCE_TO_MICROS(FREQUENCE_UPDATE_MAIN));
}


void setUp(void){
	
	delayMilis(200);
	initDroneController();
	initI2C();
	initImuBlock();
	initEulerBlock();
//	initFlyControlBlock();
	initMotorControlBlock();
	initDeltaTimeChecker(&timeCheckerMainLoop,FREQUENCE_TO_MICROS(FREQUENCE_UPDATE_MAIN));
	delayMilis(200);
	
}


void callFunctionEvadeInterrupt(void){
	disableController();
	updateImuBlock();
	enableController();
}


float t_InteGyro[3]={0,0,0};
float t_MaxGyro[3]={0,0,0};
void testGyroData(){
	
	Vector3D gyroData = getGyro();
	
	t_InteGyro[0]+=gyroData.roll;
	t_InteGyro[1]+=gyroData.pitch;
	t_InteGyro[2]+=gyroData.yaw;
	
	if(fabs(gyroData.roll)>t_MaxGyro[0])
		t_MaxGyro[0] = gyroData.roll;
	
	if(fabs(gyroData.pitch)>t_MaxGyro[1])
		t_MaxGyro[1] = gyroData.pitch;
	
	if(fabs(gyroData.yaw)>t_MaxGyro[2])
		t_MaxGyro[2] = gyroData.yaw;
}

int loop(void){
	
	static float pwms[4];
	while(!checkDeltaTimeChecker(&timeCheckerMainLoop));
//	updateDroneController();
	callFunctionEvadeInterrupt();
	testGyroData();
	if(checkAndStartCalibrate())
		return 0;
	updateEulerBlock();
	updateFlyControlBlock(pwms);	
	updateMotorControlBlock(pwms[0],pwms[1],pwms[2],pwms[3]);
	return 1;
}



int main(void){
	
	
	setUp();
	startCalibrate();
	reset();
	while(1){
		while(loop()){};
	 	reset();
	}
}







