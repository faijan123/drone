#ifndef SBUSPARSER_H_
#define SBUSPARSER_H_

#include "stm32f4xx.h"

void sbusParser_update(uint8_t val);

void sbusParser_reset();

int  sbusParser_hasNewData();

int  sbusParser_readData();

#endif
