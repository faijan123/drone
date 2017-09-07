#ifndef UART_H_
#define UART_H_



#include "stm32f4xx.h"



#define TC_UART_4 	4

#define TC_USART_6 	6



typedef void (uart_Callback)(int uartName,void *data,uint8_t c);


void uart_init(int uartName,int baudrate);

void uart_free(int uartName);

void uart_send(int uartname,uint8_t val);


void uart_sendBytes(int uartName,uint8_t *buffer,int length);

void uart_enableNVIC(int uartName);

void uart_disableNVIC(int uartName);

void uart_enable(int uartName);

void uart_disable(int uartName);

void uart_setCallback(int uartName,uart_Callback cb,void *data);

uint8_t uart_readByte(int uartName,uint32_t timeout);

int uart_readBytes(int uartName,uint32_t timeout,uint8_t *buffer,int length);


#endif

