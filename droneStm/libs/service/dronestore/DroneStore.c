#include "DroneStore.h"
#include "FlashReader.h"
#include "FlashWriter.h"
#include "ArrayUtil.h"
#include <string.h>

#define ACCEL_OFF_SET_ADDR 	0
#define GYRO_OFF_SET_ADDR  	0

int readDroneStoreFlag=0;
int16_t storeAccelOffset[3];
int16_t storeGyroOffset[3]={-27,-2,83};
float storeAltitudeOffset=-27.43;



float matrixMagnet[3][3]={
	{9.158,-15.811,0.482},
	{9.185,4.237,-0.195},
	{16.057,-21.979,3.084},
};

float biasMagnet[]={
	-35.098
	-4.267,
	193.471
};




void getMagnetOffset(float matrix[3][3],float bias[3]){
	for(int i=0;i<3;i++)
		memcpy(matrix[i],matrixMagnet,3*sizeof(float));
	memcpy(bias,biasMagnet,3*sizeof(float));
}
void writeAltitudeOffset(float offset){
	storeAltitudeOffset=offset;
}
float getAltitudeOffset(){
	return storeAltitudeOffset;
}
void readAccelOffset(){
	uint8_t bytesOffset[6];
	readFromFlash(ACCEL_OFF_SET_ADDR,bytesOffset,0,6);
	wrapBytesToInt16_tArray(bytesOffset,storeGyroOffset,3);
}


void readGyroOffset(){
	uint8_t bytesOffset[6];
	readFromFlash(GYRO_OFF_SET_ADDR,bytesOffset,0,6);
	wrapBytesToInt16_tArray(bytesOffset,storeGyroOffset,3);
}


void readDataFromDroneStore(){
	if(!readDroneStoreFlag)
		return ;
	readAccelOffset();
	readGyroOffset();
	readDroneStoreFlag=1;
}



void writeAccelOffset(int16_t *offset){	
//	uint8_t bytesOffset[6];
//	getBytesFromInt16_tArray(offset,bytesOffset,3);
//	initFlashWriter();
//	writeToFlash(ACCEL_OFF_SET_ADDR,bytesOffset,0,6);
//	closeWriter();
}

void writeGyroOffset(int16_t *offset){

	memcpy(storeGyroOffset,offset,3*sizeof(int16_t));
//	uint8_t bytesOffset[6];
//	getBytesFromInt16_tArray(offset,bytesOffset,3);
//	initFlashWriter();
//	writeToFlash(GYRO_OFF_SET_ADDR,bytesOffset,0,6);
//	closeWriter();
}



void getAccelOffset(int16_t *offset){
	readDataFromDroneStore();
	copyInt16_tArray(offset,storeAccelOffset,3);
}

void getGyroOffset(int16_t *offset){
	readDataFromDroneStore();
	copyInt16_tArray(offset,storeGyroOffset,3);
}


