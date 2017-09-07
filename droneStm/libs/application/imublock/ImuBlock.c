/*
@author: truonglx
*/


#include "ImuBlock.h"
#include "Mpu9250Reader.h"
#include "ImuCalibrate.h"
#include "DroneStore.h"
#include "MagnetCalibrate.h"
#include "GpsBlock.h"




#define OFFSET_ACCEL_Z 10.325f
#define F_READ_MAGNET 5

Mpu9250Reader    mpuReader;
Vector3D mAccel,mGyro,mMagnet;
ImuCalibrator gyroCalib;
MagnetCalibrator mMagnetCalib;
int convertDataFlag=0;

void initMagnetCalib(void){
	float matrix[3][3];
	float bias[3];
	getMagnetOffset(matrix,bias);
	initMagnetCalibrator(&mMagnetCalib,matrix,bias);
}

void initGyroCalib(void){
	int16_t offset[3];
	getGyroOffset(offset);
	Vector3DInt16_t vectorOffset;
	vectorOffset=convertArrayToVector3DInt16(offset);
	initImuCalibrator(&gyroCalib,vectorOffset);
}




void initImuReader(void){
	initMpu9250Reader(&mpuReader);
}


void convertImuData(void){
	static Vector3DInt16_t rawAccel,rawGyro,rawMagnet;
	if(convertDataFlag)
		return ;
	convertDataFlag=1;
	rawAccel=getRawAccel(mpuReader);
	rawGyro=getRawGyro(mpuReader);
	rawMagnet=getRawMagnet(mpuReader);
	mGyro=convertRawGyroToRealGyro(calibrate(gyroCalib,rawGyro));
	mAccel=convertRawAccelToRealAccel(rawAccel);
	mMagnet=convertRawMagnetToRealMagnet(rawMagnet);
	mMagnet=calibMagnetVector(mMagnetCalib,mMagnet);
	
}

/*-------------------------------------------public------------------------------------------------------------------*/

void initImuBlock(void){
	initImuReader();
	initGyroCalib();
}

void resetImuBlock(void){
	initGyroCalib();
}





void updateImuBlock(void){
	readFullDataMpu9250(&mpuReader);
	convertDataFlag=0;
}



Vector3D getGyro(void){
	convertImuData();
	return mGyro;
}

Vector3D getAccel(void){
	convertImuData();
	return mAccel;
}


Vector3D getMagnet(void){
	convertImuData();
	return mMagnet;
}



float 	getRealAccelZ(void){
	return mAccel.yaw-OFFSET_ACCEL_Z;
}


