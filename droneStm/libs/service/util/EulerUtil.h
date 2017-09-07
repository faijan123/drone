#ifndef EulerUtil_h_
#define EulerUtil_h_
#include <math.h>

#define DegToRad(deg) 	deg/180*3.141592f
#define RadToDeg(rad) 	rad/3.141592f*180
#define CosDeg(deg)   	cos(DegToRad(deg))
#define SinDeg(deg)   	sin(DegToRad(deg))
#define DEG_TO_RAG_GAIN 3.141592f/180
#define RAD_TO_DEG_GAIN 180/3.141592f

#endif
