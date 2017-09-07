/*
@author:truonglx,teca soft and tech.
@des: implement function handle message when have interrupt.
@des: observer pattern.
*/
#include "stm32f4xx_usart.h"
#include "UartHandler.h"
#include "UartConst.h"
#include <string.h>
#include "Time.h"


// @des: container struct contain many listener.
typedef struct ListenerUartList{
	int number;
	UartListener listeners[10];
}ListenerUartList;


ListenerUartList listenerUartList4,listenerUartList6;


// @des:util function.
ListenerUartList* getListenerUartList(int uart){
	ListenerUartList *pList=NULL;
	switch(uart){
		case SERIAL_4:
			pList=&listenerUartList4;
			break;
		case SERIAL_6:
			pList=&listenerUartList6;
			break;
		default:
			break;
	}
	return pList;
}

void copyUartListener(UartListener *des,UartListener source){
	des->received=source.received;
	des->who=source.who;
}




// @des: interrupt handler.
void USART6_IRQHandler(void){
	static u8 tem;
	tem=USART_ReceiveData(USART6);
	ListenerUartList *pList=getListenerUartList(SERIAL_6);
	for(int i=0;i<pList->number;i++)
		pList->listeners[i].received(pList->listeners[i].who,SERIAL_6,tem);
	USART_ClearFlag(USART6, USART_FLAG_RXNE);
}



// @des: interrupt handler.
void UART4_IRQHandler(void){
	static u8 tem;
	tem=USART_ReceiveData(UART4);
	ListenerUartList *pList=getListenerUartList(SERIAL_4);
	for(int i=0;i<pList->number;i++)
		pList->listeners[i].received(pList->listeners[i].who,SERIAL_4,tem);
	USART_ClearFlag(UART4, USART_FLAG_RXNE);
}


/*------------------------------------public-------------------------------------*/




void registerUartListener(int uart,UartListener listener){
	ListenerUartList* pList=getListenerUartList(uart);
	if(pList==NULL)
		return ;
	copyUartListener(pList->listeners+pList->number,listener);
	pList->number++;
}







