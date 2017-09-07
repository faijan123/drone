#ifndef Mpu9250Reader_h_
#define Mpu9250Reader_h_
#include "Vector3D.h"

typedef struct Mpu9250Data
{
	Vector3DInt16_t 				accelData,gyroData,magnetData;
}Mpu9250Data;


typedef struct Mpu9250Reader
{
	u8 addr;
	u8 magnetAddr;
	Mpu9250Data data;
}Mpu9250Reader;



void initMpu9250Reader(Mpu9250Reader *reader);
void readFullDataMpu9250(Mpu9250Reader *reader);
void readAccelAndGyroDataMpu9250(Mpu9250Reader *reader);
Vector3DInt16_t getRawAccel(Mpu9250Reader reader);
Vector3DInt16_t getRawGyro(Mpu9250Reader 	reader);
Vector3DInt16_t getRawMagnet(Mpu9250Reader reader);
Vector3D convertRawAccelToRealAccel(Vector3DInt16_t rawAccel);
Vector3D convertRawGyroToRealGyro(Vector3DInt16_t rawGyro);
Vector3D convertRawMagnetToRealMagnet(Vector3DInt16_t rawMagnet);
#endif
