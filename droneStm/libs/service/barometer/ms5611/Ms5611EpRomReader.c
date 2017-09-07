/*
@author: truonglx,tecasoftandtech
@des: cai dat function doc eprom ms5611.
*/
#include "Ms5611EpRomReader.h"
#include "i2c.h"


#define MS5611_EPROM_READER_ADDR 		0x76<<1
#define MS5611_EPROM_BEGIN_RE    		0xA2
#define MS5611_EPROM_NUMBER_ELEMENT 6					
#define MS5611_EPROM_SIZE_ELEMENT  	2





u16 readElementEprom(int offset){
	u8 buffer[2];
	requestAndReadBytesViaI2C(MS5611_EPROM_READER_ADDR,MS5611_EPROM_BEGIN_RE+offset*2,buffer,MS5611_EPROM_SIZE_ELEMENT);
	return buffer[0]<<8|buffer[1];
}

void readMs5611Eprom(Ms5611EpromReader *reader){
	reader->c1=readElementEprom(0);
	reader->c2=readElementEprom(1);
	reader->c3=readElementEprom(2);
	reader->c4=readElementEprom(3);
	reader->c5=readElementEprom(4);
	reader->c6=readElementEprom(5);
	return ;
}

void copyMs5611Eprom(Ms5611EpromReader reader,u16 *out){
	out[0]=reader.c1;
	out[1]=reader.c2;
	out[2]=reader.c3;
	out[3]=reader.c4;
	out[4]=reader.c5;
	out[5]=reader.c6;
}
