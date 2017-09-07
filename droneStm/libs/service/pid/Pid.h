#ifndef Pid_h_
#define Pid_h_

typedef struct PIDConfig{
	float 	kp,ki,kd;
	float   maxP,maxI,maxD,maxE,maxOut;
}PIDConfig;

typedef struct PID{
	PIDConfig 	config;	
	float 		setPoint;
	float 		prevError;
	float 		integral;
	int 		isReset;
}PID;

void    initPid(PID *pid,float kp,float ki,float kd,float maxE,float maxKp,float maxKi,float maxKd,float maxOut);
void 		initPidWithConfig(PID *pid,PIDConfig config);
float 	updateErrorPID(PID *pid, float pError);
float 	updatePID(PID *pid, float value);
void 		resetPID(PID *pid);
void 		setSetPoint(PID *pid,float sp);
float 	getSetPoint(PID pid);
void 		resetPIDWithNewSetPoint(PID *pid,float sp);
int 		isReseted(PID pid);

#endif
