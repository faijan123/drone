
// @author:truonglx,teca soft and tech.
// des: 


#ifndef UartControl_h_
#define UartControl_h_

#include "stm32f4xx.h"

void configUart4(u32 baudrate);
void configUart6(u32 baudrate);
void configUart7(u32 baudrate);

void initUart4(u32 baudrate);
void initUart6(u32 baudrate);
void initUart7(u32 baudrate);


void initUartWithNVIC(int uart,int baudrate,int size);
void initUart4NVIC(u32 baudrate,int sizeBuffer);
void initUart6NVIC(u32 baudrate,int sizeBuffer);
void initUart7NVIC(u32 baudrate,int sizeBuffer);


void disableUart4(void);
void disableUart6(void);
void disableUart7(void);
void disableUart(int uart);

void enableUart4(void);
void enableUart6(void);
void enableUart7(void);
void enableUart(int uart);

#endif
