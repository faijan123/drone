#include "SystemTime.h"

#include "stm32f4xx_tim.h"

#include "stm32f4xx_rcc.h"



#define TIME_TIM 			TIM2

int time_sensi;



typedef struct TimeConfig{
	
	int timeSensi;
	int timeMax;
}TimeConfig;

TimeConfig time_config;



void time_init(int timeSensi){
	
	TIM_TimeBaseInitTypeDef  timeConfig;
	
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN,ENABLE);
	
	time_config.timeSensi=timeSensi;
	time_config.timeMax=(timeSensi==TIME_SENSI_MIL)?(1000-1):(1000000-1);
	timeConfig.TIM_Prescaler		=	((SystemCoreClock)/2/(timeSensi==TIME_SENSI_MIL?1000:1000000))-1;
	timeConfig.TIM_ClockDivision	=	0;
	timeConfig.TIM_CounterMode		=	TIM_CounterMode_Up;
	timeConfig.TIM_Period			=	time_config.timeMax;
	
	TIM_TimeBaseInit(TIME_TIM,&timeConfig);
	TIM_Cmd(TIME_TIM, ENABLE);
	
	
}

uint32_t time_getMicros(void){

	if(time_sensi==TIME_SENSI_MIL)
		return time_getMillis()*1000;
	else
		TIM_GetCounter(TIME_TIM);
}

uint32_t time_getMillis(void){
	
	if(time_sensi==TIME_SENSI_MIL)
		return TIM_GetCounter(TIME_TIM);
	return TIM_GetCounter(TIME_TIM)/1000;
}


uint32_t time_calDeltaTime(uint32_t after,uint32_t before){

	if(after<=before)
		return after-before+time_config.timeMax;
	return after-before;
	
}


uint32_t time_calDeltaTimeBySensi(uint32_t after,uint32_t before,int sensi){

	if(after<=before){
	
		if(sensi==TIME_SENSI_MIC)
			return after-before+1000000;
		return after-before+1000;
	}
	return after-before;
}
