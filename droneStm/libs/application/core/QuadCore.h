#ifndef QuadCore_h_
#define QuadCore_h_
#include "Vector3D.h"
void 			initQuadCore(void);
Vector3D 	updateQuadCore(Vector3D euler,Vector3D gyro);
void 			changeSetPointRoll(float setPoint);
void 			changeSetPointPitch(float setPoint);
void 			changeSetPointYaw(float setPoint);
void 			resetQuadCore(void);
int 			isQuadCoreReseted(void);
void			checkAndResetQuadCore(void);
#endif
