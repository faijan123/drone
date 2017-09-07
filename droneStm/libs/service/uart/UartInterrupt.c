/*
@author:truonglx
@des: implement uart with interrupt and buffer.
*/




#include "UartHandler.h"
#include <string.h>
#include "UartInterrupt.h"
#include "UartConst.h"
#include "UartControl.h"

Buffer uartBuffer4,uartBuffer6;
Buffer* findBuffer(int uart){
	switch(uart){
		case SERIAL_4 :
			return &uartBuffer4;
		case SERIAL_6:
			return &uartBuffer6;
	}
	return NULL;
}

void nvicHandler(void *who,int uart,u8 bReceived){
	Buffer *pBuffer=findBuffer(uart);
	if(isBufferFull(*pBuffer))
			clearBuffer(pBuffer);
	if(pBuffer!=NULL)
		addByteToBuffer(pBuffer,bReceived);
}



void configUartNVIC(USART_TypeDef *uart,uint8_t NVIC_IRQChannel,u32 groupPriority,u8 subPriority){
	NVIC_InitTypeDef config;
	NVIC_PriorityGroupConfig(groupPriority);
	config.NVIC_IRQChannel = NVIC_IRQChannel;
	config.NVIC_IRQChannelSubPriority = subPriority;
	config.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&config);
	USART_ITConfig(uart,USART_IT_RXNE, ENABLE);
}



/*------------------------------------------public------------------------------------------------*/






void 	initUart4NVIC(uint32_t baudrate,int sizeBuffer){	
	static int initFlag=0;
	if(initFlag)
		return ;
	initFlag=1;
	

	initBuffer(&uartBuffer4,sizeBuffer);
	UartListener listener;
	listener.received=nvicHandler;
	registerUartListener(SERIAL_4,listener);
	configUart4(baudrate);
	configUartNVIC(UART4,UART4_IRQn,NVIC_PriorityGroup_3,2);
	USART_Cmd(UART4, ENABLE);
}



void 	initUart6NVIC(uint32_t baudrate,int sizeBuffer){
	static int initFlag=0;
	if(initFlag)
		return ;
	initFlag=1;
	
	initBuffer(&uartBuffer6,sizeBuffer);
	UartListener listener;
	listener.received=nvicHandler;
	registerUartListener(SERIAL_6,listener);
	
	
	configUart6(baudrate);
	configUartNVIC(USART6,USART6_IRQn,NVIC_PriorityGroup_1,2);
	USART_Cmd(USART6, ENABLE);
}


void 	initUart7NVIC(uint32_t baudrate,int sizeBuffer){
	
}




int readBytesBufferOfUart4(uint8_t *out,int size){
	return getBytesFromBuffer(&uartBuffer4,out,size);
}
int readBytesBufferOfUart6(uint8_t *out,int size){
	return getBytesFromBuffer(&uartBuffer6,out,size);
}

int readBytesBufferOfUart7(uint8_t *out,int size){
	return 0;
}

int readBytesBufferOfUart(int uart,u8 *out,int length){
	Buffer *pBuffer=findBuffer(uart);
	return getBytesFromBuffer(pBuffer,out,length);
}


u8 readByteBufferOfUart4(){
	return getByteFromBuffer(&uartBuffer4);
}
u8 readByteBufferOfUart6(){
	return getByteFromBuffer(&uartBuffer6);
}
u8 readByteBufferOfUart7(){
	return 0;
} 
u8 readByteBufferOfUart(int uart){
	Buffer *pBuffer=findBuffer(uart);
	return getByteFromBuffer(pBuffer);
}




u8 getByteBufferOfUart(int uart,int position){
	Buffer* pBuffer=findBuffer(uart);
	if(pBuffer==NULL||position>=pBuffer->numberByteContent)
		return 0;
	return pBuffer->data[position];
}

u8 getByteBufferOfUart4(int position){
	return getByteBufferOfUart(SERIAL_4,position);
}
u8 getByteBufferOfUart6(int position){
	return getByteBufferOfUart(SERIAL_6,position);
}
u8 getByteBufferOfUart7(int position){
	return 0;
}


u8 getBytesBufferOfUart(int uart,u8 *out,int position,int length){
	Buffer* pBuffer=findBuffer(uart);
	if(pBuffer==NULL||position>=pBuffer->numberByteContent)
		return 0;
	length=length<(pBuffer->numberByteContent-position)?length:(pBuffer->numberByteContent-position);
	memcpy(out,pBuffer->data+position,length);
	return length;
}

u8 getBytesBufferOfUart4(u8 *out,int position,int length){
	return getBytesBufferOfUart(SERIAL_4,out,position,length);
}
u8 getBytesBufferOfUart6(u8 *out,int position,int length){
	return getBytesBufferOfUart(SERIAL_6,out,position,length);
}
u8 getBytesBufferOfUart7(u8 *out,int position,int length){
	return 0;
}

int getNumberByteInBufferOfUart(int uart){
	Buffer *pBuffer=findBuffer(uart);
	if(pBuffer==NULL)
		return -1;
	return pBuffer->numberByteContent;
}
int getNumberByteInBufferOfUart4(void){
	return getNumberByteInBufferOfUart(SERIAL_4);
}
int getNumberByteInBufferOfUart6(void){
	return getNumberByteInBufferOfUart(SERIAL_6);
}
int getNumberByteInBufferOfUart7(void){
	return 0;
}



void removeBytesInBufferOfUart(int uart,int length){
	Buffer* pBuffer=findBuffer(uart);
	if(pBuffer==NULL)
		return;
	removeBytesInBuffer(pBuffer,length);
}

void removeBytesInBufferOfUart4(int length){
	removeBytesInBufferOfUart(SERIAL_4,length);
}
void removeBytesInBufferOfUart6(int length){
	removeBytesInBufferOfUart(SERIAL_6,length);
}
void removeBytesInBufferOfUart7(int length){
	
}



void clearBufferOfUart(int uart){
	Buffer* pBuffer=findBuffer(uart);
	if(pBuffer==NULL)
		return ;

	clearBuffer(pBuffer);
}

void clearBufferfUart4(){
	clearBufferOfUart(SERIAL_4);
}

void clearBufferUart6(){
	clearBufferOfUart(SERIAL_6);
}



int isBufferOfUartEmpty(int uart){
	Buffer *pBuffer=findBuffer(uart);
	if(uart==NULL)
		return 0;
	return pBuffer->numberByteContent==0;
}
int isBufferOfUart4Empty(void){
	return isBufferOfUartEmpty(SERIAL_4);
}
int isBufferOfUart6Empty(void){
	return isBufferOfUartEmpty(SERIAL_6);
}
int isBufferOfUart7Empty(void){
	return 0;
}


int isDataInBufferOfUartReadlly(int uart){
	Buffer *pBuffer=findBuffer(uart);
	if(uart==NULL)
		return 0;
	return pBuffer->numberByteContent>0;
}
int isDataInBufferOfUart4Readlly(void){
	return isBufferOfUartEmpty(SERIAL_4);
}
int isDataInBufferOfUart6Readlly(void){
	return isDataInBufferOfUartReadlly(SERIAL_6);
}
int isDataInBufferOfUart7Readlly(void){
	return 0;
}


int findSubArrayInBufferOffUart(int uart,u8 *element,int length){
	Buffer* pBuffer=findBuffer(uart);
	return findSubArrayInBuffer(*pBuffer,element,length);
}

