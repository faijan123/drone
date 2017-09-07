#ifndef UBXReceiver_h_
#define UBXReceiver_h_
#include "UbxPackage.h"
#include "stm32f4xx.h"
#include "UBXFilter.h"
#include "UBXListener.h"




typedef int (*_receiveUbxPackage)(void *receiver,UbxPackage *package);
typedef void (*_enableUbxReceiver)(void *receiver);
typedef void (*_disableUbxReceiver)(void *receiver);
typedef int (*_isEnableUbxReceiver)(void *receiver);


typedef struct UbxReceiver{
	int uart;
	int enableFlag;
	void *cache;
	u32 timeout;
	
	_receiveUbxPackage _rec;
	_enableUbxReceiver _ena;
	_disableUbxReceiver _dis;
	_isEnableUbxReceiver _isEna;

}UbxReceiver;

#define castUbxReceiver(ubxReicever) (UbxReceiver*)ubxReicever;

void initUbxReceiver(UbxReceiver *receiver, int uart,u32 timeout);
void initUbxReceiverWithInterrupt(UbxReceiver *receiver,int uart);



#endif





