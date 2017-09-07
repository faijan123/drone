#include "Ublox.h"
#include "UbloxParser.h"
#include <string.h>
#include "UBXReceiver.h"
#include "UBXSender.h"
#include "UBloxConfig.h"
#include <stdlib.h>




float dlat,dlon;
int dcounter;


typedef struct UbloxTransport{
	UBXSender sender;
	UbxReceiver receiver;
}UbloxTransport;



UbxReceiver* getUbxReceiverPointer(Ublox ublox){
	return &((UbloxTransport*)ublox.transport)->receiver;
}


UBXSender* getUbxSenderPointer(Ublox ublox){
	return &((UbloxTransport*)ublox.transport)->sender;
}



void onReceive0107Package(Ublox *ublox,UbxPackage package){
	
	Content0107 content=parsePackage0107(package.content);
	dcounter++;
	ublox->state.height=content.heightAboveSea;
	dlat=ublox->state.lat=content.lat*0.0000001;
	dlon=ublox->state.lon=content.lon*0.0000001;
	return ;
}


void initUbloxSender(Ublox *ublox,int serial){
	UBXSender *sender=getUbxSenderPointer(*ublox);
	initUbxSender(sender,serial);
}

void initUbloxReceiver(Ublox *ublox,int serial){
	UbxReceiver *receiver=getUbxReceiverPointer(*ublox);
	initUbxReceiver(receiver,serial,2000);
}


void initUbloxTransport(Ublox *ublox,int serial){

	ublox->transport=malloc(sizeof(UbloxTransport));
	initUbloxSender(ublox,serial);
	initUbloxReceiver(ublox,serial);
}



void setUpUbloxConfig(Ublox *ublox,UbloxConfigParam paramConfig){
	UbloxConfig config;
	config.sender=getUbxSenderPointer(*ublox);
	config.receiver=getUbxReceiverPointer(*ublox);
	configUartBaudrate(config,paramConfig.baudrate);
	configUartMeasureRate(config,paramConfig.measureRate);
}




void initUbloxWithUart(Ublox *ublox,UbloxConfigParam config,u8 uart,u32 baudrate){
	initUbloxTransport(ublox,uart);
//	setUpUbloxConfig(ublox,config);
}



int counter0107;
int updateUblox(Ublox *ublox){
	static UbxPackage package;
	
	UbxReceiver*pReceiver=getUbxReceiverPointer(*ublox);
	if(!pReceiver->_rec(pReceiver,&package))
		return 0;
	
	if(package.header._class==0x01&&package.header.id==0x07){
		onReceive0107Package(ublox,package);
		counter0107++;
	}
	return 1;
}


NaviPosition getPositionViaUblox(Ublox ublox){
	NaviPosition res;
	res.lat=ublox.state.lat;
	res.lon=ublox.state.lon;
	return res;
}

void disableUblox(Ublox *ublox){
	ublox->isEnable=0;
	UbxReceiver *pReceiver=getUbxReceiverPointer(*ublox);
	pReceiver->_dis(pReceiver);
}

void enableUblox(Ublox *ublox){
	ublox->isEnable=1;
	UbxReceiver *pReceiver=getUbxReceiverPointer(*ublox);
	pReceiver->_ena(pReceiver);
}

