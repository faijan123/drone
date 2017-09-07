/*
author: truonglx
des: proxy for Imu.
*/
#ifndef ImuBlock_h_
#define ImuBlock_h_
#include "Vector3D.h"

void initImuBlock(void);
void updateImuBlock(void);

Vector3D getGyro(void);
Vector3D getAccel(void);
Vector3D getMagnet(void);

float 	getRealAccelZ(void);

void resetImuBlock(void);
#endif

