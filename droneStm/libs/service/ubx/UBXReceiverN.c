#include <String.h>
#include <stdlib.h>
#include "TcTime.h"
#include "Uart.h"
#include "UbxReceiverN.h"


typedef struct UbxReceiverNCache{
	u8 *buffer;
	int size;
	int numberContent;
}UbxReceiverNCache;


typedef struct CacheReader{
	int pointerReader;
	UbxReceiverNCache *cache;
}CacheReader;


UbxReceiverNCache* initCache(int size){
	UbxReceiverNCache *pCache=(UbxReceiverNCache*)malloc(sizeof(UbxReceiverNCache));
	pCache->buffer=(u8*)malloc(size);
	pCache->numberContent=0;
	pCache->size=size;
	return pCache;
}

UbxReceiverNCache* freeCache(UbxReceiverNCache *cache){
	free(cache->buffer);
	free(cache);
	return NULL;
}


void addByteToCache(UbxReceiverNCache *cache,u8 *buffer,int length){
	length=length<(cache->size-cache->numberContent)?length:(cache->size-cache->numberContent);
	if(length==0)
		return ;
	memcpy(cache->buffer+cache->numberContent,buffer,length);
	cache->numberContent+=length;
	
}


void removeByteFromCache(UbxReceiverNCache *cache,int length){
	int remain=cache->numberContent-length;
	
	
	if(length>=cache->numberContent){
		cache->numberContent=0;
		return;
	}
	
	for(int i=length;i<remain;i++)
		cache->buffer[i-length]=cache->buffer[i];
	cache->numberContent-=length;
}

void clearCache(UbxReceiverNCache *cache){
	cache->numberContent=0;
}

void initCacheReader(CacheReader *reader,UbxReceiverNCache *cache){
	reader->cache=cache;
	reader->pointerReader=0;
}

int readerAvailable(CacheReader reader){
	return reader.pointerReader<reader.cache->numberContent;
}


u8 readByte(CacheReader *reader){
	if(!readerAvailable(*reader))
		return 0;
	return reader->cache->buffer[reader->pointerReader++];
}


int readBytes(CacheReader *reader,u8 *buffer,int length){
	int remain=reader->cache->size-reader->pointerReader;
	if(remain<length)
		return 0;
	memcpy(buffer,reader->cache->buffer+reader->pointerReader,length);
	reader->pointerReader+=length;
	return 1;
}

int remain(CacheReader reader){
	return reader.cache->numberContent-reader.pointerReader;
}


int receiveUbxPackageN(void *receiver,UbxPackage *package);
void enableUbxReceiverN(void *receiver);
void disableUbxReceiverN(void *receiver);
int isEnableUbxReceiverN(void *pReceiver);





u32 readByteViaUbxReceiverN(UbxReceiver receiver, u8 *out,u32 timeout){
	return readBytesViaUartWithTimeout(receiver.uart,out,1,timeout);
}





u32 waitUbxSymbols(UbxReceiver receiver,u32 timeout){

	u8 symbol1,symbol2;
	while(timeout){
		symbol1=symbol2=0;
		timeout=readByteViaUbxReceiverN(receiver,&symbol1,timeout);
		if(symbol1!=SYMBOL_1)
			continue;
		timeout=readByteViaUbxReceiverN(receiver,&symbol2,timeout);
		if(symbol2!=SYMBOL_2)
			continue;
		else
			return timeout;
	}

	return timeout;
}


u32 waitUbxHeader(UbxReceiver receiver,UbxHeader *header,u32 timeout){
	u8 buffer[4];
	timeout=readBytesViaUartWithTimeout(receiver.uart,buffer,4,timeout);
	if(!timeout)
		return 0;
	header->_class=buffer[0];
	header->id=buffer[1];
	header->length=buffer[2]|(u16)((buffer[3])<<8);
	return timeout;
}


u32 waitUbxContent(UbxReceiver receiver,u8 *content,int length,u32 timeout){
	return readBytesViaUartWithTimeout(receiver.uart,content,length,timeout);
}


u32 waitUbxChecksum(UbxReceiver receiver,UbxChecksum *checksum,u32 timeout){
	u8 buffer[2];
	timeout=readBytesViaUartWithTimeout(receiver.uart,buffer,2,timeout);
	if(!timeout)
		return 0;
	checksum->ckA=buffer[0];
	checksum->ckB=buffer[1];
	return timeout;
}


void initUbxReceiverN(UbxReceiver *receiver,u32 timeout,int uart){
	receiver->timeout=timeout;
	receiver->uart=uart;
	receiver->enableFlag=0;
	
	receiver->_dis=disableUbxReceiverN;
	receiver->_ena=enableUbxReceiverN;
	receiver->_rec=receiveUbxPackageN;
	receiver->_isEna=isEnableUbxReceiverN;

	receiver->cache=initCache(1024);
}



