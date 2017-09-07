/*
@author : truonglx
@des    : define struct data 2d.
*/

#ifndef Vector2D_h_
#define Vector2D_h_


#define X			0
#define Y			1



typedef struct Vector2D
{
	float x,y;
}Vector2D;


void 		Vector2DToArray(Vector2D data,float *arrayOutput);
Vector2D 	arrayToVector2D(float *array);
Vector2D 	subVector2D(Vector2D a,Vector2D b);
Vector2D 	addVector2D(Vector2D a,Vector2D b);
Vector2D 	scaleVector2D(Vector2D a,float gain);
Vector2D 	contraintVector2D(Vector2D data,float maxFieldValue);
void    	resetVector2D(Vector2D *data);

#endif



