#ifndef AltitudeFilter_h_
#define AltitudeFilter_h_
#include "Filter.h"


typedef struct AltitudeFilterConfig{
	float aGain,vGain,dGain;
	float aThresHold;
	float aMax,vMax,dMax;
}AltitudeFilterConfig;

typedef struct AltitudeFilter{
	PositionKalmanFilter kalmanFilter;
	HightPassFilter hightPassFilter;
	int isEnable;
	float aOffset;
}AltitudeFilter;
	

void initAltitudeFilter(AltitudeFilter *filter,AltitudeFilterConfig config,float aOffset);
void enableAltitudeFilter(AltitudeFilter *filter,float d0);
void disablAltitudeFilter(AltitudeFilter *filter);
float updateAltitudeFilter(AltitudeFilter *filter,float accel,float altitude,float dt);
#endif

