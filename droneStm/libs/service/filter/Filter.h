#ifndef Filter_h_
#define Filter_h_


/*------------------------------------------ComplementeryFilter--------------------------------*/

typedef struct ComplementeryFilter
{
	float oldValue;
	float coefficient;
}ComplementeryFilter;

void  	initComplementeryFilter(ComplementeryFilter *filter, float coefficient);
float 	updateComplementeryFilter(ComplementeryFilter *filter, float in);
void  	resetComplementeryFilter(ComplementeryFilter *filter);


/*------------------------------------------LowPassFilter-----------------------------------*/

typedef struct LowPassFilter
{
	float coefficient;
	float thresHold;
}LowPassFilter;

void    initLowPassFilter(LowPassFilter *filter,float thresHold);
float 	updateLowPassFilte(LowPassFilter *filter, float in);
void 		resetLowPassFilter(LowPassFilter *filter);

/*------------------------------------------HightPassFilter---------------------------------*/
typedef struct HightPassFilter
{
	float defaultValue;
	float thresHold;
}HightPassFilter;

void 	initHightPassFilter(HightPassFilter *filter,float defaultValue,float thresHold);
float updateHightPassFilter(HightPassFilter *filter,float value);

/*------------------------------------------AveFilter--------------------------------------*/




typedef struct AveFilter{
	int 	numberSample;
	float *samples;
	int counter;
	
}AveFilter;





typedef struct DynamicAveFilter
{
	int sample;
	int counter;
	float *store;
}DynamicAveFilter;



void 	initAveFilter(AveFilter *aveFilter,int sample);
float updateAveFilter(AveFilter *aveFilter,float value);
void 	resetAveFilter(AveFilter *aveFilter);
float getAveFilterResult(AveFilter aveFilter);




void 	initDynamicAveFilter(DynamicAveFilter *filter,int sample);
float	updateDynamicAveFilter(DynamicAveFilter *filter,float value);
void 	resetDynamicAveFilter(DynamicAveFilter *filter);
float getDynamicAveFilterResult(DynamicAveFilter filter);
void 	deleteDynamicAveFilter(DynamicAveFilter *filter);
int 	isDynamicAveFilterEmpty(DynamicAveFilter filter);
int 	isDynamicAveFilterFull(DynamicAveFilter filter);


/*--------------------------------- DistanceKalmanFilter -------------------------------------------*/
typedef struct PositionKalmanFilterConfig{
	float aGain,vGain,dGain;
	float aMax,vMax,dMax;
}PositionKalmanFilterConfig;

typedef struct PositionKalmanFilterState{
	float a,v,d;
}PositionKalmanFilterState;


typedef struct PositionKalmanFilter{
	PositionKalmanFilterConfig config;
	PositionKalmanFilterState state;
	int filterFlag;
}PositionKalmanFilter;


void initPositionKalmanConfig(PositionKalmanFilterConfig *config,float aGain,float vGain,float dGain,float aMax,float vMax,float dMax);
void initPositionKalmanFilter(PositionKalmanFilter *filter,PositionKalmanFilterConfig config);
float updatePositionKalmanFilter(PositionKalmanFilter *filter,float a,float p,float dt);
void enablePositionKalmanFilter(PositionKalmanFilter *filter,float dBegin);
void disablePositionKalmanFilter(PositionKalmanFilter *filter);





#endif
