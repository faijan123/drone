/*
@author:truonglx, tecasoftandtech.
@des: Thu vien lam viec voi barometer ms5611.
+ Quan li qua trinh request,doc cam bien.
*/

#ifndef BarometerMs5611_h_
#define BarometerMs5611_h_


#include "TimeChecker.h"
#include "Ms5611Reader.h"
#include "Ms5611Calculator.h"
#include "Filter.h"


typedef enum Ms5611Quality{
    MS5611_ULTRA_HIGH_RES   = 0x08,
    MS5611_HIGH_RES         = 0x06,
    MS5611_STANDARD         = 0x04,
    MS5611_LOW_POWER        = 0x02,
    MS5611_ULTRA_LOW_POWER  = 0x00
} Ms5611Quality;

typedef enum{
	NULL_ACTION=-1,
	REQUEST_PRESSURE=0,
	WAIT_RES_PRESSURE=1,
	READ_RES_PRESSURE=2,
	REQUEST_TEMP=3,
	WAIT_RES_TEMP=4,
	READ_RES_TEMP=5
}Ms5611Action;


typedef struct BarometerMs5611State{
	float presure,temp;
	Ms5611Action prevAction;
	DeltaTimeChecker checkTimeResponse;
	int counterRequestPressure;
	
}BarometerMs5611State;

typedef struct BarometerMs5611{
	BarometerMs5611State state;
	Ms5611Reader ms5611Reader;
	Ms5611Calculator ms5611Cal;
}BarometerMs5611;


void initBarometerMs5611(BarometerMs5611 *barometer,Ms5611Quality quality);
int updateBarometerMs5611(BarometerMs5611 *barometer);
float getMs5611Temp(BarometerMs5611 barometer);
float getMs5611Presure(BarometerMs5611 barometer);
float getMs5611Altitude(BarometerMs5611 barometer);


#endif

