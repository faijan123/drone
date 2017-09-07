#include "Filter.h"
#include "Constraint.h"







PositionKalmanFilterState constraintKalmanFilterState(PositionKalmanFilterState state,PositionKalmanFilterConfig config){
	PositionKalmanFilterState res=state;
	res.a=constraintFloatValue(state.a,config.aMax);
	res.d=constraintFloatValue(state.d,config.dMax);
	res.v=constraintFloatValue(state.v,config.vMax);
	return res;
}

void resetPositionKalmanFilterState(PositionKalmanFilterState *state){
	state->d=state->v=state->a=0;
}

PositionKalmanFilterState estStatePositionKalmanFilter(PositionKalmanFilterState prevState,PositionKalmanFilterConfig config,float dt){
	PositionKalmanFilterState estState;

	estState.v=prevState.v+dt*prevState.a;
	estState.v=constraintFloatValue(estState.v,config.vMax);
	estState.d=0.5f*dt*dt*prevState.a+prevState.v*dt+prevState.d;
	estState.d=constraintFloatValue(estState.d,config.dMax);
	estState.a=prevState.a;
	return estState;
}


PositionKalmanFilterState correctState(PositionKalmanFilterState estState,PositionKalmanFilterConfig config,float a,float e){
	PositionKalmanFilterState correctState;
	correctState.d=estState.d+e*config.dGain;
	correctState.v=estState.v+e*config.vGain;
	correctState.a=a+e*config.aGain;
	return constraintKalmanFilterState(correctState,config);
}

void initPositionKalmanConfig(PositionKalmanFilterConfig *config,float aGain,float vGain,float dGain,float aMax,float vMax,float dMax){
	config->aGain=aGain;
	config->vGain=vGain;
	config->dGain=dGain;
	config->aMax=aMax;
	config->dMax=dMax;
	config->vMax=vMax;
}



void initPositionKalmanFilter(PositionKalmanFilter *filter,PositionKalmanFilterConfig config){
	filter->config=config;
	resetPositionKalmanFilterState(&filter->state);
}


float updatePositionKalmanFilter(PositionKalmanFilter *filter,float a,float p,float dt){
	float error;
	PositionKalmanFilterState estState=estStatePositionKalmanFilter(filter->state,filter->config,dt);
	error=p-estState.d;
	filter->state=correctState(estState,filter->config,a,error);
	return filter->state.d;
}

void enablePositionKalmanFilter(PositionKalmanFilter *filter,float dBegin){
	filter->state.d=dBegin;
	filter->filterFlag=1;
}

void disablePositionKalmanFilter(PositionKalmanFilter *filter){
	filter->filterFlag=0;
	resetPositionKalmanFilterState(&filter->state);
}
