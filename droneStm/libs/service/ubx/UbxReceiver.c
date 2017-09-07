#include "UbxReceiver.h"
#include "UbxReceiverI.h"
#include "UbxReceiverN.h"



void initUbxReceiver(UbxReceiver *receiver,int serial ,u32 timeout){
	initUbxReceiverN(receiver,timeout,serial);
}
void initUbxReceiverWithInterrupt(UbxReceiver *receiver,int uart){
	initUbxReceiverI(receiver,uart);
}
