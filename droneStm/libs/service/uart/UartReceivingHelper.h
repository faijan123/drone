#ifndef UartReceivingHelper_h_
#define UartReceivingHelper_h_


typedef enum UartReceivingHelperState {Busy,Free} UartReceivingHelperState;
typedef struct UartReceivingHelper{
	int serial;
	void* section;
	UartReceivingHelperState state;
}UartReceivingHelper;

void initUartReceivingHelper(UartReceivingHelper *receiver,int serial);
void cancelUartReceivingHelper(UartReceivingHelper *receiver);
UartReceivingHelperState getUartReceivingHelperState(UartReceivingHelper *receiver);
void createUartReceivingHelperSection(UartReceivingHelper *receiver,u8 *buffer,int length,u32 timeout);
#endif