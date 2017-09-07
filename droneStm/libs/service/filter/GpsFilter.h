#ifndef GpsFilter_h_
#define GpsFilter_h_
#include "Position.h"
#include "Vector2D.h"
#include "Vector3D.h"


typedef struct GpsFilterState{
	Vector2D velo;
	Vector2D accelOffset;
	NaviPosition gpsPos;
}GpsFilterState;

typedef struct GpsFilterConfig{
	float vGain,aGain,gpsGain;
	float vMax,aMax;
}GpsFilterConfig;

typedef struct GpsFilter{
	GpsFilterConfig conf;
	GpsFilterState sta;
	int enableFlag;
}GpsFilter;

void initGpsFilter(GpsFilter *filter,GpsFilterConfig con);
void enableGpsFilter(GpsFilter *filter,NaviPosition beginPoint);
void disableGpsFiler(GpsFilter *filter);
int isEnableGpsFilter(GpsFilter filter);
NaviPosition updateGpsFilter(GpsFilter *filter,NaviPosition gpsPoint,Vector2D accel,Vector3D euler,float dt);
NaviPosition getPositionViaGpsFilter(GpsFilter filter);
#endif
