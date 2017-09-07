#ifndef UbloxConfig_h_
#define UbloxConfig_h_

typedef struct UbloxConfig{
	void *sender;
	void *receiver;
}UbloxConfig;


void configUartBaudrate(UbloxConfig config,long baudrate);
void configUartMeasureRate(UbloxConfig config,long timeUpdate);

#endif
