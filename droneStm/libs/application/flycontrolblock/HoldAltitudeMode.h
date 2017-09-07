/*
@author:truonglx,tecasoftandtech.
@des:
1. Tinh toan gia tri muc ga de du do cao.
*/

#ifndef HoldAltitudeMode_h_
#define HoldAltitudeMode_h_
void 	initHoldAltitudeMode(void);
void 	enableHoldAltitudeMode(void);
void	disableHoldAltitudeMode(void);
int 	isEnableHoldAltitudeMode(void);
void 	updateHoldAltitudeMode(float *pwms);
float updateHoldAltitudeModeWithOutPwm(void);

#endif
