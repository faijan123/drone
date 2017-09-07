#include "UartReceiver.h"
#include "UartFinder.h"
#include "string.h"
#include "SystemTime.h"




u8	_readByteViaUart(USART_TypeDef *uart){
	u8 res;
	while(USART_GetFlagStatus(uart, USART_FLAG_RXNE) == 0);
	res=USART_ReceiveData(uart);
	USART_ClearFlag(uart, USART_FLAG_RXNE);
	return res;
}

int	_readBytesViaUart(USART_TypeDef *uart,u8 *buffer,int length){
	for(int i=0;i<length;i++)
		buffer[i]=_readByteViaUart(uart);
	return length;
}


u32 _readByteViaUartWithTimeout(USART_TypeDef *uart,u8 *out,u32 timeout){
	u32 anchor;
	anchor=getCurrentTime();
	while(!USART_GetFlagStatus(uart, USART_FLAG_RXNE) &&timeout)
		timeout=timeout>(getCurrentTime()-anchor)?(timeout-(getCurrentTime()-anchor)):0;
	
	if(!timeout)
		return 0;
	*out=USART_ReceiveData(uart);
	USART_ClearFlag(uart, USART_FLAG_RXNE);
	return timeout;
}


u32 _readBytesViaUartWithTimeout(USART_TypeDef *uart,u8 *buffer,int length,u32 timeout){
	u32 remain=timeout;
	for(int i=0;i<length&&remain>0;i++)
		remain=_readByteViaUartWithTimeout(uart,buffer+i,remain);
	return remain;
}



/*-----------------------------------------public----------------------------------*/

u8 readByteViaUart(int uart){
	USART_TypeDef *pUart=findUSARTPointer(uart);
	if(pUart==NULL)
		return 0;
	return _readByteViaUart(pUart);
}



u8 readByteViaUart4(void){
	return readByteViaUart(SERIAL_4);
}

u8 readByteViaUart6(void){
	return readByteViaUart(SERIAL_6);
}

u8 readByteViaUart7(void){
	return 0;
}


void readBytesViaUart(int uart,u8 *out,int length){
	USART_TypeDef *pUart=findUSARTPointer(uart);
	if(pUart==NULL)
		return ;
	_readBytesViaUart(pUart,out,length);
}


void  readBytesViaUart4(u8 *out,int size){
	readBytesViaUart(SERIAL_4,out,size);
}

void readBytesViaUart6(u8 *out,int size){
	readBytesViaUart(SERIAL_6,out,size);
}

void readBytesViaUart7(u8 *out,int size){
}


u32 readBytesViaUartWithTimeout(int uart,u8 *out,int length,u32 timeout){
	USART_TypeDef *uartPointer=findUSARTPointer(uart);
	if(uart==NULL)
		return 0;
	return _readBytesViaUartWithTimeout(uartPointer,out,length,timeout);	
}


u32 readBytesViaUart4WithTimeout(u8 *out,int length,u32 timeout){
	return readBytesViaUartWithTimeout(SERIAL_4,out,length,timeout);	
}

u32 readBytesViaUart6WithTimeout(u8 *out,int length,u32 timeout){
	return readBytesViaUartWithTimeout(SERIAL_6,out,length,timeout);	
}

u32 readBytesViaUart7WithTimeout(u8 *out,int length,u32 timeout){
	return 0;
}

