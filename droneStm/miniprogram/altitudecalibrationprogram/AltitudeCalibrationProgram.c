#include "AltitudeCalibrationProgram.h"
#include "BarometerMs5611.h"
#include "DroneStore.h"
#define ALT_CALIB_NUMBER_SAMPLE 200



BarometerMs5611 altCalib_Barometer;

void initAltitudeCalibraionProgram(void){
	initBarometerMs5611(&altCalib_Barometer,MS5611_ULTRA_HIGH_RES);
}

float altCalibGetSample(void){
	while(!updateBarometerMs5611(&altCalib_Barometer));
	return getMs5611Altitude(altCalib_Barometer);
}

float startAltitudeCalibrationProgram(void){
	double sum=0;
	for(int i=0;i<ALT_CALIB_NUMBER_SAMPLE;i++)
		sum+=altCalibGetSample();
	sum/=ALT_CALIB_NUMBER_SAMPLE;
	writeAltitudeOffset((float)sum);
	return (float)sum;
}

