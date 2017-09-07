#ifndef DroneController_h_
#define DroneController_h_
#include "stm32f4xx.h"
#define DELTA_TIME_ACCURACY 3000000

typedef struct ControlValue
{
	float 		value;
	int 			availid;
	uint32_t 	timeReceiveControl;
}ControlValue;


typedef struct DroneControlData{
	ControlValue roll,pitch,yaw,thr;
}DroneControlData;


void 	initDroneController(void);
int 	isRunCalibrateProgram(void);



ControlValue getControlRollValue(void);
ControlValue getControlPitchValue(void);
ControlValue getControlYawValue(void);
ControlValue getControlThrValue(void);
void  updateDroneController(void);

void enableController(void);
void disableController(void);
void resetController(void);
float getChannel1Value(void);
float getChannel2Value(void);
float getChannel3Value(void);
float getChannel4Value(void);


#endif
