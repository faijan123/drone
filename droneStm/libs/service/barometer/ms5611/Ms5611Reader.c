/*
@author: truonglx,tecasoftandtech.
@des: cai dat cac ham doc cam bien ms5611.
*/



#define READER_MS5611_ADDR_W 0x76<<1
#define READER_MS5611_ADDR_R 0x76<<1


#define READER_MS5611_TEMP_LENGTH 3
#define READER_MS5611_PRESURE_LENGTH 3
#define READER_MS5611_CMD_READ 0x00



#include "Ms5611Reader.h"
#include "i2c.h"


u8 getMs5611ReadPressureCommand(u16 osr){
	if(osr==256)
		return 0x40;
	else if(osr==512)
		return 0x42;
	else if(osr==1024)
		return 0x44;
	else if(osr==2048)
		return 0x46;
	else if(osr==4096)
		return 0x48;
	return 0;
}

u8 getMs5611ReadTempCommand(u16 osr){
	if(osr==256)
		return 0x50;
	else if(osr==512)
		return 0x52;
	else if(osr==1024)
		return 0x54;
	else if(osr==2048)
		return 0x56;
	else if(osr==4096)
		return 0x58;
	return 0;
}


void initMs5611Reader(Ms5611Reader *reader,u16 osr){
	reader->osr=osr;
	
}

void requestPressureMs5611(Ms5611Reader reader){
	requestI2C(READER_MS5611_ADDR_W,getMs5611ReadPressureCommand(reader.osr));
}

uint32_t readPressureMs5611(Ms5611Reader *reader){
	u8 buffer[READER_MS5611_PRESURE_LENGTH];
	requestAndReadBytesViaI2C(READER_MS5611_ADDR_R,READER_MS5611_CMD_READ,buffer,3);
	reader->adcPressure=(uint32_t)buffer[0]<<16|(uint32_t)buffer[1]<<8|(uint32_t)buffer[2];
	return reader->adcPressure;
}

void requestTempMs5611(Ms5611Reader reader){
	requestI2C(READER_MS5611_ADDR_W,getMs5611ReadTempCommand(reader.osr));
}

uint32_t readTempMs5611(Ms5611Reader *reader){
	u8 buffer[READER_MS5611_PRESURE_LENGTH];
	requestAndReadBytesViaI2C(READER_MS5611_ADDR_R,READER_MS5611_CMD_READ,buffer,3);
	reader->adcTemp=(uint32_t)buffer[0]<<16|(uint32_t)buffer[1]<<8|(uint32_t)buffer[2];
	return reader->adcTemp;
}