int readSymbols(CacheReader *reader){
	while(readerAvailable(*reader))
			if(readByte(reader)==SYMBOL_1&&readByte(reader)==SYMBOL_2){
				int lengRemove=reader->pointerReader-2;
				if(lengRemove<=0)
					return 1;
				
				removeByteFromCache(reader->cache,lengRemove);
				reader->pointerReader=2;
				return 1;		
			}
	return 0;
	
}


int readHeader(CacheReader *reader,UbxPackage *package){
	u8 buffer[4];
	if(!readBytes(reader,buffer,4))
		return 0;
	package->header._class=buffer[0];
	package->header.id=buffer[1];
	package->header.length=(u16)buffer[3]<<8|buffer[2];
	return 1;
}


int readContent(CacheReader *reader,UbxPackage *package){
	u8 *tem;
	if(remain(*reader)<package->header.length)
		return 0;
	tem=(u8*)malloc(package->header.length);
	readBytes(reader,tem,package->header.length);
	createUbxPackage(package,package->header,tem);
	free(tem);
	return 1;
}


int readChecksum(CacheReader *reader,UbxChecksum *ck){
	u8 checksum[2];
	if( remain(*reader)<2)
		return 0;
	
	readBytes(reader,checksum,2);
	ck->ckA=checksum[0];
	ck->ckB=checksum[1];
	return 1;
}


void updateUbxReaderN(void *pReceiver){
	UbxReceiver *receiver=castUbxReceiver(pReceiver);
	u8 buffer[30];
	int counter=0;
	u32 timeout=receiver->timeout;
	memset(buffer,0,30);
	while(timeout){
		timeout=readBytesViaUartWithTimeout(receiver->uart,buffer+counter,1,timeout);
		if(timeout)
			counter++;
	}
	addByteToCache((UbxReceiverNCache*)receiver->cache,buffer,counter);	
}




int debugCounter;

int receiveUbxPackageN(void *pReceiver,UbxPackage *package){

	UbxChecksum checksum;
	u8 *content;
	u32 timeout;
	UbxReceiver *receiver=castUbxReceiver(pReceiver);
	timeout=receiver->timeout;
	
	
	
	
	
	
	
	
	
	
	timeout=waitUbxSymbols(*receiver,timeout);
	if(!timeout)
		return 0;

	timeout=waitUbxHeader(*receiver,&package->header,timeout);
	if(!timeout)
		return 0;
	
	if(package->header.length>512)
		return 0;
	
	
	content=(u8*)malloc(package->header.length);
	timeout=waitUbxContent(*receiver,content,package->header.length,timeout);	
	if(!timeout){
		free(content);
		return 0;
	}
	createUbxPackage(package,package->header,content);
	free(content);
	

	timeout=waitUbxChecksum(*receiver,&checksum,timeout);
	if(!timeout){
		deleteUbxPackage(package);
		return 0;
	}
	
	if(!equalUbxChecksum(checksum,package->checksum)){
		deleteUbxPackage(package);
		return 0;
	}


	return 1;



//	UbxReceiver *receiver=castUbxReceiver(pReceiver);
//	UbxChecksum ck;
//	CacheReader reader;
//	static int counterUpdate=0;
//	if(counterUpdate++<10){
//		updateUbxReaderN(receiver);
//		return 0;
//	}
//	
//	initCacheReader(&reader,(UbxReceiverNCache*)receiver->cache);
//	counterUpdate=0;

//	
//	
//	if(!readSymbols(&reader))
//		return 0;

//	if(!readHeader(&reader,package))
//		return 0;
//	
//	if(package->header.length>100){debugCounter++;
//		removeByteFromCache(reader.cache,reader.pointerReader+package->header.length+2);
//		return 0;
//	}
//	
//	if(!readContent(&reader,package))
//		return 0;

//	
//	if(!readChecksum(&reader,&ck)){
//		deleteUbxPackage(package);
//		return 0;
//	}

//	removeByteFromCache(receiver->cache,reader.pointerReader);
//	if(!equalUbxChecksum(package->checksum,ck)){
//		deleteUbxPackage(package);
//		return 0;
//	}
//	return 1;
	

}


void enableUbxReceiverN(void *pReceiver){
	UbxReceiver *receiver=castUbxReceiver(pReceiver);
	enableUart(receiver->uart);
	receiver->enableFlag=1;
	

}
void disableUbxReceiverN(void *pReceiver){
	UbxReceiver *receiver=castUbxReceiver(pReceiver);
	enableUart(receiver->uart);
	receiver->enableFlag=0;
}


int isEnableUbxReceiverN(void *pReceiver){
	UbxReceiver *receiver=castUbxReceiver(pReceiver);
	return receiver->enableFlag;
}
