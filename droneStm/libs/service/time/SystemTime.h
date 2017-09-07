#ifndef MTIME_H_
#define MTIME_H_



#include "stm32f4xx.h"



#define TIME_SENSI_MIL 0

#define TIME_SENSI_MIC 1




void time_init(int timeSensi);

uint32_t time_getMicros(void);

uint32_t time_getMillis(void);

uint32_t time_calDeltaTime(uint32_t after,uint32_t before);

uint32_t time_calDeltaTimeBySensi(uint32_t after,uint32_t before,int sensi);

#endif
