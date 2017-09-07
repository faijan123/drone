#include "Uart.h"

#include "stm32f4xx_usart.h"


#include "stm32f4xx_rcc.h"

#include "stm32f4xx_gpio.h"

#include <string.h>


USART_TypeDef* uart_getUartTypeDef(int uartName){

	if(uartName == TC_UART_4)
		return UART4;
	
	if(uartName == TC_USART_6)
		return USART6;
	
	return NULL;
}


// @private function
void uart_init4(uint32_t baudrate);

// @private function
void uart_init6(uint32_t baudrate);



void uart_init(int uartName,int baudrate){
	
	if(uartName==TC_UART_4)
		uart_init4(baudrate);
	
	else if(uartName==TC_USART_6)
		uart_init6(baudrate);
}

void uart_free(int uartName){

}

void uart_send(int uartName,uint8_t val){
	
	uart_sendBytes(uartName,&val,1);
}

void uart_sendBytes(int uartName,uint8_t *buffer,int length){
	
	USART_TypeDef *pUart=uart_getUartTypeDef(uartName);
	if(pUart==NULL)
		return ;
	for(int i=0;i<length;i++){
		USART_SendData(pUart,buffer[i]);
		while (USART_GetFlagStatus(pUart, USART_FLAG_TC) == RESET);
	}
		
}

void uart_enable(int uartName){

	USART_TypeDef *pUart=uart_getUartTypeDef(uartName);
	if(pUart!=NULL)
		USART_Cmd(pUart,ENABLE);
}

void uart_disable(int uartName){
	
	USART_TypeDef *pUart=uart_getUartTypeDef(uartName);
	if(pUart!=NULL)
		USART_Cmd(pUart,DISABLE);
}


void uart_enableNVIC(int uartName){

}

void uart_disableNVIC(int uartName){

}

void uart_setCallback(int uartName,uart_Callback cb,void *data){


}

uint8_t uart_readByte(int uartName,uint32_t timeout){

}

int uart_readBytes(int uartName,uint32_t timeout,uint8_t *buffer,int length){

		
}




/*-----------------------------------------------------------*/

void uart_init4(uint32_t baudrate){

	GPIO_InitTypeDef gpioConfig;
	USART_InitTypeDef uartConfig;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 

	gpioConfig.GPIO_OType 	= GPIO_OType_PP;
	gpioConfig.GPIO_PuPd 	= GPIO_PuPd_UP;
	gpioConfig.GPIO_Mode 	= GPIO_Mode_AF;
	gpioConfig.GPIO_Pin 		= GPIO_Pin_0|GPIO_Pin_1;
	gpioConfig.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &gpioConfig);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	uartConfig.USART_BaudRate 					= baudrate;
	uartConfig.USART_WordLength 				= USART_WordLength_8b;
	uartConfig.USART_StopBits 					= USART_StopBits_1;
	uartConfig.USART_Parity 					= USART_Parity_No;
	uartConfig.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;
	uartConfig.USART_Mode 						= USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4,&uartConfig);
}

void uart_init6(uint32_t baudrate){

	GPIO_InitTypeDef gpioConfig;
	USART_InitTypeDef uartConfig;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 

	gpioConfig.GPIO_OType 	= 	GPIO_OType_PP;
	gpioConfig.GPIO_PuPd 	= 	GPIO_PuPd_UP;
	gpioConfig.GPIO_Mode 	= 	GPIO_Mode_AF;
	gpioConfig.GPIO_Pin 		= 	GPIO_Pin_6|GPIO_Pin_7;
	gpioConfig.GPIO_Speed 	=	GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &gpioConfig);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	uartConfig.USART_BaudRate 					= baudrate;
	uartConfig.USART_WordLength 				= USART_WordLength_8b;
	uartConfig.USART_StopBits 					= USART_StopBits_1;
	uartConfig.USART_Parity 					= USART_Parity_No;
	uartConfig.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;
	uartConfig.USART_Mode 						= USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART6,&uartConfig);
}
