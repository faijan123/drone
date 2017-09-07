#ifndef HoldAltitude_h_
#define HoldAltitude_h_
#include "Vector3D.h"
void initHoldAltitude(void);
float updateHoldAltitude(float accelZ,float alt);
void enableHoldAltitude(float alt);
void disableHoldAltitude(void);
int isEnableHoldAltitude(void);
void setNewAltitudeSp(float alt);
#endif
