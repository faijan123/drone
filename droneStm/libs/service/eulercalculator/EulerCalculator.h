#ifndef EulerCalculator_h_
#define EulerCalculator_h_
#include "Vector3D.h"



typedef struct EulerCalculatorConfig
{
	float frequence,twoKp,twoKi;
}EulerCalculatorConfig;

typedef struct EulerCalculator
{
	EulerCalculatorConfig config;
	float integralRoll,integralPitch,integralYaw;
	float q0,q1,q2,q3;
}EulerCalculator;

void 			initEulerCalculator(EulerCalculator *cal,float frequence,float kp,float ki);
void 			changeEulerCalculatorConfig(EulerCalculator *cal,EulerCalculatorConfig config);
Vector3D 	updateImuCalculator(EulerCalculator *cal,Vector3D accel,Vector3D magnet,Vector3D gyro);


#endif
