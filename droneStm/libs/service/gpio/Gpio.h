#ifndef Gpio_h_
#define Gpio_h_
#include "stm32f4xx_gpio.h"
#define setPinHight(GPIOx, GPIO_Pin) 		((GPIOx)->BSRRL = (GPIO_Pin))
#define setPinLow(GPIOx, GPIO_Pin)			((GPIOx)->BSRRH = (GPIO_Pin))
void initGPIO(GPIO_TypeDef *gpio,int pin,GPIOMode_TypeDef mode,GPIOOType_TypeDef type,GPIOSpeed_TypeDef speed,GPIOPuPd_TypeDef puPd);
#endif
