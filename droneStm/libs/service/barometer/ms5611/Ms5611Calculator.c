/*
@author:truonglx,tecasoftandtech
@des: cai dat cac function tinh toan tu header.
*/

#include "Ms5611Calculator.h"
#include "math.h"
#include "CastType.h"
#define SEA_LEVEL_PRESSURE 1013.25
float calculateTemp(Ms5611Calculator *cal){
	int32_t dt;
	dt=cal->adcTemp-(cal->config.c5<<8);
	cal->temp=(2000+(dt*cal->config.c6>>23))/100;
	return cal->temp;
}


float calculatePressure(Ms5611Calculator *cal ){
	int64_t off,sens;
	int32_t dt;

	dt=cal->adcTemp-(CAST_TO_INT32(cal->config.c5)<<8);
	off=(CAST_TO_INT64(cal->config.c2)<<16)+ (CAST_TO_INT64(cal->config.c4*dt)>>7);
	sens=(CAST_TO_INT64(cal->config.c1)<<15)+(CAST_TO_INT64(cal->config.c3*dt)>>8);
	cal->pressure=(((CAST_TO_INT64(cal->adcPressure*sens)>>21)-off)>>15)/100.0f;
	
	return cal->pressure;
}


float calculateAltitude(Ms5611Calculator *cal){
	return cal->altitude=(44330.0f * (1.0f - pow((double)cal->pressure / (double)SEA_LEVEL_PRESSURE, 0.1902949f)));
}
void initMs5611Calculator(Ms5611Calculator *cal,uint16_t *calibrated){
	cal->config.c1=calibrated[0];
	cal->config.c2=calibrated[1];
	cal->config.c3=calibrated[2];
	cal->config.c4=calibrated[3];
	cal->config.c5=calibrated[4];
	cal->config.c6=calibrated[5];

	
}
void updateTempMs5611Calculator(Ms5611Calculator *cal,uint32_t temp){
	cal->adcTemp=temp;
	calculateTemp(cal);
}

void updatePressureMs5611Calculator(Ms5611Calculator *cal,uint32_t pressure){
	cal->adcPressure=pressure;
	calculatePressure(cal);
	calculateAltitude(cal);
}

void updateTempAndPressureMs5611Calculator(Ms5611Calculator *cal, uint32_t pressure,uint32_t temp){
	cal->adcPressure=pressure;
	cal->adcTemp=temp;
	calculateTemp(cal);
	calculatePressure(cal);
	calculateAltitude(cal);
}



float getMs5611CalculatorTemp(Ms5611Calculator cal){
	return cal.temp;
}

float getMs5611CalculatorPressure(Ms5611Calculator cal){
	return cal.pressure;
}
float getMs5611CalculatorAltitude(Ms5611Calculator cal){
	return cal.altitude;
}

