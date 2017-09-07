#include <stdlib.h>
#include <string.h>
#include "UbxReceiverI.h"
#include "Uart.h"
#include "UartHandler.h"
#include "Delay.h"


int receiveUbxPackageI(void *pReceiver,UbxPackage *package);
void enableUbxReceiverI(void *pReceiver);
void disableUbxReceiverI(void *pReceiver);
int isEnableUbxReceiverI(void *pReceiver);



typedef struct UbxReceiverHandlerState{
	u8 prevByte;
	int counterSysbol;
}UbxReceiverHandlerState;


UbxReceiverHandlerState* getUbxReceiverHandlerState(UbxReceiver receiver){
	return (UbxReceiverHandlerState*)receiver.cache;
}


void resetHandlerState(UbxReceiver receiver){
	UbxReceiverHandlerState *handlerState=getUbxReceiverHandlerState(receiver);
	handlerState->prevByte=0;
	handlerState->counterSysbol=0;
}

/*--------------------------------------------------ubx handler------------------------------------------------------------------*/

// @ listener interrupt in channel.
void ubxReceiverHandler(void *pReceiver,int uart,u8 byte){
	UbxReceiverHandlerState *handlerState=(UbxReceiverHandlerState*)pReceiver;
	if(handlerState->prevByte==SYMBOL_1&&byte==SYMBOL_2)
		handlerState->counterSysbol++;
	handlerState->prevByte=byte;
	return ;
}

// @ bind receiver to handler.
void registerHandler(int uart,UbxReceiverHandlerState *handler){
	UartListener listener;
	listener.who=(void*)handler;
	listener.received=ubxReceiverHandler;
	registerUartListener(uart,listener);
}

/*----------------adapter with ubx and uart--------------------------*/

// @ test
int getNumberByteInBufferOfUBXChannel(UbxReceiver receiver){
	return getNumberByteInBufferOfUart(receiver.uart);
}
//	@ test
int isDataInUbxChannelReadlly(UbxReceiver receiver){
	return isDataInBufferOfUartReadlly(receiver.uart);
}

//@ operation
void removeByteFromeBufferOfUBXChannel(UbxReceiver receiver,int length){
	removeBytesInBufferOfUart(receiver.uart,length);
}

//@ operation
u8 readByteViaUBX(UbxReceiver receiver){
	while(!isDataInUbxChannelReadlly(receiver)){};
	return readByteBufferOfUart(receiver.uart);
}

//@ operation
int readBytesViaUBX(UbxReceiver receiver,u8 *buffer,u16 length){
	if(getNumberByteInBufferOfUBXChannel(receiver)<length)
		return -1;
	return readBytesBufferOfUart(receiver.uart,buffer,length);
}

//@ operation
void freeUBXReceiverBuffer(UbxReceiver receiver){
	clearBufferOfUart(receiver.uart);
}


/*---------------------------------------ubx protocol----------------------------------------------------------------*/


//@ ubx protocol
int findUBXSymbol(UbxReceiver receiver){
	static u8 head[]={SYMBOL_1,SYMBOL_2};
	int res=findSubArrayInBufferOffUart(receiver.uart,head,2);
	if(res>=0)
		removeByteFromeBufferOfUBXChannel(receiver,res+2);
	return res;
}

//@ ubx protocol
int readUbxHeader(UbxReceiver receiver,UbxHeader *header){
	static u8 specRaw[4];
	if(getNumberByteInBufferOfUBXChannel(receiver)<4)
		return -1;

	readBytesViaUBX(receiver,specRaw,4);
	header->_class=specRaw[0];
	header->id=specRaw[1];
	header->length=specRaw[2]|((u16)specRaw[3]<<8);
	return 1;
}

//@ ubx protocol

int readUbxContent(UbxReceiver receiver,u8 **buffer,int length){
	if(getNumberByteInBufferOfUBXChannel(receiver)<length)
		return -1;
	*buffer=(u8*)malloc(length);
	readBytesViaUBX(receiver,*buffer,length);
	return 1;
}

//@ ubx protocol
int readCheckSum(UbxReceiver receiver,UbxChecksum *checksum){
	if(getNumberByteInBufferOfUBXChannel(receiver)<2)
		return -1;
	checksum->ckA=readByteViaUBX(receiver);
	checksum->ckB=readByteViaUBX(receiver);
	return 1;
}

/*-------------------------------------filter-------------------------------------*/

int forwardFilter(UbxReceiver *receiver,UbxHeader header){

	return 1;
}




/*-----------------------------------util--------------------------------------------------*/




void endSection(UbxReceiver *receiver){
	UbxReceiverHandlerState *handlerState=getUbxReceiverHandlerState(*receiver);
	if(handlerState->counterSysbol>=2)
		handlerState->counterSysbol--;
}


void startSection(UbxReceiver receiver){
	//disableUart(receiver.uart);	
}


void resetUbxReceiver(UbxReceiver *receiver){
	clearBufferOfUart(receiver->uart);
	resetHandlerState(*receiver);
}


/*-------------------------------------public--------------------------------------*/

void initUbxReceiverI(UbxReceiver *receiver ,int uart){
	receiver->uart=uart;
	receiver->cache=(UbxReceiverHandlerState*)malloc(sizeof(UbxReceiverHandlerState));
	registerHandler(uart,getUbxReceiverHandlerState(*receiver));
	
	
	receiver->_dis=disableUbxReceiverI;
	receiver->_ena=enableUbxReceiverI;
	receiver->_rec=receiveUbxPackageI;
	receiver->_isEna=isEnableUbxReceiverI;
	
}



int receiveUbxPackageI(void *pReceiver,UbxPackage *package){
	
	 u8* buffer;
	 UbxChecksum checksumPackage;
	 int posBeginPackage;
	 UbxReceiver *receiver=castUbxReceiver(pReceiver);

	
	
	startSection(*receiver);
	if(getUbxReceiverHandlerState(*receiver)->counterSysbol<2){
		endSection(receiver);
		return 0;
	}
	
	
	posBeginPackage=findUBXSymbol(*receiver);
	if(posBeginPackage==-1){
		resetUbxReceiver(receiver);
		endSection(receiver);
		return 0;
	}
	
	if(readUbxHeader(*receiver,&package->header)==-1){
		resetUbxReceiver(receiver);
		endSection(receiver);
		return 0;
	}



	
	if(readUbxContent(*receiver,&buffer,package->header.length)==-1){
		endSection(receiver);
		return 0;
	} 

	
	
	if(readCheckSum(*receiver,&checksumPackage)==-1){
		free(buffer);
		endSection(receiver);
		return 0;
	}
	
	createUbxPackage(package,package->header,buffer);
	free(buffer);
	endSection(receiver);
	if(!equalUbxChecksum(checksumPackage,package->checksum)){
		deleteUbxPackage(package);
		return 0;
	}
	return 1;
}



void enableUbxReceiverI(void *pReceiver){
	
	UbxReceiver *receiver=castUbxReceiver(pReceiver);
	enableUart(receiver->uart);
	receiver->enableFlag=1;
}
void disableUbxReceiverI(void *pReceiver){
	UbxReceiver *receiver=castUbxReceiver(pReceiver);
	disableUart(receiver->uart);
	receiver->enableFlag=0;
}

int isEnableUbxReceiverI(void *pReceiver){
	UbxReceiver *receiver=castUbxReceiver(pReceiver);
	return receiver->enableFlag;
}
