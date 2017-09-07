#ifndef UartSendingHelper_
#define UartSendingHelper_
#include "stm32f4xx.h"


typedef enum UartSendingHelperState {UartHelperState_Busy,UartHelperState_Free} UartSendingHelperState;
typedef struct UartSendingHelper{
	int serial;
	void* section;
	UartSendingHelperState state;
}UartSendingHelper;

void initUartSendingHelper(UartSendingHelper *sender,int serial);
void cancelUartSendingHelper(UartSendingHelper *sender);
UartSendingHelperState getUartSendingHelperState(UartSendingHelper sender);
void createUartSendingHelperSection(UartSendingHelper *sender,u8 *buffer,int length,u32 timeout);
int continueUartSendingHelperSection(UartSendingHelper *sender);


#endif
