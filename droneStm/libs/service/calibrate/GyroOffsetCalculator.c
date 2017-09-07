#include "GyroOffsetCalculator.h"


void initGyroOffsetCalculator(GyroOffsetCalculator *cal,int numberSample){
	cal->numberSample=numberSample;
	cal->sumPitch=cal->sumRoll=cal->sumYaw=0;
	cal->counter=0;
}




int  addSample(GyroOffsetCalculator *cal,Vector3DInt16_t sample){
	if(cal->counter==cal->numberSample)
		return 1;
	
	
	
	
	cal->sumRoll+=sample.roll;
	cal->sumPitch+=sample.pitch;
	cal->sumYaw+=sample.yaw;
	cal->counter++;

	
	return 0;
}

Vector3DInt16_t getGyroCalculateOffsetResult(GyroOffsetCalculator cal){
	Vector3DInt16_t res;
	res.roll=cal.sumRoll/cal.counter;
	res.pitch=cal.sumPitch/cal.counter;
	res.yaw=cal.sumYaw/cal.counter;
	return res;
}
