#ifndef SystemTick_h_
#define SystemTick_h_
#include "stm32f4xx.h"
typedef struct SystemTickSubcriber{
	uint32_t 	current;
	int 			unit;
	uint8_t 	available;
}SystemTickSubcriber;

void registerSystemTickSubcriber(SystemTickSubcriber *subcriber);
void disableSystemTickSubcriber(SystemTickSubcriber *subcriber);
void enableSystemTichSubcriber(SystemTickSubcriber *subcriber);
#endif
