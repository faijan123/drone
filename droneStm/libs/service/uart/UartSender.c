#include "UartSender.h"
#include "UartFinder.h"
#include "TcTime.h"
#include "string.h"



u32 _sendByteViaUartWithTimeOut(USART_TypeDef *uart,u8 value,u32 timeout){
	u32 anchor=getCurrentTime();
	u32 remain;

	USART_SendData(uart,value);
	do{
		remain=timeout<(getCurrentTime()-anchor)?0:timeout-(getCurrentTime()-anchor);
	}while (USART_GetFlagStatus(uart, USART_FLAG_TC) == RESET&&remain);
	return timeout>(getCurrentTime()-anchor)?0:timeout-(getCurrentTime()-anchor);
}


u32 _sendBytesViaUartWithTimeOut(USART_TypeDef *uart,u8 *values,int length,u32 timeout){
	u32 remain=timeout;
	for(int i=0;i<length&&remain;i++)
		remain=_sendByteViaUartWithTimeOut(uart,values[i],remain);
	return remain;
}




void _sendByteViaUart(USART_TypeDef *uart,uint8_t value){
	USART_SendData(uart,value);
	while (USART_GetFlagStatus(uart, USART_FLAG_TC) == RESET);
}


void _sendBytesViaUart(USART_TypeDef *uart,uint8_t *values,int length){
	for(int i=0;i<length;i++)
		_sendByteViaUart(uart,values[i]);
}


/*------------------------------------------public--------------------------------------------------------------------*/

void sendByteviaUart(int uart,u8 value){
	USART_TypeDef *pUart=findUSARTPointer(uart);
	if(pUart==NULL)
		return ;
	_sendByteViaUart(pUart,value);
}


void sendByteViaUart4(u8 value){
	sendByteviaUart(SERIAL_4,value);
}

void sendByteViaUart6(u8 value){
	sendByteviaUart(SERIAL_6,value);
}


void sendBytesviaUart(int uart,u8 *value,int length){
	USART_TypeDef *pUart=findUSARTPointer(uart);
	if(pUart==NULL)
		return ;
	_sendBytesViaUart(pUart,value,length);
}




void sendBytesViaUart4(u8 *buffer,int length){
	sendBytesviaUart(SERIAL_4,buffer,length);
}

void sendBytesViaUart6(uint8_t *buffer,int length){
	sendBytesviaUart(SERIAL_6,buffer,length);
}

void sendBytesViaUart7(u8 *value,int length){

}



u32 sendByteViaUartWithTimeout(int uart,u8 value,u32 timeout){
	USART_TypeDef *uartPointer=findUSARTPointer(uart);
	if(uartPointer==NULL)
		return 0;
	return _sendByteViaUartWithTimeOut(uartPointer,value,timeout);
}



u32 sendByteViaUart4WithTimeout(u8 value,u32 timeout){
	return sendByteViaUartWithTimeout(SERIAL_4,value,timeout);
}
u32 sendByteViaUart6WithTimeout(u8 value,u32 timeout){
	return sendByteViaUartWithTimeout(SERIAL_6,value,timeout);
}
u32 sendByteViaUart7WithTimeout(u8 value,u32 timeout){
	return 0;
}

u32 sendBytesviaUartWithTimeout(int uart,u8 *values,int length,u32 timeout){
	USART_TypeDef* pUart=findUSARTPointer(uart);
	if(uart!=NULL)
		return sendBytesviaUartWithTimeout(uart,values,length,timeout);
	return 0;
}

u32 sendBytesViaUart4WithTimeout(u8 *values,int length,u32 timeout){
	return sendBytesviaUartWithTimeout(SERIAL_4,values,length,timeout);
}

u32 sendBytesViaUart6WithTimeout(u8 *values,int length,u32 timeout){
	return sendBytesviaUartWithTimeout(SERIAL_6,values,length,timeout);
}

u32 sendBytesViaUart7WithTimeout(u8 *values,int length,u32 timeout){
	return 0;
}
