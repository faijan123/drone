#ifndef DroneStore_h_
#define DroneStore_h_
#include "stm32f4xx.h"




void getMagnetOffset(float matrix[3][3],float bias[3]);
void writeAltitudeOffset(float offset);
float getAltitudeOffset(void);
void writeAccelOffset(int16_t *offset);
void writeGyroOffset(int16_t *offset);
void getAccelOffset(int16_t *offset);
void getGyroOffset(int16_t *offset);
#endif
