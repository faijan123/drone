#include "Vector3D.h"
#include "math.h"
#include "TimeUtil.h"

Vector3D 	convertArrayToVector3D(float *rawData)
{
	Vector3D res;
	res.roll=rawData[ROLL];
	res.pitch=rawData[PITCH];
	res.yaw=rawData[YAW];
	return res;
}

void 	convertVector3DToArray(Vector3D data,float *arrayOutput)
{
	arrayOutput[ROLL]=data.roll;
	arrayOutput[PITCH]=data.pitch;
	arrayOutput[YAW]=data.yaw;
}

Vector3D subVector3D(Vector3D a,Vector3D b)
{
	Vector3D res;
	res.roll=a.roll-b.roll;
	res.pitch=a.pitch-b.pitch;
	res.yaw=a.yaw-b.yaw;
	return res;
}


Vector3D scaleVector3D(Vector3D in,float gain)
{
	Vector3D res;
	res.roll=in.roll*gain;
	res.pitch=in.pitch*gain;
	res.yaw=in.yaw*gain;
	return res;
}


Vector3D  normaliseVector3D(Vector3D in)
{
	float tem=in.roll*in.roll+in.pitch*in.pitch+in.yaw*in.yaw;
	if(tem==0)
		return in;
	tem=1.0f/sqrtf(tem);
	return scaleVector3D(in,tem);
}


void 	reset3DData(Vector3D *data)
{
	data->roll=0;
	data->pitch=0;
	data->yaw=0;
}

Vector3DInt16_t convertArrayToVector3DInt16(int16_t *rawData)
{
	Vector3DInt16_t res;
	res.roll=rawData[ROLL];
	res.pitch=rawData[PITCH];
	res.yaw=rawData[YAW];
	return res;
	
}
void convertVector3DInt16ToArray(Vector3DInt16_t data,int16_t *arrayOutput)
{
	arrayOutput[ROLL]=data.roll;
	arrayOutput[PITCH]=data.pitch;
	arrayOutput[YAW]=data.yaw;
}

Vector3DInt16_t subVector3D16(Vector3DInt16_t a,Vector3DInt16_t b)
{
	Vector3DInt16_t res;
	res.roll=a.roll-b.roll;
	res.pitch=a.pitch-b.pitch;
	res.yaw=a.yaw-b.yaw;
	return res;
}


void resetVector3D(Vector3DInt16_t *data)
{
	data->roll=data->pitch=data->yaw=0;
}


Vector3D  scaleVector3DIntToVector3D(Vector3DInt16_t in,float gain)
{
	Vector3D res;
	res.roll=in.roll*gain;
	res.pitch=in.pitch*gain;
	res.yaw=in.yaw*gain;
	return res;
}
