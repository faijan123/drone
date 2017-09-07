#include "Vector2D.h"
#include "Constraint.h"



void 	Vector2DToArray(Vector2D data,float *arrayOutput)
{
	arrayOutput[X]=data.x;
	arrayOutput[Y]=data.y;
}
Vector2D 	arrayToVector2D(float *array)
{
	Vector2D res;
	res.x=array[X];
	res.y=array[Y];
	return res;
}


Vector2D 	subVector2D(Vector2D a,Vector2D b)
{
	Vector2D res;
	res.x=a.x-b.x;
	res.y=a.y-b.y;
	return res;
}


Vector2D 	addVector2D(Vector2D a,Vector2D b)
{
	Vector2D res;
	res.x=a.x+b.x;
	res.y=a.y+b.y;
	return res;
}
Vector2D 	scaleVector2D(Vector2D a,float gain)
{
	Vector2D res;
	res.x=a.x*gain;
	res.y=a.y*gain;
	return res;
}
Vector2D 	contraintVector2D(Vector2D data,float maxFieldValue)
{
	Vector2D res;
	res.x=constraintFloatValue(data.x,maxFieldValue);
	res.y=constraintFloatValue(data.y,maxFieldValue);
	return res;
}
void    	resetVector2D(Vector2D *data)
{
	data->x=data->y=0;
}



