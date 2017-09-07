#include "EulerBlock.h"
#include "EulerCalculator.h"
#include "TimeChecker.h"
#include "TimeUtil.h"
#include "ImuBlock.h"

#define KP_NORMAL  3.0f
#define KI_NORMAL  0.0f
#define FRE_NORMAL 250.0f

#define ROLL_OFF_SET 1.6f
#define PITCH_OFF_SET 1.5f
EulerCalculator cal;
DeltaTimeChecker imuBlockTimeChecker;
Vector3D mEuler;


void initEulerBlock(void)
{
	initEulerCalculator(&cal,FRE_NORMAL,KP_NORMAL,KI_NORMAL);
	initDeltaTimeChecker(&imuBlockTimeChecker,FREQUENCE_TO_MICROS(FRE_NORMAL));
}


void updateCalculator(void){
	Vector3D accel=getAccel();
	Vector3D gyro=getGyro();
	Vector3D magnet=getMagnet();
	mEuler=updateImuCalculator(&cal,accel,magnet,gyro); 
	mEuler.roll-=ROLL_OFF_SET;
	mEuler.pitch-=PITCH_OFF_SET;
}

Vector3D 	updateEulerBlock(void){
	updateCalculator();
	resetDeltaTimeChecker(&imuBlockTimeChecker);
	return mEuler;
}



Vector3D  getEuler(void){
	return mEuler;
}





