#include "EulerCalculator.h"
#include "EulerUtil.h"
#include "TimeUtil.h"
#include <string.h>

Vector3D updateImuCalculatorWithOutHeading(EulerCalculator *cal,float *accels,float *gyros);
float invSqrt(float x){
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

Vector3D quaternionToDegEuler(float q0,float q1,float q2,float q3)
{
	Vector3D res;
	res.roll	=	atan2(2*q0*q1+2*q2*q3,1-2*q1*q1-2*q2*q2);
 	res.pitch	=	asin((2*q0*q2-2*q3*q1));
	res.yaw		=	atan2(-2*q0*q3-2*q2*q1,1-(2*q3*q3+2*q2*q2));

 	return scaleVector3D(res,RAD_TO_DEG_GAIN);
	
}
void 	initEulerCalculator(EulerCalculator *cal,float frequence,float kp,float ki){
	cal->config.twoKi=ki*2;
	cal->config.twoKp=kp*2;
	cal->config.frequence=frequence;
	cal->integralRoll=cal->integralPitch=cal->integralYaw=0;
	cal->q0=1;
}


void  changeEulerCalculatorConfig(EulerCalculator *cal,EulerCalculatorConfig config){
	cal->config=config;
}


void convertData(Vector3D accel,Vector3D magnet,Vector3D gyro,float *accels,float *magnets,float *gyros){
	gyro=scaleVector3D(gyro,DEG_TO_RAG_GAIN);
	magnet=normaliseVector3D(magnet);
	accel=normaliseVector3D(accel);
	
	convertVector3DToArray(gyro,gyros);
	convertVector3DToArray(magnet,magnets);
	convertVector3DToArray(accel,accels);
}



Vector3D 	updateImuCalculator(EulerCalculator *cal,Vector3D accel,Vector3D magnet,Vector3D gyro){
	float recipNorm;
	float q0,q1,q2,q3;
	float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
	float hx, hy, bx, bz;
	float halfvx, halfvy, halfvz, halfwx, halfwy, halfwz;
	float halfex, halfey, halfez;
	float qa, qb, qc;
	float deltaTime=FREQUENCE_TO_SECOND(cal->config.frequence);
	float gyros[3],magnets[3],accels[3];
	float mx,my,mz;
	float ax,ay,az;
	float gx,gy,gz;
	
	
	convertData(accel,magnet,gyro,accels,magnets,gyros);
	
	
	if(magnets[0]==0&&magnets[1]==0&&magnets[2]==0)
		return updateImuCalculatorWithOutHeading(cal,accels,gyros);
	
	q0=cal->q0;q1=cal->q1;q2=cal->q2;q3=cal->q3;
	mx=magnets[1];my=-magnets[0];mz=magnets[2];
	gx=gyros[0];gy=gyros[1];gz=-gyros[2];
	
//	mx=magnets[0];my=magnets[1];mz=magnets[2];
//	gx=gyros[0];gy=gyros[1];gz=gyros[2];
	
	ax=accels[0];ay=accels[1];az=accels[2];

	q0q0 = q0 * q0;
	q0q1 = q0 * q1;
	q0q2 = q0 * q2;
	q0q3 = q0 * q3;
	q1q1 = q1 * q1;
	q1q2 = q1 * q2;
	q1q3 = q1 * q3;
	q2q2 = q2 * q2;
	q2q3 = q2 * q3;
	q3q3 = q3 * q3; 
	
	hx = 2.0f * (mx * (0.5f - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2));
	hy = 2.0f * (mx * (q1q2 + q0q3) + my * (0.5f - q1q1 - q3q3) + mz * (q2q3 - q0q1));
	bx = sqrt(hx * hx + hy * hy);
	bz = 2.0f * (mx * (q1q3 - q0q2) + my * (q2q3 + q0q1) + mz * (0.5f - q1q1 - q2q2));
	
	halfvx = q1q3 - q0q2;
	halfvy = q0q1 + q2q3;
	halfvz = q0q0 - 0.5f + q3q3;
	halfwx = bx * (0.5f - q2q2 - q3q3) + bz * (q1q3 - q0q2);
	halfwy = bx * (q1q2 - q0q3) + bz * (q0q1 + q2q3);
	halfwz = bx * (q0q2 + q1q3) + bz * (0.5f - q1q1 - q2q2);  
	
	
	halfex = (ay * halfvz - az * halfvy) + (my * halfwz - mz * halfwy);
	halfey = (az * halfvx - ax * halfvz) + (mz * halfwx - mx * halfwz);
	halfez = (ax * halfvy - ay * halfvx) + (mx * halfwy - my * halfwx);
	
	
	if(cal->config.twoKi > 0.0f) {
		cal->integralRoll  += cal->config.twoKi * halfex * deltaTime;	
		cal->integralPitch += cal->config.twoKi * halfey * deltaTime;
		cal->integralYaw 	 += cal->config.twoKi * halfez * deltaTime;
		gx += cal->integralRoll;	
		gy += cal->integralPitch;
		gz += cal->integralYaw;
	}
	else {
		cal->integralRoll = 0.0f;	
		cal->integralPitch = 0.0f;
		cal->integralYaw = 0.0f;
	}

	gx += cal->config.twoKp * halfex;
	gy += cal->config.twoKp * halfey;
	gz += cal->config.twoKp * halfez;
	

	gx *= (0.5f * deltaTime);		// pre-multiply common factors
	gy *= (0.5f * deltaTime);
	gz *= (0.5f * deltaTime);
	qa = q0;
	qb = q1;
	qc = q2;
	q0 += (-qb * gx - qc * gy - q3 * gz);
	q1 += (qa * gx + qc * gz - q3 * gy);
	q2 += (qa * gy - qb * gz + q3 * gx);
	q3 += (qa * gz + qb * gy - qc * gx);
	
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm; 	
		
	cal->q0=q0;cal->q1=q1;cal->q2=q2;cal->q3=q3;
	return quaternionToDegEuler(cal->q0,cal->q1,cal->q2,cal->q3);
}






Vector3D 	updateImuCalculatorWithOutHeading(EulerCalculator *cal,float *accels,float *gyros){
	
	Vector3D res;
	float recipNorm;
	float halfvx, halfvy, halfvz;
	float halfex, halfey, halfez;
	float qa, qb, qc;
	float temIntegral;
	float deltaTime=FREQUENCE_TO_SECOND(cal->config.frequence);
	
	if(accels[0]==0&&accels[1]==0&&accels[2])
		return res;
	
	halfvx = cal->q1 * cal->q3 	- cal->q0 * cal->q2;
	halfvy = cal->q1 * cal->q0	+ cal->q2 * cal->q3;
	halfvz = cal->q0 * cal->q0  + cal->q3 * cal->q3 -0.5f;
	
	
	
	halfex = (accels[1] * halfvz - accels[2] * halfvy);
	halfey = (accels[2] * halfvx - accels[0] * halfvz);
	halfez = (accels[0] * halfvy - accels[1] * halfvx);
	
	
	if(cal->config.twoKi){
		temIntegral=cal->config.twoKi * halfey *deltaTime;
		cal->integralRoll  += temIntegral;
		cal->integralPitch += temIntegral;
		cal->integralYaw	 += temIntegral;
		
		gyros[0]+=cal->integralRoll;
		gyros[1]+=cal->integralPitch;
		gyros[2]+=cal->integralYaw;
	}
	else {
			cal->integralRoll  = 0.0f;
			cal->integralPitch = 0.0f;
			cal->integralYaw   = 0.0f;
	}
	
	gyros[0] += cal->config.twoKp * halfex;
	gyros[1] += cal->config.twoKp * halfey;
	gyros[2] += cal->config.twoKp * halfez;
	
 	gyros[0] *= 0.5f*deltaTime;
	gyros[1] *= 0.5f*deltaTime;
	gyros[2] *= 0.5f*deltaTime;
	
	qa = cal->q0;
	qb = cal->q1;
	qc = cal->q2;
	
	cal->q0 += (-qb * gyros[0] - qc * gyros[1] - cal->q3 * gyros[2]);
	cal->q1 += (qa  * gyros[0] + qc * gyros[2] - cal->q3 * gyros[1]);
	cal->q2 += (qa  * gyros[1] - qb * gyros[2] + cal->q3 * gyros[0]);
	cal->q3 += (qa  * gyros[2] + qb * gyros[1] - qc * gyros[0]);

	// Normalise quaternion
	recipNorm = invSqrt(cal-> q0*cal->q0 +  cal->q1*cal->q1 + cal->q2 * cal->q2 + cal->q3 * cal->q3);
	cal->q0 *= recipNorm;
	cal->q1 *= recipNorm;
	cal->q2 *= recipNorm;
	cal->q3 *= recipNorm;
	return quaternionToDegEuler(cal->q0,cal->q1,cal->q2,cal->q3);
}
