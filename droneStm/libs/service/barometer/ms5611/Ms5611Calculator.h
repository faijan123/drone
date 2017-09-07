/*
@author:truonglx,tecasoftandtech.
@des: tinh toan nhiet do,ap xuat,do cao tu cac gia tri adc thu thap duoc.
+ congthuctinhtoan: https://www.cdiweb.com/datasheets/te/ENG_DS_MS5611-01BA03_B.pdf ,trang 8
*/


#ifndef Ms5611Calculator_h_
#define Ms5611Calculator_h_
#include "stm32f4xx.h"


typedef struct Ms5611CalculatorConfig{
	u16 c1,c2,c3,c4,c5,c6;
	
}Ms5611CalculatorConfig;

typedef struct Ms5611Calculator{
	Ms5611CalculatorConfig config;
	float pressure,temp,altitude;
	uint32_t adcTemp,adcPressure;
}Ms5611Calculator;



void initMs5611Calculator(Ms5611Calculator *cal,u16 *calibrate);
void updateTempMs5611Calculator(Ms5611Calculator *cal,uint32_t temp);
void updatePressureMs5611Calculator(Ms5611Calculator *cal,uint32_t pressure);
void updateTempAndPressureMs5611Calculator(Ms5611Calculator *cal, uint32_t pressure,uint32_t temp);
float getMs5611CalculatorPressure(Ms5611Calculator cal);
float getMs5611CalculatorTemp(Ms5611Calculator cal);
float getMs5611CalculatorAltitude(Ms5611Calculator cal);

#endif


