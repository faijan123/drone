#ifndef FlashWriter_h_
#define FlashWriter_h_
#include "stm32f4xx.h"
int initFlashWriter(void);
int writeToFlash(uint32_t  addr,uint8_t *buffer,int offset,int length);
void closeWriter(void);
#endif
