//#include "PinStateReader.h"
//#include "stm32f4xx.h"
//#include "Delay.h"


//void configClockPinStateReader(void){
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
//}
//void initGeneralAdcPinStateReader(void){
//	ADC_InitTypeDef adcConfig; 
//	ADC_CommonInitTypeDef ADC_CommonInitStructure;
//	
//	
//	
//	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
//	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
//	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
//	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
//	ADC_CommonInit(&ADC_CommonInitStructure);
//	
//	
//	
//	adcConfig.ADC_Resolution = ADC_Resolution_12b;
//	adcConfig.ADC_ScanConvMode= DISABLE;
//	adcConfig.ADC_ContinuousConvMode = DISABLE;
//	adcConfig.ADC_ExternalTrigConv=ADC_ExternalTrigConvEdge_None;
//	adcConfig.ADC_DataAlign = ADC_DataAlign_Right;
//	adcConfig.ADC_NbrOfConversion = 1;
//	ADC_Init(ADC1, &adcConfig);


//	
//}




//void configGpioPinStateReader(){
//	GPIO_InitTypeDef config;
//	config.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_2;
//	config.GPIO_Mode = GPIO_Mode_AIN;
//	config.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &config);
//}








//void initPinStateReader(void){
//	configClockPinStateReader();
//	initGeneralAdcPinStateReader();
//	configGpioPinStateReader();
//}

//uint16_t readI(void){
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_144Cycles);
//	ADC_Cmd(ADC1, ENABLE);
//	ADC_TempSensorVrefintCmd(ENABLE);
//	ADC_SoftwareStartConv(ADC1);
//	delayMilis(500);
//	return ADC_GetConversionValue(ADC1);
//}

//uint16_t readU(void){
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_144Cycles);
//	ADC_Cmd(ADC1, ENABLE);
//	ADC_TempSensorVrefintCmd(ENABLE);
//	ADC_SoftwareStartConv(ADC1);
//	return ADC_GetConversionValue(ADC1);
//}


//void enablePinStateReader(void){

//}
//	
//void disablePinStateReader(void){

//}
//	
//	
