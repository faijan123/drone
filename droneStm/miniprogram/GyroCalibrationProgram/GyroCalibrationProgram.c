#include "GyroCalibrationProgram.h"
#include "GyroOffsetCalculator.h"
#include "Mpu9250Reader.h"
#include "Delay.h"
#include "DroneStore.h"
#define NUMBER_SAMPLE_GYRO 2000

GyroOffsetCalculator gyroPro_cal;
Mpu9250Reader gyroPro_reader;

void initGyroCalibrationProgram(){
	initGyroOffsetCalculator(&gyroPro_cal,NUMBER_SAMPLE_GYRO );
	initMpu9250Reader(&gyroPro_reader);
}

Vector3DInt16_t calGyroOffset(){
	Vector3DInt16_t gyroRaw;
	do{
		delayMilis(3);
		readAccelAndGyroDataMpu9250(&gyroPro_reader);
		gyroRaw=getRawGyro(gyroPro_reader);
	}while(!addSample(&gyroPro_cal,gyroRaw));
	return getGyroCalculateOffsetResult(gyroPro_cal);
}



Vector3DInt16_t gyroOffsetResult;

void startGyroCalibrationProgram(){
	Vector3DInt16_t offset=calGyroOffset();
	gyroOffsetResult=offset;
	int16_t offsetArray[3];
	convertVector3DInt16ToArray(offset,offsetArray);
	writeGyroOffset(offsetArray);
}

Vector3DInt16_t getGyroOffsetResult(){
	return getGyroCalculateOffsetResult(gyroPro_cal);
}
