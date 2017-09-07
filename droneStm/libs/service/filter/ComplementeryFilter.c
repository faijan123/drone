#include "Filter.h"

void initComplementeryFilter(ComplementeryFilter *filter, float coefficient){
	filter->coefficient = coefficient;
	resetComplementeryFilter(filter);
}

void resetComplementeryFilter(ComplementeryFilter *filter){
	filter->oldValue = 0;
}

float updateComplementeryFilter(ComplementeryFilter *filter, float in){
	return filter->oldValue = filter->oldValue*filter->coefficient + in*(1 - filter->coefficient);
}
