#include "Gpio.h"



uint32_t getClock(GPIO_TypeDef*  GPIOx)
{
		if(GPIOx==GPIOA)
			return RCC_AHB1Periph_GPIOA;
		if(GPIOx==GPIOB)
			return RCC_AHB1Periph_GPIOB;
		if(GPIOx==GPIOC)
			return RCC_AHB1Periph_GPIOC;
		if(GPIOx==GPIOD)
			return RCC_AHB1Periph_GPIOD;
		if(GPIOx==GPIOE)
			return RCC_AHB1Periph_GPIOE;
		if(GPIOx==GPIOF)
			return RCC_AHB1Periph_GPIOF;
		if(GPIOx==GPIOG)
			return RCC_AHB1Periph_GPIOG;
		if(GPIOx==GPIOH)
			return RCC_AHB1Periph_GPIOH;
		if(GPIOx==GPIOI)
			return RCC_AHB1Periph_GPIOI;
		if(GPIOx==GPIOJ)
			return RCC_AHB1Periph_GPIOJ;
		if(GPIOx==GPIOK)
			return RCC_AHB1Periph_GPIOK;
		return 0;
	
}

void initGPIO(GPIO_TypeDef *gpio,int pin,GPIOMode_TypeDef mode,GPIOOType_TypeDef type,GPIOSpeed_TypeDef speed,GPIOPuPd_TypeDef puPd)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(getClock(gpio), ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= mode;
	GPIO_InitStructure.GPIO_OType = type;
	GPIO_InitStructure.GPIO_Speed = speed;
	GPIO_InitStructure.GPIO_PuPd 	= puPd;
	GPIO_Init(gpio, &GPIO_InitStructure);
}



