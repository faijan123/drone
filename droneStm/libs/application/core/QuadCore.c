#include "QuadCore.h"
#include "Pid.h"
#include "Filter.h"
#include "TimeChecker.h"
#include "TcTime.h"

#define QUADCORE_ROLL_AXIS 	0
#define QUADCORE_PITCH_AXIS 1
#define QUADCORE_YAW_AXIS		2	
#define TIME_AVAI_UPDATE_EULER 500000
/*-----------------------------------------pid config gyro---------------------------------------------------------*/
#define KP_G_R          1.35
#define KI_G_R          0.04
#define KD_G_R          18
#define MAXE_G_R       	450
#define MAXP_G_R      	450
#define MAXI_G_R      	450
#define MAXD_G_R      	450
#define MAXOUT_G_R     	450

#define KP_G_P          1.35
#define KI_G_P          0.04
#define KD_G_P          18
#define MAXE_G_P       	450
#define MAXP_G_P      	450
#define MAXI_G_P      	450
#define MAXD_G_P      	450
#define MAXOUT_G_P     	450


#define KP_G_Y          5.0
#define KI_G_Y          0.03
#define KD_G_Y          0
#define MAXE_G_Y       	450
#define MAXP_G_Y      	450
#define MAXI_G_Y      	450
#define MAXD_G_Y      	400
#define MAXOUT_G_Y     	450

/*-----------------------------------------pid config euler ---------------------------------------------------------*/
#define KP_E_R         			1.0
#define KI_E_R         			0.0
#define KD_E_R         			0.0
#define MAXE_E_R      			20.0
#define MAXP_E_R     				20.0
#define MAXI_E_R     				20.0
#define MAXD_E_R     				20.0
#define MAXOUT_E_R    			20.0

#define KP_E_P         			1.0
#define KI_E_P         			0.0
#define KD_E_P         			0.0
#define MAXE_E_P      			20.0
#define MAXP_E_P     				20.0
#define MAXI_E_P     				20.0
#define MAXD_E_P     				20.0
#define MAXOUT_E_P    			20.0


#define KP_E_Y         			0.0
#define KI_E_Y         			0.0
#define KD_E_Y         			0.0
#define MAXE_E_Y      			20.0
#define MAXP_E_Y     				20.0
#define MAXI_E_Y     				20.0
#define MAXD_E_Y     				20.0
#define MAXOUT_E_Y    			20.0

#define GYRO_FILTER_GAIN    0.8f

PID eulerPids[3];
PID gyroPids[3];
ComplementeryFilter gyroFilters[3];
Vector3D core_res;

uint32_t timerUpdateEuler[3];


float updatePidOnAxis(int axis,float euler,float gyro){
	float newSetPointGyro=0;
	if(axis>2||axis<0)
	return 0;
	if(axis!=2&&(getCurrentTime()-timerUpdateEuler[axis])<TIME_AVAI_UPDATE_EULER){
		newSetPointGyro=updatePID(eulerPids+axis,euler);
		setSetPoint(gyroPids+axis,newSetPointGyro);
	}
	return updatePID(gyroPids+axis,updateComplementeryFilter(gyroFilters+axis,gyro));
}

float updatePidOnAxisDebug(int axis,float euler,float gyro)
{
	float newSetPointGyro=0;
	if(axis>2||axis<0)
	return 0;
	if(axis!=2&&(getCurrentTime()-timerUpdateEuler[axis])<TIME_AVAI_UPDATE_EULER){
		newSetPointGyro=updatePID(eulerPids+axis,euler);
		setSetPoint(gyroPids+axis,newSetPointGyro);
	}
	else
			setSetPoint(gyroPids+axis,0);
	return updatePID(gyroPids+axis,updateComplementeryFilter(gyroFilters+axis,gyro));
}

void initPids(void){
	initPid(eulerPids+QUADCORE_ROLL_AXIS, KP_E_R,KI_E_R,KD_E_R,MAXE_E_R,MAXP_E_R,MAXI_E_R,MAXD_E_R,MAXOUT_E_R);
	initPid(eulerPids+QUADCORE_PITCH_AXIS,KP_E_P,KI_E_P,KD_E_P,MAXE_E_P,MAXP_E_P,MAXI_E_P,MAXD_E_P,MAXOUT_E_P);
	initPid(eulerPids+QUADCORE_YAW_AXIS,  KP_E_R,KI_E_Y,KD_E_Y,MAXE_E_Y,MAXP_E_Y,MAXI_E_Y,MAXD_E_Y,MAXOUT_E_Y);
	
	initPid(gyroPids+QUADCORE_ROLL_AXIS, KP_G_R,KI_G_R,KD_G_R,MAXE_G_R,MAXP_G_R,MAXI_G_R,MAXD_G_R,MAXOUT_G_R);
	initPid(gyroPids+QUADCORE_PITCH_AXIS,KP_G_P,KI_G_P,KD_G_P,MAXE_G_P,MAXP_G_P,MAXI_G_P,MAXD_G_P,MAXOUT_G_P);
	initPid(gyroPids+QUADCORE_YAW_AXIS,  KP_G_R,KI_G_Y,KD_G_Y,MAXE_G_Y,MAXP_G_Y,MAXI_G_Y,MAXD_G_Y,MAXOUT_G_Y);
	
}


void initGyroFiltes(void){
	for(int i=0;i<3;i++)
		initComplementeryFilter(gyroFilters+i,GYRO_FILTER_GAIN);
}


void initQuadCore(void){
	initPids();
	initGyroFiltes();
}



Vector3D updateQuadCore(Vector3D euler,Vector3D gyro){
	Vector3D res;	
	res.roll=updatePidOnAxisDebug(QUADCORE_ROLL_AXIS,euler.roll,gyro.roll);
	res.pitch=updatePidOnAxisDebug(QUADCORE_PITCH_AXIS,euler.pitch,gyro.pitch);
	res.yaw=updatePidOnAxisDebug(QUADCORE_YAW_AXIS,euler.yaw,gyro.yaw);
	core_res=res;
	return res;
}

void changeSetPointRoll(float setPoint){
	timerUpdateEuler[0]=getCurrentTime();
	setSetPoint(eulerPids+QUADCORE_ROLL_AXIS,setPoint);
}

void changeSetPointPitch(float setPoint){
	timerUpdateEuler[1]=getCurrentTime();
	setSetPoint(eulerPids+QUADCORE_PITCH_AXIS,setPoint);
}
void changeSetPointYaw(float setPoint){
	timerUpdateEuler[2]=getCurrentTime();
	setSetPoint(eulerPids+QUADCORE_YAW_AXIS,setPoint);
}

void resetQuadCore(void){
	for(int i=0;i<3;i++){
		resetPIDWithNewSetPoint(gyroPids+i,0);
		resetPIDWithNewSetPoint(eulerPids+i,0);
		resetComplementeryFilter(gyroFilters+i);
	}
}

int isQuadCoreReseted(void){
	int res=1;
	for(int i=0;i<3;i++)
		res&=(isReseted(eulerPids[i])&&isReseted(gyroPids[i]));
	return res;
}

void checkAndResetQuadCore(void){
	if(!isQuadCoreReseted())
		resetQuadCore();
}



