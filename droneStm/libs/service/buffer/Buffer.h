/*
@author:truonglx
*/
#ifndef Buffer_h_
#define Buffer_h_
#include "stm32f4xx.h"
#include <stdlib.h>

#define MIN_SIZE_BUFFER 50

typedef struct Buffer{
	uint8_t *data;
	int size;
	int numberByteContent;
}Buffer;




void removeBytesInBuffer(Buffer *buffer ,int length);
void freeBuffer(Buffer *buffer);
void initBuffer(Buffer *buffer,int length);
void addBytesToBuffer(Buffer *buffer,uint8_t* values,int length);
void addByteToBuffer(Buffer *buffer,uint8_t value);
int getBytesFromBuffer(Buffer *buffer,uint8_t *value,int length);
u8 getByteFromBuffer(Buffer *buffer);
void clearBuffer(Buffer *buffer);
void freeBuffer(Buffer *buffer);
int  getNumberByteContent(Buffer *buffer);
int isBufferNull(Buffer *buffer);
int findSubArrayInBuffer(Buffer buffer,u8 *element,int length);
int isBufferFull(Buffer buffer);
#endif
