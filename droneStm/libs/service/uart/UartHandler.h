#ifndef UartHandler_h_
#define UartHandler_h_
#include "Buffer.h"


typedef void (*onUartReceived)(void *who,int uart,u8 byte);
typedef struct UartListener{
	void *who;				 // tac gia cua cai thai nay? :D
	onUartReceived received; 
}UartListener;

void registerUartListener(int uart,UartListener listener);


#endif

