#include "MagnetCalibrate.h"
#include <string.h>
void initMagnetCalibrator(MagnetCalibrator *cal,float maxtrix[3][3],float *bias){
	for(int i=0;i<3;i++)
		memcpy(cal->matrix[i],maxtrix[i],3*sizeof(float));
	memcpy(cal->bias,bias,3*sizeof(float));
}
void calibMagnet(MagnetCalibrator cal,float *magnetIn,float *magnetOut){
	for(int i=0;i<3;i++){
		magnetOut[i]=magnetIn[i]-cal.bias[i];
		for(int j=0;j<3;j++)
			magnetOut[i]+=cal.matrix[i][j]*magnetIn[j];
		
	}
}

Vector3D calibMagnetVector(MagnetCalibrator cal,Vector3D vectorIn){
	float arrayIn[3],arrayOut[3];
	convertVector3DToArray(vectorIn,arrayIn);
	calibMagnet(cal,arrayIn,arrayOut);
	return convertArrayToVector3D(arrayOut);
}
