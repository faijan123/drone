#ifndef Ublox_h_
#define Ublox_h_

#include "stm32f4xx.h"
#include "Position.h"
#include "UbxProtocol.h"



typedef struct UbloxConfigParam{
	long baudrate,measureRate;
}UbloxConfigParam;



typedef struct UbloxState{
	double lat,lon,height;
}UbloxState;





typedef struct Ublox{
	void  *transport;
	UbloxState state;
	int isEnable;
}Ublox;


void initUbloxWithUart(Ublox *ublox,UbloxConfigParam config,u8 uart,u32 baudrate);
int updateUblox(Ublox *ublox);
void disableUblox(Ublox *ublox);
void enableUblox(Ublox *ublox);
void isEnableUblox(Ublox ublox);
NaviPosition getPositionViaUblox(Ublox ublox);



#endif
