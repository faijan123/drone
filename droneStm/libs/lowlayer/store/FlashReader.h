#ifndef FlashReader_h_
#define FlashReader_h_
#include "stm32f4xx.h"

int 	initFlashReader(void);
int 	readFromFlash(uint32_t addr,uint8_t *buffer,int offset,int length);
void 	closeReader(void);
#endif
