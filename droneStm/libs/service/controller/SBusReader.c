/*
@author:truonglx,teca soft and tech
@des: 
read sbus data via uart.Uart Baudrate is 100000.Uart is uart6 with interrupt;
SBus Frame Detail is in https://developer.mbed.org/users/Digixx/notebook/futaba-s-bus-controlled-by-mbed/. 
*/


#include "SBusReader.h"
#include "Uart.h"
#include "stdio.h"
#include "TcTime.h"

#define SBUS_END_FRAME_INDEX 		23
#define SBUS_HEADER 					(u8)0x0F
#define SBUS_END    					(u8)0x0
#define SBUS_LENGTH 					25
#define SBUS_BAUDRATE   			100000
#define SBUS_CHANNEL          	SERIAL_6


int checkHeaderSBus(void){
	while(getNumberByteInBufferOfUart(SBUS_CHANNEL)>=SBUS_END_FRAME_INDEX)
		if(readByteBufferOfUart(SBUS_CHANNEL)==SBUS_HEADER)
			return 1;
	return 0;
}



int checkEndByteSbus(uint8_t *frame){
	return frame[SBUS_END_FRAME_INDEX]==SBUS_END;
}


u8 debugSbusFlag;
u8 debugSbusEnd;
u8 debugHeader;

int readFrame(u8 *frame){
	
	if(!checkHeaderSBus())
		return 0;
	frame[0]=SBUS_HEADER;
	readBytesBufferOfUart(SBUS_CHANNEL,frame+1,SBUS_LENGTH-2);
	clearBufferOfUart(SBUS_CHANNEL);
	debugSbusFlag=frame[21];
	debugSbusEnd=frame[22];
	return checkEndByteSbus(frame);
}



SBusData parseSBusFrame(uint8_t *buffer){
	SBusData res;
	res.channel1 	= ((buffer[1]|buffer[2]<<8) & 0x07FF);   
	res.channel2   = ((buffer[2]>>3|buffer[3]<<5)  & 0x07FF);
	res.channel3   = ((buffer[3]>>6 |buffer[4]<<2 |
	buffer[5]<<10)  & 0x07FF);
	res.channel4 	= ((buffer[5]>>1 |buffer[6]<<7) & 0x07FF);
	res.channel5   = ((buffer[6]>>4 |buffer[7]<<4) & 0x07FF);
	res.channel6 	= ((buffer[7]>>7 |buffer[8]<<1 |buffer[9]<<9)   & 0x07FF);
	res.channel7   = ((buffer[9]>>2 |buffer[10]<<6) & 0x07FF);
	res.channel8 	= ((buffer[10]>>5|buffer[11]<<3) & 0x07FF);
	res.channel9   = ((buffer[12]   |buffer[13]<<8) & 0x07FF);
	res.channel10  = ((buffer[13]>>3|buffer[14]<<5)  & 0x07FF);
	res.channel11  = ((buffer[14]>>6|buffer[15]<<2|buffer[16]<<10) & 0x07FF);
	res.channel12  = ((buffer[16]>>1|buffer[17]<<7) & 0x07FF);
	res.channel13  = ((buffer[17]>>4|buffer[18]<<4) & 0x07FF);
	res.channel14  = ((buffer[18]>>7|buffer[19]<<1|buffer[20]<<9)  & 0x07FF);
	res.channel15  = ((buffer[20]>>2|buffer[21]<<6) & 0x07FF);
	res.channel16  = ((buffer[21]>>5|buffer[22]<<3) & 0x07FF);
	return res;
}


void initSBusReader(void){
	initUartWithNVIC(SBUS_CHANNEL,100000,30);
}


u8 debugFlag;

int readDataViaSBus(SBusData *res)
{
	static uint8_t sbusFrame[SBUS_LENGTH];
	if(getNumberByteInBufferOfUart(SBUS_CHANNEL)<SBUS_LENGTH )
		return 0;
	if(readFrame(sbusFrame)){
		*res=parseSBusFrame(sbusFrame);
		return 1;
	}
	return 0;
}


void disableSBusReader(){
	disableUart(SBUS_CHANNEL);
}

void enableSBusReader(){
	enableUart(SBUS_CHANNEL);
}


