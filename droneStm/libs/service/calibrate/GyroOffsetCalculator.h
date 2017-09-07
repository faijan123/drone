#ifndef GyroOffsetCalculator_h_
#define GyroOffsetCalculator_h_
#include "Vector3D.h"

typedef struct GyroOffsetCalculator{
		int numberSample;
		long sumRoll,sumPitch,sumYaw;
		int counter;
}GyroOffsetCalculator;


void initGyroOffsetCalculator(GyroOffsetCalculator *cal,int numberSample);
int  addSample(GyroOffsetCalculator *cal,Vector3DInt16_t sample);
Vector3DInt16_t getGyroCalculateOffsetResult(GyroOffsetCalculator cal);
#endif
