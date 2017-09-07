/*
@author: truonglx,tecasoftandtech
@des: cai dat function cho header barometer ms5611.h
@link:
1. Ms5611EpromReader: Doc Eprom cua cam bien
2. Ms5611Reader: Doc du lieu ADC tu cam bien
3. Ms5611Calculator: tinh toan du lieu tho.
*/




#include "BarometerMs5611.h"
#include "Ms5611EpRomReader.h"
#include "i2c.h"
#include "Delay.h"



#define MS_ADDR 0x76<<1
#define MS_CMD_RESET 0x1E
#define MS_TIME_WAIT_RESPONSE 15000 // thoi gian cho baromater tinh toan gia tri adc.
#define MS_CYCLE_UPDATE_TEMP  1000    // tinh toan theo chu ki update pressue;



#define MS_ULTRA_HIGHT 0x05
#define MS_HIGHT 0x04
#define MS_STANDARD 0x03
#define MS_LOW 0x02
#define MS_ULTRA_LOW 0x01
#define MS_RESET 
#define MS_RE_TEMP 0x40
#define MS_RE_PRESURE 0x50

#define RESULT_STATE_NO_NEW_VALUE 			0
#define RESULT_STATE_NEW_VALUE_PRESSURE 1
#define RESULT_STATE_NEW_VALUE_TEMP 		2





int mapQualityToOSR(Ms5611Quality quality){
	if(quality==MS5611_ULTRA_LOW_POWER)
		return 256;
	else if(quality==MS5611_LOW_POWER)
		return 512;
	else if(quality==MS5611_STANDARD)
		return 1024;
	else if(quality==MS5611_HIGH_RES)
		return 2048;
	else if(quality==MS5611_ULTRA_HIGH_RES)
		return 4096;
	return -1;
}


void resetMs5611(void){
	writeByteWithOutRegViaI2c(MS_ADDR,MS_CMD_RESET);
	delayMilis(20);
}


void readEprom(u16 *buffer){
	Ms5611EpromReader epromReader;	
	readMs5611Eprom(&epromReader);
	copyMs5611Eprom(epromReader,buffer);
}






int checkTimeWaitReponse(BarometerMs5611 *ms5611){
	if(checkDeltaTimeChecker(&ms5611->state.checkTimeResponse)){
		disableDeltaTimeChecker(&ms5611->state.checkTimeResponse);
		return 1;
	}
	return 0;
}

int isRequestTemp(BarometerMs5611 *ms5611){
	ms5611->state.counterRequestPressure++;
	if(ms5611->state.counterRequestPressure>MS_CYCLE_UPDATE_TEMP){
		ms5611->state.counterRequestPressure=0;
		return 1;
	}
	return 0;
}






Ms5611Action getNextAction(BarometerMs5611 *ms5611){
	Ms5611Action prevAction=ms5611->state.prevAction;
	if(prevAction==NULL_ACTION)
		return REQUEST_PRESSURE;
	else if(prevAction==REQUEST_PRESSURE)
		return WAIT_RES_PRESSURE;
	else if(prevAction==WAIT_RES_PRESSURE)
		return checkTimeWaitReponse(ms5611)?READ_RES_PRESSURE:WAIT_RES_PRESSURE;
	else if(prevAction==READ_RES_PRESSURE)
		return isRequestTemp(ms5611)?REQUEST_PRESSURE:REQUEST_TEMP;
	else if(prevAction==REQUEST_TEMP)
		return WAIT_RES_TEMP;
	else if(prevAction==WAIT_RES_TEMP)
		return checkTimeWaitReponse(ms5611)? READ_RES_TEMP:WAIT_RES_TEMP;
	else if(prevAction==READ_RES_TEMP)
		return REQUEST_PRESSURE;
	return NULL_ACTION;
}



int readTempFromMs5611(BarometerMs5611 *ms5611){
	ms5611->state.prevAction=READ_RES_TEMP;
	readTempMs5611(&ms5611->ms5611Reader);
	updateTempAndPressureMs5611Calculator(&ms5611->ms5611Cal,ms5611->ms5611Reader.adcPressure,ms5611->ms5611Reader.adcTemp);
	return RESULT_STATE_NEW_VALUE_TEMP;
}


int readPressureFromMs5611(BarometerMs5611 *ms5611){
	ms5611->state.prevAction=READ_RES_PRESSURE;
	readPressureMs5611(&ms5611->ms5611Reader);
	updateTempAndPressureMs5611Calculator(&ms5611->ms5611Cal,ms5611->ms5611Reader.adcPressure,ms5611->ms5611Reader.adcTemp);
	return RESULT_STATE_NEW_VALUE_PRESSURE;
}

int requestTempFromMs5611(BarometerMs5611 *ms5611){
	ms5611->state.prevAction=REQUEST_TEMP;
	requestTempMs5611(ms5611->ms5611Reader);
	return RESULT_STATE_NO_NEW_VALUE;
}


int requestPressureFromMs5611(BarometerMs5611 *ms5611){
	
	ms5611->state.prevAction=REQUEST_PRESSURE;
	requestPressureMs5611(ms5611->ms5611Reader);
	return RESULT_STATE_NO_NEW_VALUE;
}



int waitTempResultFromMs5611(BarometerMs5611 *barometer){
	if(!isEnableDeltaTimeChecker(barometer->state.checkTimeResponse))
		initDeltaTimeChecker(&barometer->state.checkTimeResponse,MS_TIME_WAIT_RESPONSE);
	barometer->state.prevAction=WAIT_RES_TEMP;
	return RESULT_STATE_NO_NEW_VALUE;
}


int waitPressureResultFromMs5611(BarometerMs5611 *barometer){
	if(!isEnableDeltaTimeChecker(barometer->state.checkTimeResponse))
		initDeltaTimeChecker(&barometer->state.checkTimeResponse,MS_TIME_WAIT_RESPONSE);
	barometer->state.prevAction=WAIT_RES_PRESSURE;
	return RESULT_STATE_NO_NEW_VALUE;
}


void initBarometerMs5611(BarometerMs5611 *barometer,Ms5611Quality quality ){
	u16 eprom[6];
	resetMs5611();
	readEprom(eprom);
	initMs5611Calculator(&barometer->ms5611Cal,eprom);
	initMs5611Reader(&barometer->ms5611Reader,mapQualityToOSR(quality));
	barometer->state.prevAction=NULL_ACTION;
	while(updateBarometerMs5611(barometer)!=RESULT_STATE_NEW_VALUE_TEMP);
}




int updateBarometerMs5611(BarometerMs5611 *barometer){
	Ms5611Action action=getNextAction(barometer);
	if(action==REQUEST_PRESSURE)
		return requestPressureFromMs5611(barometer);
	else if(action==WAIT_RES_PRESSURE)
		return waitPressureResultFromMs5611(barometer);
	else if(action==READ_RES_PRESSURE)
		return readPressureFromMs5611(barometer);
	else if(action==REQUEST_TEMP)
		return requestTempFromMs5611(barometer);
	else if(action==WAIT_RES_TEMP)
		return waitTempResultFromMs5611(barometer);
	else if(action==READ_RES_TEMP)
		return readTempFromMs5611(barometer);
	return RESULT_STATE_NO_NEW_VALUE;
}


float getMs5611Temp(BarometerMs5611 barometer){
	return barometer.ms5611Cal.temp;
}

float getMs5611Presure(BarometerMs5611 barometer){
	return barometer.ms5611Cal.pressure;
}

float getMs5611Altitude(BarometerMs5611 barometer){
	return barometer.ms5611Cal.altitude;
}
