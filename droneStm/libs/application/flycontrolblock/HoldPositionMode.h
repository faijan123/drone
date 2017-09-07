#ifndef HoldPositionMode_h_
#define HoldPositionMode_h_

void initHoldPositionMode(void);
void enableHoldPositionMode(void);
int isEnableHoldPositionMode(void);
void disableHoldPositionMode(void);
void updateHoldPositionMode(float *pwms);
void updateHoldPositionModeWithThr(float thr,float *pwms);
#endif
