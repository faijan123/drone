/*
@author:truonglx,tecasoftandtech.
@des: cai dat cac function dung chung cho cac che do bay khac nhau.
*/
#ifndef GeneralFly_h_
#define GeneralFly_h_
#include "Vector3D.h"

void initGenralFly(void);
void updateControlToQuadCore(void);
Vector3D updateDataToQuadCore(void);
void calculatePwm(float thr,Vector3D error,float *pwms);
void resetDataQuadcore(void);
float getThrottle(void);
#endif
