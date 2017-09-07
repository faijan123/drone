#include <string.h>
#include "ArrayUtil.h"

void resetFloatArray(float *array,int n,float defaultValue){
	for(int i=0;i<n;i++)
		array[i]=defaultValue;
}
void copyFloatArray(float *des,float *src,int length){
	for(int i=0;i<length;i++)
		des[i]=src[i];
}

void copyInt16_tArray(int16_t *des,int16_t *src,int length){
	for(int i=0;i<length;i++)
		des[i]=src[i];
}


void scaleInt16_tArrayToFloatArray(int16_t *in,float gain,int length,float *out){
	for(int i=0;i<length;i++)
		out[i]=in[i]*gain;
}


void scaleFloatArray(float *in,float gain,int length,float *out){
	for(int i=0;i<length;i++)
		out[i]=in[i]*gain;
}

void scaleLongArrayToFloatArray(long *in,float gain,int length,float *out){
	for(int i=0;i<length;i++)
		out[i]=in[i]*gain;
}







void subFloatArray(float *subtrahend,float *minus,int n,float *result){
	for(int i=0;i<n;i++)
		result[i]=subtrahend[i]-minus[i];
}
void subInt16_rArray(int16_t *a,int16_t *b,int n,int16_t *c){
	for(int i=0;i<n;i++)
		c[i]=b[i]-a[i];
}



void addFloatArray(float *a,float *b,int length,float *res){
	for(int i=0;i<length;i++)
		res[i]=a[i]+b[i];
}


void addInt16_tArray(int16_t *a,int16_t *b,int length,long *res){
	for(int i=0;i<length;i++)
		res[i]=a[i]+b[i];
}

void getBytesFromInt16_tArray(int16_t *in,uint8_t *out,int length){
	for(int i=0;i<length;i++){
		out[i]=(uint8_t)(in[i]>>8);
		out[i+1]=(uint8_t)in[i];
	}
}


void wrapBytesToInt16_tArray(uint8_t *in,int16_t *out,int length){
	for(int i=0;i<length/2;i++){
		out[i]=in[i*2];
		out[i]<<=8;
		out[i]|=in[i*2+1];
	}
}


void copyData(void* des,void* source,int length,int type){
	if(type){
		memcpy(des,source,length);
		return;
	}
	for(int i=0;i<length;i++)
		memcpy((u8*)des+length-1-i,(u8*)source+i,1);
}
