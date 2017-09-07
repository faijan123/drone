// @ des:Finder USART by uartId that defined in UartConst.h .
#ifndef UartFinder_h_
#define UartFinder_h_
#include "stm32f4xx_usart.h"
#include "UartConst.h"

USART_TypeDef* findUSARTPointer(int uart);
#endif
