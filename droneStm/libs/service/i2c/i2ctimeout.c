#include "i2c.h"
#include "TcTime.h"

int isTimeOut(u32 *prevTime,int32_t *timeout){	
	if(timeout<=0)
		return 1;
	if(*prevTime==0){
		*prevTime=getCurrentTime();
		return 0;
	}
	else{
		*timeout-=getCurrentTime()-*prevTime;
		if(*timeout>0){
			*prevTime=getCurrentTime();
			return 0;
		}
		return 1;
	}
}


void startI2CWithTimeOut(u8 address,u8 direction,int32_t *timeout){
	
	u32 time=0;
 	while(I2C_GetFlagStatus(i2cPointer, I2C_FLAG_BUSY))
		if(isTimeOut(&time,timeout))
			return;
	
		
  I2C_GenerateSTART(i2cPointer, ENABLE);
  while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_MODE_SELECT))
		if(isTimeOut(&time,timeout))
			return;
	
	
  I2C_Send7bitAddress(i2cPointer, address, direction);
  if(direction == I2C_Direction_Transmitter){
		while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
			if(isTimeOut(&time,timeout)){
				stopI2C();
				return;
			}
	}
	
	else if(direction == I2C_Direction_Receiver){
		while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
			if(isTimeOut(&time,timeout)){
				stopI2C();
				return;
			}
	}
}



void requestI2CWithTimeOut(u8 address,u8 reg,int32_t *timeout){
	writeByteWithOutRegViaI2cWithTimeOut(address,reg,timeout);
}


void readBytesViaI2CWithTimeOut(u8 address,u8 *buffer,int length,int32_t *timeout){
	int counter=0;
	u32 time=0;
	
	startI2CWithTimeOut(address,I2C_Direction_Receiver,timeout);
	if(*timeout<0)
		return;
	I2C_AcknowledgeConfig(i2cPointer, ENABLE);
	while(counter<length){
		if(isTimeOut(&time,timeout)){
			stopI2C();
			return;
		}
		
		if(counter==length-1){
			I2C_AcknowledgeConfig(i2cPointer, DISABLE);
			stopI2C();
		}
		
		while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_BYTE_RECEIVED))
			if(isTimeOut(&time,timeout)){
				stopI2C();
				return ;
			}
		buffer[counter]=I2C_ReceiveData(i2cPointer);
		counter++;
	}
}

u8   readByteViaI2CWithTimeOut(u8 address,int32_t *timeout){
	u8 buffer[1];
	readBytesViaI2C(address,buffer,1);
	return buffer[0];
}

u8 	 requestAndReadByteViaI2CWithTimeOut(u8 address,u8 reg,int32_t *timeout){
	u8 buffer[1];
	requestAndReadBytesViaI2CWithTimeOut(address,reg,buffer,1,timeout);
	return buffer[0];
}

void requestAndReadBytesViaI2CWithTimeOut(u8 address,u8 reg,u8 *buffer,int length,int32_t *timeout){
	requestI2CWithTimeOut(address,reg,timeout);
	if(*timeout<0)
		return ;
	readBytesViaI2CWithTimeOut(address,buffer,length,timeout);
}

void writeByteViaI2CWithTimeOut(u8 address,u8 reg,u8 val,int32_t *timeout){
	u8 buffer[]={val};
	writeBytesViaI2CWithTimeOut(address,reg,buffer,1,timeout);
}

void writeBytesViaI2CWithTimeOut(u8 address,u8 reg,u8 *buffer,int length,int32_t* timeout){
	int counter=0;
	u32 time=0;
	
	startI2CWithTimeOut(address,I2C_Direction_Receiver,timeout);
	I2C_AcknowledgeConfig(i2cPointer, ENABLE);
	while(counter<length){
		if(!isTimeOut(&time,timeout)){
			stopI2C();
			return;
		}
		if(counter==length-1){
			I2C_AcknowledgeConfig(i2cPointer, DISABLE);
			stopI2C();
		}
		while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_BYTE_RECEIVED))
			if(isTimeOut(&time,timeout)){
				stopI2C();
				return ;
			}
		
		buffer[counter]=I2C_ReceiveData(i2cPointer);
		counter++;
	}
}

void writeByteWithOutRegViaI2cWithTimeOut(u8 address,u8 val,int32_t *timeout){
	u8 buffer[]={val};
	writeBytesWithOutRegViaI2cWithTimeOut(address,buffer,1,timeout);
}

void writeBytesWithOutRegViaI2cWithTimeOut(u8 address,u8 *buffer,int length,int32_t *timeout){
	int i;
	u32 time=0;
	startI2CWithTimeOut(address,I2C_Direction_Transmitter,timeout);
	for(i=0;i<length;i++){
		I2C_SendData(i2cPointer, buffer[i]);
		while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
			if(isTimeOut(&time,timeout)){
				stopI2C();
				return ;
			}
		stopI2C();
	}
}
