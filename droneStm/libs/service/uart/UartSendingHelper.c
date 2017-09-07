#include "UartSendingHelper.h"
#include <stdlib.h>
#include <string.h>
#include "UartSender.h"

typedef struct UartSendingHelperCache{
	u8 *buffer;
	int pointer;
	int length;
}UartSendingHelperCache;

typedef struct UartSendingHelperSection{
	UartSendingHelperCache cache;
	u32 timeout;
}UartSendingHelperSection;



void initUartSendingHelperCache(UartSendingHelperCache *cache,u8 *buffer,int length){
	cache->buffer=(u8*)malloc(length);
	cache->pointer=0;
	cache->length=length;
	memcpy(cache->buffer,buffer,length);
}

void initUartSendingHelperSection(UartSendingHelperSection *section,u8 *buffer,int length,u32 timeout){
	section->timeout=timeout;
	initUartSendingHelperCache(&section->cache,buffer,length);
}


void freeUartSendingHelperCache(UartSendingHelperCache *cache){
	free(cache->buffer);		
}

void freeUartSendingHelperSection(UartSendingHelperSection *section){
	free(section->cache.buffer);
	free(section);
}

int debugPointer;

u32 sendOneByteViaUartSendingHelper(UartSendingHelper *sender,u32 timeout){
	u32 remainTime;
	UartSendingHelperCache *cache=&((UartSendingHelperSection*)sender->section)->cache;	
	remainTime=sendByteViaUartWithTimeout(sender->serial,cache->buffer[cache->pointer],timeout);
	debugPointer=cache->pointer++;
	return remainTime;
}


int isDataEndInCacheUartSendingHelper(UartSendingHelper *sender){
	UartSendingHelperCache *cache=&((UartSendingHelperSection*)sender->section)->cache;	
	return cache->pointer==cache->length;
}





void initUartSendingHelper(UartSendingHelper *sender,int serial){
	sender->serial=serial;
	sender->section=NULL;
	sender->state=UartHelperState_Free;

}
void cancelUartSendingHelper(UartSendingHelper *sender){
	if(sender->section!=NULL){
		freeUartSendingHelperSection((UartSendingHelperSection*)sender->section);
		sender->section=NULL;
	}
	sender->state=UartHelperState_Free;
}

UartSendingHelperState getUartSendingHelperState(UartSendingHelper sender){
	return sender.state;
}
void createUartSendingHelperSection(UartSendingHelper *sender,u8 *buffer,int length,u32 timeout){
	sender->section=(UartSendingHelperSection*)malloc(sizeof(UartSendingHelperSection));
	initUartSendingHelperSection((UartSendingHelperSection*)sender->section,buffer,length,timeout);
	sender->state=UartHelperState_Busy;


}
int continueUartSendingHelperSection(UartSendingHelper *sender){
	u32 timeout=((UartSendingHelperSection*)sender->section)->timeout;
	while(timeout&&!isDataEndInCacheUartSendingHelper(sender))
		timeout=sendOneByteViaUartSendingHelper(sender,timeout);
	if( isDataEndInCacheUartSendingHelper(sender)){
		cancelUartSendingHelper(sender);
		return 1;
	}
	else 
		return 0;
}



