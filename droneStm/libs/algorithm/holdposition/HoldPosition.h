#ifndef HoldPosition_h_
#define HoldPosition_h_
#include "Position.h"
#include "Vector2D.h"
#include "Pid.h"
typedef struct PositionAnchorConfig{
	float a,b,c,d;
}PositionAnchorConfig;

typedef struct PositionAnchorPIDS{
	PID pLat,pLon;
	PID pvLat,pvLon;
}PositionAnchorPIDS;

typedef struct PositionAnchor{
	PositionAnchorConfig config;
	PositionAnchorPIDS pids;
	NaviPosition anchorPosi;
	int isEnable;
}PositionAnchor;



void initPositionAnchor(PositionAnchor *anchor,PIDConfig posiPidConfig,PIDConfig vePidConfig);
void enablePositionAnchor(PositionAnchor *anchor,NaviPosition position);
void disablePositionAnchor(PositionAnchor *anchor);
//Vector2D updatePositionAnchor(PositionAnchor *anchor,NaviPosition newPosition,Vector2D accel,float yaw);
Vector2D updatePositionAnchor(PositionAnchor *anchor,NaviPosition newPosition,NaviPosition velo,float yaw);
int isPositionAnchorEnable(PositionAnchor anchor);
#endif

