#include "Constraint.h"
#include <math.h>

float constraintFloatValues(float value,float min,float max)
{
	if(value>max)
		return max;
	if(value<min)
		return min;
	return value;
}

float constraintFloatValue(float value,float max)
{
	return constraintFloatValues(value,-fabs(max),fabs(max));	
}

void contraintFloatArray(float *in,int n,float max,float *out)
{
	for(int i=0;i<n;i++)
		out[i]=constraintFloatValue(in[i],max);
}

