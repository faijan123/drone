#include "UartControl.h"
#include "UartConst.h"
#include "UartFinder.h"

void configUart4(uint32_t baudrate){
	GPIO_InitTypeDef gpioConfig;
	USART_InitTypeDef uartConfig;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 

	gpioConfig.GPIO_OType = GPIO_OType_PP;
	gpioConfig.GPIO_PuPd = GPIO_PuPd_UP;
	gpioConfig.GPIO_Mode = GPIO_Mode_AF;
	gpioConfig.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	gpioConfig.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &gpioConfig);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	uartConfig.USART_BaudRate = baudrate;
	uartConfig.USART_WordLength = USART_WordLength_8b;
	uartConfig.USART_StopBits = USART_StopBits_1;
	uartConfig.USART_Parity = USART_Parity_No;
	uartConfig.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uartConfig.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4,&uartConfig);
}


void configUart6(uint32_t baudrate){
	GPIO_InitTypeDef gpioConfig;
	USART_InitTypeDef uartConfig;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 

	gpioConfig.GPIO_OType = GPIO_OType_PP;
	gpioConfig.GPIO_PuPd = GPIO_PuPd_UP;
	gpioConfig.GPIO_Mode = GPIO_Mode_AF;
	gpioConfig.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	gpioConfig.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &gpioConfig);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	uartConfig.USART_BaudRate = baudrate;
	uartConfig.USART_WordLength = USART_WordLength_8b;
	uartConfig.USART_StopBits = USART_StopBits_1;
	uartConfig.USART_Parity = USART_Parity_No;
	uartConfig.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uartConfig.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART6,&uartConfig);
}

void configUart7(uint32_t baudrate){

}



/*-------------------------------------------------------public----------------------------------------------------------------------------*/

void initUart4(u32 baudrate){
	static int initUart4Flag=0;
	if(initUart4Flag)
		return ;
	initUart4Flag=1;
	configUart4(baudrate);
	USART_Cmd(UART4, ENABLE);	
}



void initUart6(u32 baudrate){
	static int initFlag=0;
	if(initFlag)
		return;
	initFlag=1;
	USART_Cmd(USART6, ENABLE);	
}

void initUart7(u32 baudrate){

}




void initUartWithNVIC(int uart,int baudrate,int size){
	if(uart==SERIAL_4)
		initUart4NVIC(baudrate,size);
	else if(uart==SERIAL_6)
		initUart6NVIC(baudrate,size);
}


void enableUart4(){
	USART_Cmd(UART4, ENABLE);
}

void enableUart6(){
	USART_Cmd(USART6, ENABLE);
}

void enableUart(int uart){
	USART_TypeDef *pUart=findUSARTPointer(uart);
	USART_Cmd(pUart,ENABLE);
}

void disableUart4(){
	USART_Cmd(UART4, DISABLE);
}
void disableUart6(){
	USART_Cmd(USART6, DISABLE);
}

void disableUart(int uart){
	USART_TypeDef *pUart=findUSARTPointer(uart);
	USART_Cmd(pUart,DISABLE);
}


