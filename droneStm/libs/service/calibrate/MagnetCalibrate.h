#ifndef MagnetCalibrate_h_
#define MagnetCalibrate_h_
#include "Vector3D.h"


typedef struct MagnetCalibrator{
	float matrix[3][3];
	float bias[3];
}MagnetCalibrator;
void initMagnetCalibrator(MagnetCalibrator *cal,float maxtrix[3][3],float *bias);
void calibMagnet(MagnetCalibrator cal,float *magnetIn,float *magnetOut);
Vector3D calibMagnetVector(MagnetCalibrator cal,Vector3D vectorIn);
#endif
