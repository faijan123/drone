#include "TimerUtil.h"

uint16_t calPrescalerValue(uint32_t frequence)
{
		return (uint16_t) ((SystemCoreClock / 2) / frequence) - 1;
}

uint32_t calPeriod(uint32_t freqTimer,uint32_t freqPwm)
{
		return freqTimer/freqPwm;
}


