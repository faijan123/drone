#include "HoldAltitude.h"
#include "Pid.h"
#include "filter.h"

#define HALT_ALT_KP 0.7
#define HALT_ALT_KI 0
#define HALT_ALT_KD 0
#define HALT_ALT_MAX_P 10
#define HALT_ALT_MAX_I 10
#define HALT_ALT_MAX_D 10
#define HALT_ALT_MAX_E 100
#define HALT_ALT_MAX_O 10

#define HALT_ACCEL_KP 1
#define HALT_ACCEL_KI 0
#define HALT_ACCEL_KD 0
#define HALT_ACCEL_MAX_P 10
#define HALT_ACCEL_MAX_I 10
#define HALT_ACCEL_MAX_D 10
#define HALT_ACCEL_MAX_E 100
#define HALT_ACCEL_MAX_O 10

#define HALT_FILETER_ACCEL_GAIN 0.9
#define HALT_HFILTER_ACCEL_GAIN 0.2
#define HALT_HFILTER_ACCEL_DEFAULT_VAl 0

PID hAlt_AltPid,hAlt_AccelPid;
ComplementeryFilter hAlt_accelFilter;
HightPassFilter hAlt_hAccelFilter;

	

int holdAltAlgorithmFlag=0;
void initHoldAltitude(void){
	initPid(&hAlt_AccelPid,HALT_ACCEL_KP,HALT_ACCEL_KI,HALT_ACCEL_KD,HALT_ACCEL_MAX_E,HALT_ALT_MAX_P,HALT_ALT_MAX_I,HALT_ALT_MAX_D,HALT_ACCEL_MAX_O);
	initPid(&hAlt_AltPid,HALT_ALT_KP,HALT_ALT_KI,HALT_ALT_KD,HALT_ALT_MAX_E,HALT_ALT_MAX_P,HALT_ALT_MAX_I,HALT_ALT_MAX_D,HALT_ALT_MAX_O);
	initComplementeryFilter(&hAlt_accelFilter,HALT_FILETER_ACCEL_GAIN);
	initHightPassFilter(&hAlt_hAccelFilter,HALT_HFILTER_ACCEL_DEFAULT_VAl,HALT_HFILTER_ACCEL_GAIN);
}


float filterAccel(float accel){
	accel=updateHightPassFilter(&hAlt_hAccelFilter,accel);
	accel=updateComplementeryFilter(&hAlt_accelFilter,accel);
	return accel;
}

float pidAlt1,pidAlt2;
float updateHoldAltitude(float accelZ,float alt){
	float sp=updatePID(&hAlt_AltPid,alt);
	pidAlt1=sp;
	return sp;
//	return pidAlt2=updatePID(&hAlt_AccelPid,filterAccel(accelZ));
}

int isEnableHoldAltitude(void){
	return holdAltAlgorithmFlag;
}
void setNewAltitudeSp(float alt){
	setSetPoint(&hAlt_AltPid,alt);
}

void enableHoldAltitude(float alt){
	setNewAltitudeSp(alt);
	holdAltAlgorithmFlag=1;
}




void disableHoldAltitude(void){
	holdAltAlgorithmFlag=0;
	resetComplementeryFilter(&hAlt_accelFilter);
	resetPID(&hAlt_AccelPid);
	resetPID(&hAlt_AltPid);
}
