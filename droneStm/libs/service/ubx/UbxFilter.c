#include "UbxFilter.h"
#include <stdlib.h>
#include <string.h>
#define EXPAND_FILTER_SIZE 5
#define BEGIN_FILTER_SIZE  10

int getPosition(UBXFilter filter,UbxHeader header){
	for(int i=0;i<filter.numberSpec;i++)
		if(equalUbxHeader(filter.headers[i],header))
			return i;
	return -1;
}

void expandUBXFilter(UBXFilter *filter){
	filter->sizeFilter+=EXPAND_FILTER_SIZE;
	filter->headers=(UbxHeader*)realloc(filter->headers,filter->sizeFilter*sizeof(UbxHeader));
}

void initUBXFilter(UBXFilter *filter){
	filter->headers=(UbxHeader*)malloc(sizeof(UbxHeader)*BEGIN_FILTER_SIZE);
	filter->sizeFilter=BEGIN_FILTER_SIZE;
	filter->numberSpec=0;
}

void addUBXSpec(UBXFilter *filter,UbxHeader header){
	if(filter->numberSpec==filter->sizeFilter)
		expandUBXFilter(filter);
	filter->headers[filter->numberSpec++]=header;
	
}

void removeUBXSpec(UBXFilter *filter,UbxHeader header){
	int pos=getPosition(*filter,header);
	if(pos<0)
		return ;
	if(pos==filter->numberSpec-1){
		filter->numberSpec--;
		return ;
	}
	else{
		filter->headers[pos]=filter->headers[--filter->numberSpec];
		return ;
	}
}
int passPackage(UBXFilter filter,UbxHeader spec){
	return getPosition(filter,spec)>=0;
}

void copyFilter(UBXFilter *des,UBXFilter *source){
	if(source->sizeFilter==0)
		return ;
	if(des->sizeFilter)
		deleteUBXFilter(des);
	des->enableFlag=1;
	des->numberSpec=source->numberSpec;
	des->sizeFilter=source->sizeFilter;
	des->headers=(UbxHeader*)malloc(source->sizeFilter*sizeof(UbxHeader));
	memcpy(des->headers,source->headers,sizeof(UbxHeader)*source->numberSpec);
}


void deleteUBXFilter(UBXFilter *filter){
	filter->enableFlag=0;
	free(filter->headers);
	filter->numberSpec=0;
	filter->sizeFilter=0;
}

int isEnableUBXFilter(UBXFilter filter){
	return filter.enableFlag;
}

void enableUBXFilter(UBXFilter *filter){
	filter->enableFlag=1;
}
void disableUBXFilter(UBXFilter *filter){
	filter->enableFlag=0;
}



