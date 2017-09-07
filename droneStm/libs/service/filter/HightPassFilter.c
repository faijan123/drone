#include "Filter.h"
#include <math.h>

void initHightPassFilter(HightPassFilter *filter,float defaultValue,float thresHold){
	filter->defaultValue=defaultValue;
	filter->thresHold=thresHold;
}

float updateHightPassFilter(HightPassFilter *filter,float value){
	if(fabs(value)>filter->thresHold)
		return value;
	else
		return filter->defaultValue;
}
