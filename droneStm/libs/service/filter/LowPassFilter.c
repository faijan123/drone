#include "Filter.h"

void intLowPassFilter(LowPassFilter *lowPassFilter, float thresHold, float coefficient){
	lowPassFilter->coefficient = coefficient;
	lowPassFilter->thresHold = thresHold;
}


float updateLowPassFilter(LowPassFilter *lowPassFilter, float in){
	return in;
}
