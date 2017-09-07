/*
@author:truonglx
@des: implement buffer struct and function.Menory for buffer is dynamic memory.
*/

#include "Buffer.h"
#include <string.h>
#define NUMBE_BYTE_EXPAND 50
#define LIMIT_SIZE_BUFFER 2048


// @expand
int  expandBuffer(Buffer *buffer){
	int sizeExpand=NUMBE_BYTE_EXPAND;
	if(isBufferNull(buffer)||buffer->size>=LIMIT_SIZE_BUFFER)
		return 0;
	
	sizeExpand=sizeExpand<LIMIT_SIZE_BUFFER-buffer->size?sizeExpand:LIMIT_SIZE_BUFFER-buffer->size;
	buffer->data=(uint8_t *)realloc(buffer->data,buffer->size+sizeExpand);
	buffer->size+=sizeExpand;
	return sizeExpand<NUMBE_BYTE_EXPAND?0:1;
}


// @ read
int getNumberEmptyBuffer(Buffer *buffer){
	if(isBufferNull(buffer))
		return -1;
	return buffer->size-buffer->numberByteContent;
}
// @ read 
int isBufferNull(Buffer *buffer){
	return buffer->data==NULL;
}

// @ read 
int findSubArrayInBuffer(Buffer buffer,u8 *element,int length){
	for(int i=0;i<buffer.numberByteContent-length;i++){
		for(int j=0;j<length;j++){
			if(buffer.data[j+i]!=element[j])
				break;
			else if(j==length-1)
				return i;
		}
	}
	return -1;
}

// @ read
int isBufferFull(Buffer buffer){
	if(buffer.numberByteContent>=LIMIT_SIZE_BUFFER)
		return 1;
	return 0;
}	
// @ read and write
int  getBytesFromBuffer(Buffer *buffer,u8 *out,int length){
	if(isBufferNull(buffer))
		return 0;
	length=buffer->numberByteContent<length?buffer->numberByteContent:length;
	memcpy(out,buffer->data,length);
	removeBytesInBuffer(buffer,length);
	return length;
}

// @ read and write

u8  getByteFromBuffer(Buffer *buffer){
	u8 result;
	if(getBytesFromBuffer(buffer,&result,1)<=0)
		return 0;
	return result;
}



// @ write
void 	addBytesToBuffer(Buffer *buffer,u8* values,int length){
	int newNumberContent;
	if(isBufferNull(buffer))
		return ;
	newNumberContent=buffer->numberByteContent+length;
	if(newNumberContent>buffer->size)
		expandBuffer(buffer);
	if(newNumberContent>buffer->size)
		removeBytesInBuffer(buffer,length-getNumberEmptyBuffer(buffer));
	memcpy(buffer->data+buffer->numberByteContent,values,length);
	buffer->numberByteContent=newNumberContent>buffer->size?buffer->size:newNumberContent;
	return ;
}

// @ write
void 	addByteToBuffer(Buffer *buffer,uint8_t data){
	addBytesToBuffer(buffer,&data,1);
}




// @ write
void removeBytesInBuffer(Buffer *buffer,int length){
	int numberByteTrans;
	length=length<(buffer->numberByteContent)?length:(buffer->numberByteContent);
	numberByteTrans=buffer->numberByteContent-length;
	
	for(int i=0;i<numberByteTrans;i++)
		buffer->data[i]=buffer->data[i+length];
	buffer->numberByteContent-=length;
	
}

// @ write
void clearBuffer(Buffer *buffer){
	if(isBufferNull(buffer))
		return ;
	buffer->numberByteContent=0;
}

// @write
void freeBuffer(Buffer *buffer){
	if(!isBufferNull(buffer))
		return ;
	buffer->size=0;
	buffer->numberByteContent=0;
	buffer->data=NULL;
	free(buffer->data);
}

void 	initBuffer(Buffer *buffer,int length){
	length=length>LIMIT_SIZE_BUFFER?LIMIT_SIZE_BUFFER:length;
	buffer->data=(uint8_t*)malloc(length);
	buffer->size=length;
	buffer->numberByteContent=0;
}









