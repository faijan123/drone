#include "UartFinder.h"
#include "UartConst.h"
#include "string.h"

USART_TypeDef* findUSARTPointer(int uart){
	switch(uart){
		case SERIAL_4:
			return UART4;
		case SERIAL_6:
			return USART6;
		default:	
			return NULL;
	}
}
