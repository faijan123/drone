#include "Filter.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>


void initAveFilter(AveFilter *aveFilter,int numberSample){
	aveFilter->numberSample=numberSample;
	resetAveFilter(aveFilter);
	if(aveFilter->samples!=NULL)
		free(aveFilter->samples);
	aveFilter->samples=malloc(numberSample*sizeof(float));
}

void resetAveFilter(AveFilter *aveFilter){
	aveFilter->counter=0;
	memset(aveFilter->samples,0,sizeof(float)*aveFilter->numberSample);
}


void pushElementToAveFilter(AveFilter *aveFilter,float element){
	if(aveFilter->counter<aveFilter->numberSample)
		aveFilter->samples[aveFilter->counter]=element;
	
}

float getAveFilterResult(AveFilter aveFilter){
	float sum=0;
	for(int i=0;i<aveFilter.numberSample;i++)
		sum+=aveFilter.samples[i];
	return sum/aveFilter.counter;
}

void putElementToAveFilter(AveFilter *aveFilter,float element){
	if(aveFilter->counter<aveFilter->numberSample){
		aveFilter->samples[aveFilter->counter++]=element;
		return;
	}
	
	for(int i=1;i<aveFilter->counter;i++)
		aveFilter->samples[i-1]=aveFilter->samples[i];
	aveFilter->samples[aveFilter->counter-1]=element;
}

float updateAveFilter(AveFilter *aveFilter,float value){
	putElementToAveFilter(aveFilter,value);
	return getAveFilterResult(*aveFilter);
}




int isDynamicFilterEmpty(DynamicAveFilter filter){
	if(filter.counter==0)
		return 1;
	return 0;
}

int isDynamicAveFilterFull(DynamicAveFilter filter){
	if(filter.counter==filter.sample)
		return 1;
	return 0;
}

float caculateDynamicAvgFilter(DynamicAveFilter filter){
	float sum=0;
	if(isDynamicFilterEmpty(filter))
		return 0;
	for(int i=0;i<filter.counter;i++)
		sum+=filter.store[i];
	return sum/filter.counter;
	
}
void initDynamicAveFilter(DynamicAveFilter *filter,int sample){
	filter->sample=sample;
	filter->store=(float*)malloc(sizeof(float)*sample);
	resetDynamicAveFilter(filter);

}

float	updateDynamicAveFilter(DynamicAveFilter *filter,float value){

	if(!isDynamicAveFilterFull(*filter))
	{
		for(int i=1;i<filter->sample-1;i++)
			filter->store[i-1]=filter->store[i];
		filter->store[filter->sample-1]=value;
	}
	else
		filter->store[filter->counter++]=value;
	return caculateDynamicAvgFilter(*filter);
}

void resetDynamicAveFilter(DynamicAveFilter *filter){
	for(int i=0;i<filter->sample;i++)
		filter->store[i]=0;
	filter->counter=0;
}


float getDynamicAveFilterResult(DynamicAveFilter filter){
	return caculateDynamicAvgFilter(filter);
}

void deleteAveFilter(DynamicAveFilter *filter){
	free(filter->store);
}
