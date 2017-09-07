#include "UbxSender.h"
#include <stdlib.h>
#include "Uart.h"



void freeUbxIo(UBXSender *sender){
	cancelUartSendingHelper((UartSendingHelper*)sender->io);
	free(sender->io);
	sender->io=NULL;
}


void initUbxIo(UBXSender *sender,u8 *buffer,int length,u32 timeout){
	UartSendingHelper *tHelper=(UartSendingHelper*)malloc(sizeof(UartSendingHelper));
	initUartSendingHelper(tHelper,sender->serial);
	createUartSendingHelperSection(tHelper,buffer,length,timeout);
	sender->io=tHelper;
	return ;
}



void initUbxSender(UBXSender *sender,int serial){
	sender->serial=serial;
	sender->state=Free;	
}


void cancelUbxSender(UBXSender *sender){
	
	if(sender->io!=NULL){
		freeUbxIo(sender);
		sender->io=NULL;
	}
	sender->state=Free;
}


UBXSenderState getUbxSenderState(UBXSender *sender){
	return sender->state;
}


void createUbxSenderSection(UBXSender *sender,UbxPackage package,u32 timeout){
	
	
	u8 *buffer;
	buffer=(u8*)malloc(getSizeUbxPackage(package));
	if(sender->io!=NULL)
		cancelUbxSender(sender);
	ubxPackageToBytes(package,buffer);
	initUbxIo(sender,buffer,getSizeUbxPackage(package),timeout);
	free(buffer);
	sender->state=Busy;
}




int continueUbxSenderSection(UBXSender *sender){
	int res=continueUartSendingHelperSection((UartSendingHelper*)sender->io);
	if(res)
		cancelUbxSender(sender);
	return res;
}


int sendUbxPackage(UBXSender *sender,UbxPackage package){
	
	if(sender->state!=Free)
		cancelUbxSender(sender);
	createUbxSenderSection(sender,package,100000);
	while(!continueUbxSenderSection(sender));
	deleteUbxPackage(&package);
	return 1;

}
