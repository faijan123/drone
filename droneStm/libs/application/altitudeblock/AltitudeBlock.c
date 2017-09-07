/*
@author:truonglx,tecasoftandtech.
@des: cai dat function cua altitudeblock
@link:
1. BarometerMs5611.h : Thu vien doc du lieu tu sensor Ms5611
2.

/-------------------------------quan li version--------------------------------------/
Version(AltitudeBlock.h)=1.
Version(AltitudeBlock.c)=1.

Thay doi so voi version truoc: 


*/

#include "AltitudeBlock.h"
#include "BarometerMs5611.h"
#include "AltitudeFilter.h"
#include "ImuBlock.h"
#include "Delay.h"
#include "TcTime.h"
#include "DroneStore.h"


#define ALT_BLOCK_K_FILTER_A_GAIN 0.04f
#define ALT_BLOCK_K_FILTER_P_GAIN 0.09f
#define ALT_BLOCK_K_FILTER_V_GAIN 0.04f

#define ALT_BLOCK_K_FILTER_A_MAX 5.0f
#define ALT_BLOCK_K_FILTER_P_MAX 100.0f
#define ALT_BLOCK_K_FILTER_V_MAX 10.0f
#define ALT_BLOCK_K_FILTER_THR_A 0.2f

#define ALT_BLOCK_A_OFF  10.35f 

BarometerMs5611 altBlock_Ms5611Sensor;
AltitudeFilter altBlock_AltFilter;
float altBlock_altitude;
int altBlock_isInitBlog;



float debugBeforeAlt;
float debugAfterAlt;

float getAltBlockDeltaT(void){
	static u32 timer=0;
	float deltaTime;
	if(!timer){
		timer=getCurrentTime();
		return 0;
	}
	deltaTime=((float)(getCurrentTime()-timer))/1000000.0f;
	timer=getCurrentTime();
	return deltaTime;
}

void initAltitudeFilter_AltBlock(float p0){
	AltitudeFilterConfig config;
	config.aGain=ALT_BLOCK_K_FILTER_A_GAIN;
	config.vGain=ALT_BLOCK_K_FILTER_V_GAIN;
	config.dGain=ALT_BLOCK_K_FILTER_P_GAIN;
	config.aMax=ALT_BLOCK_K_FILTER_A_MAX;
	config.vMax=ALT_BLOCK_K_FILTER_V_MAX;
	config.dMax=ALT_BLOCK_K_FILTER_P_MAX;
	config.aThresHold=ALT_BLOCK_K_FILTER_THR_A;
	initAltitudeFilter(&altBlock_AltFilter,config,ALT_BLOCK_A_OFF);
	enableAltitudeFilter(&altBlock_AltFilter,p0);
}




void updateAltAltFilter(void){
	altBlock_altitude=updateAltitudeFilter(&altBlock_AltFilter,
	getAccel().yaw,
	getMs5611Altitude(altBlock_Ms5611Sensor)-getAltitudeOffset()
	,getAltBlockDeltaT());
	debugBeforeAlt=getMs5611Altitude(altBlock_Ms5611Sensor);
	debugAfterAlt=altBlock_altitude;
}


/*------------------------------------------------------public-------------------------------------------------------------------*/

int isInitAltitudeBlock(){
	return altBlock_isInitBlog;
}

void initAltitudeBlock(void){
	initBarometerMs5611(&altBlock_Ms5611Sensor,MS5611_ULTRA_HIGH_RES);
	initAltitudeFilter_AltBlock(getMs5611Altitude(altBlock_Ms5611Sensor));
	altBlock_isInitBlog=1;
}




void updateAltitudeBlock(void){
	updateBarometerMs5611(&altBlock_Ms5611Sensor);
	updateAltAltFilter();
	
	
}

float getAltitudeFromAltitudeBlock(void){	
	return altBlock_altitude;
}





