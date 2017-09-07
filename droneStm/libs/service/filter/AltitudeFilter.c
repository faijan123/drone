#include "AltitudeFilter.h"



void initPositionKalmanFilterCompo(AltitudeFilter *filter,AltitudeFilterConfig config){
	PositionKalmanFilterConfig positionKalmanFilterConfig;
	
	positionKalmanFilterConfig.aGain=config.aGain;
	positionKalmanFilterConfig.vGain=config.vGain;
	positionKalmanFilterConfig.dGain=config.dGain;
	
	positionKalmanFilterConfig.aMax=config.aMax;
	positionKalmanFilterConfig.dMax=config.dMax;
	positionKalmanFilterConfig.vMax=config.vMax;
	initPositionKalmanFilter(&filter->kalmanFilter,positionKalmanFilterConfig);
}


void initHightPassFilterCompo(AltitudeFilter *filter,AltitudeFilterConfig config){
	initHightPassFilter(&filter->hightPassFilter,0,config.aThresHold);
}


void initAltitudeFilter(AltitudeFilter *filter,AltitudeFilterConfig config,float aoffset){
	initPositionKalmanFilterCompo(filter,config);
	initHightPassFilterCompo(filter,config);
	filter->aOffset=aoffset;
}
void enableAltitudeFilter(AltitudeFilter *filter,float d0){
	enablePositionKalmanFilter(&filter->kalmanFilter,d0);
	filter->isEnable=1;
}
void disablAltitudeFilter(AltitudeFilter *filter){
	disablePositionKalmanFilter(&filter->kalmanFilter);
	filter->isEnable=0;
}

float updateAltitudeFilter(AltitudeFilter *filter,float accel,float altitude,float dt){
	if(!filter->isEnable)
		return 0;
	accel-=filter->aOffset;
	return updatePositionKalmanFilter(&filter->kalmanFilter,updateHightPassFilter(&filter->hightPassFilter,accel),altitude,dt);
}

