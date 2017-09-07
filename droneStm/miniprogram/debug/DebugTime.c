#include "stm32f4xx_gpio.h"
#include "DebugTime.h"
#include "TimeChecker.h"

#define DEBUG_TIME_PIN 		GPIO_Pin_14
#define DEBUG_TIME_CYCLE  4000

DeltaTimeChecker debugTimeChecker;


void initDebugGpio(void){
	GPIO_InitTypeDef config;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	config.GPIO_Pin=DEBUG_TIME_PIN;
	config.GPIO_Mode=GPIO_Mode_OUT;
	config.GPIO_OType=GPIO_OType_PP;
	config.GPIO_PuPd = GPIO_PuPd_DOWN;
	config.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &config);
}
void initDebugTime(void){
	initDebugGpio();
	initDeltaTimeChecker(&debugTimeChecker,DEBUG_TIME_CYCLE);
}
void startDebugTime(void){
	while(1){
		while(!checkDeltaTimeChecker(&debugTimeChecker));
		GPIO_ToggleBits(GPIOE,DEBUG_TIME_PIN);
	}
}

void updateDebugTime(void){
	GPIO_ToggleBits(GPIOE,DEBUG_TIME_PIN);
}
void stopDebugTime(void){

}


