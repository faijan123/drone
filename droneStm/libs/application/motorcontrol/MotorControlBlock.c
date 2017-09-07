#include "MotorControlBlock.h"
#include "TimerUtil.h"
#define 	ESC_FREQUENCE 		250
#define 	TIMER_CLOCK 			10000000
#define 	ESC_MIN       		1000
#define 	ESC_MAX       		2000
#define  	MOTOR_PERIOD_MAX  20000




uint32_t convertEscControlToCompareVal(float escValue)
{
		return escValue/ESC_MAX*MOTOR_PERIOD_MAX;
}


void initMotorOutGpio(void)
{
		GPIO_InitTypeDef config;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		config.GPIO_Pin 	= GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
		config.GPIO_Mode 	= GPIO_Mode_AF;
		config.GPIO_Speed = GPIO_Speed_100MHz;
		config.GPIO_OType = GPIO_OType_PP;
		config.GPIO_PuPd 	= GPIO_PuPd_UP ;
		GPIO_Init(GPIOE, &config);

		GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, 	GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1); 
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1); 	
	
}



void initMotorTimer(void)
{
	TIM_TimeBaseInitTypeDef timerConfig;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	timerConfig.TIM_Period=39999;
	timerConfig.TIM_Prescaler = 17; 
	timerConfig.TIM_ClockDivision = 0;
	timerConfig.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &timerConfig);
}




void initMotorPwms(void)
{
	TIM_OCInitTypeDef  pwmConfig;
	pwmConfig.TIM_OCMode 			= TIM_OCMode_PWM1;
	pwmConfig.TIM_OutputState = TIM_OutputState_Enable;
	pwmConfig.TIM_Pulse 			= convertEscControlToCompareVal(1000);
	pwmConfig.TIM_OCPolarity 	= TIM_OCPolarity_High;

	TIM_OC1Init(TIM1, &pwmConfig);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM_OC2Init(TIM1, &pwmConfig);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	
	TIM_OC3Init(TIM1, &pwmConfig);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	
	TIM_OC4Init(TIM1, &pwmConfig);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
  TIM_Cmd(TIM1, ENABLE);
}





void initMotorControlBlock(void){
	initMotorOutGpio();
	initMotorTimer();
	initMotorPwms();
}


void updateMotorControlBlock(float esc1,float esc2,float esc3,float esc4){
	
	uint16_t escCompare1,escCompare2,escCompare3,escCompare4;
	escCompare1=convertEscControlToCompareVal(esc1);
	escCompare2=convertEscControlToCompareVal(esc2);
	escCompare3=convertEscControlToCompareVal(esc3);
	escCompare4=convertEscControlToCompareVal(esc4);
	
	TIM_SetCompare1(TIM1,escCompare1);
	TIM_SetCompare2(TIM1,escCompare2);
	TIM_SetCompare3(TIM1,escCompare3);
	TIM_SetCompare4(TIM1,escCompare4);
}

