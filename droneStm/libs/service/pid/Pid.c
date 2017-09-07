#include "Pid.h"
#include "Constraint.h"





void initPidWithConfig(PID *pid, PIDConfig info)
{
	pid->config = info;
}

void  initPid(PID *pid,float kp,float ki,float kd,float maxE,float maxKp,float maxKi,float maxKd,float maxOut){
	PIDConfig config;
	config.kp=kp;
	config.ki=ki;
	config.kd=kd;
	config.maxE=maxE;
	config.maxP=maxKp;
	config.maxI=maxKi;
	
	config.maxD=maxKd;
	config.maxOut=maxOut;
	initPidWithConfig(pid,config);
}




float calE(PID *pid,float value){
	return 	constraintFloatValue(pid->setPoint-value,pid->config.maxE);
}

float calP(PID *pid,float error){
	float res=pid->config.kp*error;
	return constraintFloatValue(res,pid->config.maxP);
	
}


float calI(PID *pid,float error){
	float res=pid->config.ki*error+pid->integral;
	return pid->integral=constraintFloatValue(res,pid->config.maxI);
}


float calD(PID *pid,float error)
{
	float res=(error-pid->prevError)*pid->config.kd;
	res=constraintFloatValue(res,pid->config.maxD);
	pid->prevError=error;
	return res;
}


float sumPID(PID *pid,float p,float i,float d)
{
	float res=p+i+d;
	return constraintFloatValue(res,pid->config.maxOut);
}

void enablePID(PID *pid)
{
	pid->isReset=1;
}
float updateErrorPID(PID *pid, float pError)
{
	float p,i,d;	
	pError=constraintFloatValue(pError,pid->config.maxE);
	p=calP(pid,pError);
	i=calI(pid,pError);
	d=calD(pid,pError);
	return sumPID(pid,p,i,d);
}

float updatePID(PID *pid, float value)
{
	pid->isReset=0;
	float error = calE(pid,value);
	return updateErrorPID(pid, error);
}


void resetPID(PID *pid){
	pid->setPoint	 =	0;
	pid->integral  = 	0;
	pid->prevError = 	0;
	pid->isReset 	 = 	1;
}

void resetPIDWithNewSetPoint(PID *pid,float sp){
	resetPID(pid);
	pid->setPoint=sp;
}

int isReseted(PID pid)
{
	return pid.isReset;
}


void setSetPoint(PID *pid, float sp)
{
	pid->setPoint = sp;
}


float getSetPoint(PID pid)
{
	return pid.setPoint;
}

