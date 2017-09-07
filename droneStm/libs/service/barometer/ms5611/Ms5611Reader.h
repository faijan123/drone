/*
@author:truonglx,tecasoftandtech.
@des: 
1. quan li qua trinh reques va doc du lieu tu cam bien ms5611
2. nguyen li doc du lieu tu cam bien
Buoc 1. Request voi cmd tuong ung (cmd gom 2 loai la doc ap xuat va doc nhiet do)
Buoc 2. Cho khong dong bo. Trong khi cam bien tinh toan gia tri adc, ta co the lam viec khac
Buoc 3. Doc gia tri adc bit bang cmd doc.
*/



#ifndef Ms5611Reader_h_
#define Ms5611Reader_h_
#include "stm32f4xx.h"

typedef struct Ms5611Reader{ 
	u16 osr;
	uint32_t adcPressure,adcTemp;
}Ms5611Reader;


void initMs5611Reader(Ms5611Reader *reader,u16 osr);
void requestPressureMs5611(Ms5611Reader reader);
uint32_t readPressureMs5611(Ms5611Reader *reader);
void requestTempMs5611(Ms5611Reader reader);
uint32_t readTempMs5611(Ms5611Reader *reader);
#endif


