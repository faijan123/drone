#ifndef SBusReader_h_
#define SBusReader_h_
#include "stm32f4xx.h"

typedef struct SBusData
{
	uint16_t channel1;
	uint16_t channel2;
	uint16_t channel3;
	uint16_t channel4;
	uint16_t channel5;
	uint16_t channel6;
	uint16_t channel7;
	uint16_t channel8;
	uint16_t channel9;
	uint16_t channel10;
	uint16_t channel11;
	uint16_t channel12;
	uint16_t channel13;
	uint16_t channel14;
	uint16_t channel15;
	uint16_t channel16;
}SBusData;

int 			readDataViaSBus(SBusData *res);
void 			initSBusReader(void);
void			disableSBusReader(void);
void 			enableSBusReader(void);

#endif

