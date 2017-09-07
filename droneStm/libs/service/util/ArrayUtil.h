/*

@author: truonglx
@des: util function for process  with array
*/

#ifndef ArrayUtil_h_
#define ArrayUtil_h_

#include "stm32f4xx.h"
#define COPY_BIG_ENDIAN 0
#define COPY_LITLE_EDIAN 1
void resetFloatArray(float *array,int n,float defaultValue);

void copyFloatArray(float *des,float *src,int length);
void copyInt16_tArray(int16_t *des,int16_t *src,int length);

void scaleFloatArray(float *in,float gain,int length,float *out);
void scaleLongArrayToFloatArray(long *in,float gain,int length,float *out);
void scaleInt16_tArrayToFloatArray(int16_t *in,float gain,int length,float *out);

void addFloatArray(float *a,float *b,int length,float *res);
void addInt16_tArray(int16_t *a,int16_t *b,int length,long *res);

void subInt16_tArray(int16_t *a,int16_t *b,int n,int16_t *c);
void subFloatArray(float *subtrahend,float *minus,int n,float *result);


void getBytesFromInt16_tArray(int16_t *in,uint8_t *out,int length);
void wrapBytesToInt16_tArray(uint8_t *in,int16_t *out,int length);



void copyData(void* des,void *source,int length,int type);
#endif
