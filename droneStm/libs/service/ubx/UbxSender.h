#ifndef UBXSender_h_
#define UBXSender_h_
#include "UbxPackage.h"



typedef enum UBXSenderState {Busy,Free} UBXSenderState;

typedef struct UBXSender{
	UBXSenderState state;
	int serial;
	void* io;
}UBXSender;




void initUbxSender(UBXSender *sender,int serial);
void cancelUbxSender(UBXSender *sender);
UBXSenderState getUbxSenderState(UBXSender *sender);
void createUbxSenderSection(UBXSender *sender,UbxPackage package,u32 timeout);
int continueUbxSenderSection(UBXSender *sender);
int sendUbxPackage(UBXSender *sender,UbxPackage package);


#endif
