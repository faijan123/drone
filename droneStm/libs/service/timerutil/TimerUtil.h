#ifndef TimerUtil_h_
#define TimerUtil_h_
#include "stm32f4xx.h"
uint16_t calPrescalerValue(uint32_t frequence);
uint32_t calPeriod(uint32_t timerFreq,uint32_t outFrea);
#endif
