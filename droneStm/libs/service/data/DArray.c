
#include "Array.h"
#include <string.h>
#include <stdlib.h>

int isArrayNULL(DArray array){
	return array.size==0||array.data==NULL;
}

DArray createArray(int size){
	DArray res;
	res.size=size;
	res.data=malloc(size);
	return res;
}
void deleteDArray(DArray *array){
	if(isArrayNULL(*array))
		return ;
	free(array->data);
	array->data=NULL;
	array->size=0;
}

void getDataFromDArray(DArray *array,int offset,int length,void *buffer){
	if(isArrayNULL(*array))
		return ;
	length=array->size>length?length:array->size;
	//memcpy(array->data+offset,buffer,length);
}

void setDataToDArrayD(DArray *array,int offset,void *buffer,int length){
	if(isArrayNULL(*array))
		return ;
	//memcpy(array->data+offset,buffer,length);
}
