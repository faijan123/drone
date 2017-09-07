#include "i2c.h"
#include "stdio.h"
#include "delay.h"
#include "gpio.h"
#include "tm_stm32f4_gpio.h"
#define RCC_GPIO 				RCC_AHB1Periph_GPIOB
#define RCC_I2C  				RCC_APB1Periph_I2C2
#define SDA_PIN  				GPIO_Pin_11
#define SCL_PIN  				GPIO_Pin_10
#define SCL_PIN_SOURCE 	GPIO_PinSource10
#define SDA_PIN_SOURCE 	GPIO_PinSource11
#define I2CGPIO GPIOB 
#define GPIO_AF GPIO_AF_I2C2
#define I2C_DUTY I2C_DutyCycle_2
#define I2C_CLOCK 400000


void enableI2C(){

	TM_GPIO_Init(GPIOD, GPIO_Pin_10, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_High);
  TM_GPIO_Init(GPIOA, GPIO_Pin_6, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_High);
  TM_GPIO_Init(GPIOC, GPIO_Pin_2, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_High);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_10);
  TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_6);
  TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_2);
	
//	initGPIO(GPIOD,GPIO_Pin_10,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_High_Speed,GPIO_PuPd_UP);
//	initGPIO(GPIOA,GPIO_Pin_6,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_High_Speed,GPIO_PuPd_UP);
//	initGPIO(GPIOC,GPIO_Pin_2,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_High_Speed,GPIO_PuPd_UP);
//	setPinHight(GPIOD, GPIO_Pin_10);
//	setPinLow(GPIOA, GPIO_Pin_6);
//	setPinHight(GPIOC, GPIO_Pin_2);
	
}
void initGpioI2C()
{
	enableI2C();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef gpioConfig;
	gpioConfig.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	gpioConfig.GPIO_Mode=GPIO_Mode_AF;
	gpioConfig.GPIO_OType=GPIO_OType_OD;
	gpioConfig.GPIO_PuPd = GPIO_PuPd_UP;
	gpioConfig.GPIO_Speed = GPIO_Speed_100MHz;  
	GPIO_Init(GPIOB, &gpioConfig);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_I2C2);
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_I2C2);
}


void initI2C2()
{
	I2C_InitTypeDef i2cConfig;
	I2C_DeInit(I2C2);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	i2cConfig.I2C_Mode 	= I2C_Mode_I2C;
	i2cConfig.I2C_Ack 	= I2C_Ack_Enable;
	i2cConfig.I2C_ClockSpeed = I2C_CLOCK;
	i2cConfig.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C2, &i2cConfig);	
	I2C_Cmd(I2C2, ENABLE); 
}


void initI2C()
{
	initGpioI2C();
	initI2C2();
}




void startI2C(u8 address,u8 direction){
 	while(I2C_GetFlagStatus(i2cPointer, I2C_FLAG_BUSY)){};
  I2C_GenerateSTART(i2cPointer, ENABLE);
		
  while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(i2cPointer, address, direction);
  if(direction == I2C_Direction_Transmitter){
		while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
	else if(direction == I2C_Direction_Receiver){
		while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
}

void stopI2C(void)
{
	I2C_GenerateSTOP(i2cPointer, ENABLE);
}




void requestI2C(u8 address,u8 reg)
{
	uint8_t buffer[]={reg};
	writeBytesWithOutRegViaI2c(address,buffer,1);
}



void readBytesViaI2C(u8 address,u8 *buffer,int length)
{
	int counter=0;
	startI2C(address,I2C_Direction_Receiver);
  I2C_AcknowledgeConfig(i2cPointer, ENABLE);
	while(counter<length)		
	{ 
		if(counter==length-1)
		{
			I2C_AcknowledgeConfig(i2cPointer, DISABLE);
			stopI2C();
			
		}
		while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_BYTE_RECEIVED));
		buffer[counter]=I2C_ReceiveData(i2cPointer);
		counter++;
	}
}

u8 readByteViaI2C(u8 address )
{
	u8 buffer[1];
	readBytesViaI2C(address,buffer,1);
	return buffer[0];
}


u8 requestAndReadByteViaI2C(u8 address,u8 reg)
{
	requestI2C(address,reg);
	return readByteViaI2C(address);
}


void requestAndReadBytesViaI2C(u8 address,u8 reg,u8 *buffer,int length)
{
	requestI2C(address,reg);
	readBytesViaI2C(address,buffer,length);
}






void writeBytesViaI2C(u8 address,u8 reg,u8 *buffer,int length)
{
	int i;
	startI2C(address,I2C_Direction_Transmitter);
	I2C_SendData(i2cPointer,reg);
	while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){};
  for(i=0;i<length;i++)
  {
    I2C_SendData(i2cPointer, buffer[i]);
    while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  }
  stopI2C();
}

void writeByteViaI2C(u8 address,u8 reg,u8 val)
{
	u8 buffer[]={val};
	writeBytesViaI2C(address,reg,buffer,1);
}


void writeByteWithOutRegViaI2c(u8 address,u8 val){
	u8 buffer[]={val};
	writeBytesWithOutRegViaI2c(address,buffer,1);
}
void writeBytesWithOutRegViaI2c(u8 address,u8 *buffer,int length)
{
	int i;
	startI2C(address,I2C_Direction_Transmitter);
	for(i=0;i<length;i++)
	{
		I2C_SendData(i2cPointer, buffer[i]);
		while(!I2C_CheckEvent(i2cPointer, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
	stopI2C();
}

void checkDeviceConnected(u8 address){
	
}
