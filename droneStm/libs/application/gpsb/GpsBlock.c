#include "GpsBlock.h"
#include "GpsFilter.h"
#include "Ublox.h"
#include "EulerBlock.h"
#include "ImuBlock.h"
#include "Uart.h"
#include "TimeUtil.h"
#include "TcTime.h"
#include "Filter.h"
#include <math.h>

#define NUMBER_SAMPLE_START_UBLOX 3
#define FREQUENCE_UPDATE_GPS_BLOCK 10
#define GPS_CHANNEL SERIAL_4
#define GPS_BAUDRATE 9600

//#define GPS_FILTER_A_GAIN 5
//#define GPS_FILTER_V_GAIN 5
//#define GPS_FILTER_G_GAIN 1
//#define GPS_FILTER_A_MAX 	1000.0
//#define GPS_FILTER_V_MAX  1000.0

#define GPS_NUM_SAMPLE_FILTER 20



#define GPS_CONF_BDRATE 9600
#define GPS_CONF_MEASURE_RATE 100



typedef struct _GpsFilter{
	AveFilter filterLon,filterLat;
}_GpsFilter;

//GpsFilter mGpsBlock_GpsFilter;
_GpsFilter mGpsBlock_GpsFilter;

Ublox mGpslock_Ublox;
int mGpsBlock_EnableFlag,mGpsBlock_startedFlag;



float getGpsBlockDeltaT(void){
	static u32 timer=0;
	static u32 deltaT;
	
	if(timer==0)
		timer=getCurrentTime();
	deltaT=getCurrentTime()-timer;
	timer=getCurrentTime();
	return ((float)deltaT)*0.000001f;
}


int checkAndStartedBlock(void){
	
	
	static int counterSample=0;
	NaviPosition pos;

	if(mGpsBlock_startedFlag)
		return 1;
	if(!updateUblox(&mGpslock_Ublox))
		return 0;
	pos=getPositionViaUblox(mGpslock_Ublox);
	if(pos.lat&&pos.lon)
		counterSample++;
	mGpsBlock_startedFlag=counterSample>NUMBER_SAMPLE_START_UBLOX;
	return 0;
}




void gpsBlock_initUblox(){
	
	UbloxConfigParam config;
	config.baudrate=GPS_CONF_BDRATE;
	config.measureRate=GPS_CONF_MEASURE_RATE;
	initUbloxWithUart(&mGpslock_Ublox,config,GPS_CHANNEL,GPS_CONF_BDRATE);
}


void gpsBlock_initGpsFilter(){
	initAveFilter(&mGpsBlock_GpsFilter.filterLat,GPS_NUM_SAMPLE_FILTER);
	initAveFilter(&mGpsBlock_GpsFilter.filterLon,GPS_NUM_SAMPLE_FILTER);
//	GpsFilterConfig con;
//	con.aGain=GPS_FILTER_A_GAIN;
//	con.vGain=GPS_FILTER_V_GAIN;
//	con.gpsGain=GPS_FILTER_G_GAIN;
//	con.vMax=GPS_FILTER_V_MAX;
//	con.aMax=GPS_FILTER_A_MAX;
//	initGpsFilter(&mGpsBlock_GpsFilter,con);
}

void gpsBlock_updateFilter(void){
	updateAveFilter(&mGpsBlock_GpsFilter.filterLat,(float)mGpslock_Ublox.state.lat);
	updateAveFilter(&mGpsBlock_GpsFilter.filterLat,(float)mGpslock_Ublox.state.lon);
}

void initGpsBlock(void){
	mGpsBlock_EnableFlag=1;
	gpsBlock_initUblox();
	gpsBlock_initGpsFilter();
}

int isGpsBlockReadly(void){
	return mGpsBlock_startedFlag;
}

NaviPosition debugAnchorPoint;

float debugDistance;

int updateGpsBlock(void){
//	Vector2D accel;
//	if(!mGpsBlock_EnableFlag)
//		return 0;
//	if(!checkAndStartedBlock())
//		return 0;
//	updateUblox(&mGpslock_Ublox);
//	if(debugAnchorPoint.lat==0&&debugAnchorPoint.lon==0){
//		debugAnchorPoint=getPositionViaUblox(mGpslock_Ublox);
//		enableGpsFilter(&mGpsBlock_GpsFilter,getPositionViaUblox(mGpslock_Ublox));
//		return 0;
//	}
//	
//	NaviPosition navi;
//	navi.lat=0;
//	navi.lon=0;
//	
//	debugDistance=getDistance(debugAnchorPoint,debugAnchorPoint);
//	accel.x=getAccel().roll;
//	accel.y=getAccel().pitch;
//	updateGpsFilter(&mGpsBlock_GpsFilter,getPositionViaUblox(mGpslock_Ublox),accel,getEuler(),getGpsBlockDeltaT());


	updateUblox(&mGpslock_Ublox);
	gpsBlock_updateFilter();
	return 1;
}



NaviPosition getPositionViaGpsBlock(void){
	
	NaviPosition result;
	result.lat=getAveFilterResult(mGpsBlock_GpsFilter.filterLat);
	result.lon=getAveFilterResult(mGpsBlock_GpsFilter.filterLon);
	return result;
//	return getPositionViaGpsFilter(mGpsBlock_GpsFilter);
}

void enableGpsBlock(void){
	enableUblox(&mGpslock_Ublox);
	mGpsBlock_EnableFlag=1;
}

void disableGpsBlock(void){
	disableUblox(&mGpslock_Ublox);
	mGpsBlock_EnableFlag=0;
}


int isGpsBlockEnable(void){
	return mGpsBlock_EnableFlag;
}

