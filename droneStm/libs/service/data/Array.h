#include "stm32f4xx.h"
#ifndef Array_h_
#define Array_h_
typedef struct DArray{
	int 	size;
	void 	*data;
}DArray;
int isArrayNULL(DArray array);
DArray createArray(int size);
void deleteDArray(DArray *array);
void getDataFromDArray(DArray *array,int offset,int length,void *buffer);
void setDataToDArrayD(DArray *array,int offset,void *buffer,int length);
#endif
