#ifndef Vector3D_h_
#define Vector3D_h_
#include "stm32f4xx.h"

#define ROLL 	0
#define PITCH 	1
#define YAW     2
typedef struct Vector3D
{
	float roll,pitch,yaw;
}Vector3D;


typedef struct Vector3DInt16_t
{
	int16_t roll,pitch,yaw;	
}Vector3DInt16_t;



Vector3D 	convertArrayToVector3D(float *rawData);
void 			convertVector3DToArray(Vector3D data,float *arrayOutput);
Vector3D 	subVector3D(Vector3D a,Vector3D b);
Vector3D 	scaleVector3D(Vector3D in,float gain);
Vector3D  scaleVector3DIntToVector3D(Vector3DInt16_t in,float gain);
Vector3D  normaliseVector3D(Vector3D in);  
void 			reset3DData(Vector3D *data);




Vector3DInt16_t 	convertArrayToVector3DInt16(int16_t *rawData);
void 							convertVector3DInt16ToArray(Vector3DInt16_t data,int16_t *arrayOutput);
Vector3DInt16_t 	subVector3D16(Vector3DInt16_t a,Vector3DInt16_t b);
void 							resetVector3D(Vector3DInt16_t *data);



#endif
