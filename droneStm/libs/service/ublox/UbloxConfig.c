#include "UbloxConfig.h"
#include "UbxPackage.h"
#include "UbxReceiver.h"
#include "UbxSender.h"
#include <stdlib.h>
#include <string.h>

#define CLASS_ID_ACK 0x05
#define MSG_ID_ACK 0x01
#define MSG_ID_N_ACK 0x00
#define NUMBER_TRY 50
int isAckOfMessage(UbxPackage settingMessage,UbxPackage feedbackMessage){
	u8 classIdOfAck,messageIdOfAck;
	if(feedbackMessage.header._class!=CLASS_ID_ACK)
		return 0;
	classIdOfAck=feedbackMessage.content[0];
	messageIdOfAck=feedbackMessage.content[1];
	if(settingMessage.header._class!=classIdOfAck&&settingMessage.header.id!=messageIdOfAck)
		return 0;
	return feedbackMessage.header.id==MSG_ID_ACK;
}


int isFeedbackMessage(UbxPackage feedbackMessage){
	return feedbackMessage.header._class==CLASS_ID_ACK;
}


int receiveFeedBack(UbloxConfig config,UbxPackage settingMessage){
	UbxPackage feedbackMessage;
	int res;
	
	UbxReceiver *receiver=(UbxReceiver*)config.receiver;
	while(!receiver->_rec(receiver,&feedbackMessage));
	res=isAckOfMessage(settingMessage,feedbackMessage);
	deleteUbxPackage(&feedbackMessage);
	return res;
}



int sendSettingPackage(UbloxConfig config,u8 _class,u8 id,u8 *content,u16 length){
	UbxPackage sendPackage;
	UBXSender *sender;
	UbxHeader header;
	
	int res=0;
	int tryingCounter=0;
	
	
	sender=(UBXSender*)config.sender;
	initUbxHeader(&header,_class,id,length);
	createUbxPackage(&sendPackage,header,content);
	do{
		sendUbxPackage(sender,sendPackage);
		res=receiveFeedBack(config,sendPackage);
	}while(!res&&++tryingCounter<NUMBER_TRY);
	deleteUbxPackage(&sendPackage);
	return res;
	
}

void configUartBaudrate(UbloxConfig config,long baudrate){
	u8 mClass=6,mId=00;
	u16 mLength=20;
	u8 *bufferMsg;
	u8 portId=1;


	bufferMsg=(u8*)malloc(mLength);
	memset(bufferMsg,0,mLength);
	bufferMsg[0]=portId;
	memcpy(bufferMsg+8,&baudrate,4); 
	sendSettingPackage(config,mClass,mId,bufferMsg,mLength);
	free(bufferMsg);
}
void configUartMeasureRate(UbloxConfig config,long timeUpdate){
	const u8 mClass=6,mId=8;
	const u8 mLength=6;
	u8 *mBuffer;
	u16 measRate=timeUpdate;
	u16 navRate=127;
	u16 timeRef=1;
	
	
	mBuffer=(u8*)malloc(mLength);
	memcpy(mBuffer,&measRate,2);
	memcpy(mBuffer+2,&navRate,2);
	memcpy(mBuffer+4,&timeRef,2);
	sendSettingPackage(config,mClass,mId,mBuffer,mLength);
	free(mBuffer);
} 

