#ifndef Mapper_h_
#define Mapper_h_
#include "stm32f4xx.h"


uint16_t mapUint16ToUint16(uint16_t sourceValue,uint16_t lowSource,uint16_t hightSource,uint16_t lowDes,uint16_t hightDes);
float mapUint16ToFloat(uint16_t sourceValue,uint16_t lowSource,uint16_t hightSource,float lowDes,float hightDes);

#endif
