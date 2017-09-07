#include "stm32f4xx.h"
#include "TimerUtil.h"

void initTimer1(uint32_t frequenceTimer,uint32_t period)
{
	TIM_TimeBaseInitTypeDef timerConfig;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	timerConfig.TIM_Prescaler=calPrescalerValue(frequenceTimer);
	timerConfig.TIM_CounterMode=TIM_CounterMode_Up;
	timerConfig.TIM_Period=period;
	timerConfig.TIM_ClockDivision = TIM_CKD_DIV1;
	timerConfig.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&timerConfig);
}

