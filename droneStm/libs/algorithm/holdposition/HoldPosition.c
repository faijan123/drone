#include "HoldPosition.h"
#include "GpsUtil.h"

//Vector2D updatePidAccelPosition(PositionAnchor *anchor,Vector2D accel){
//	Vector2D result;
//	result.x=updatePID(&anchor->pids.accelX,accel.x);
//	result.y=updatePID(&anchor->pids.accelY,accel.y);
//	return result;
//}

//Vector2D updatePositionAnchor(PositionAnchor *anchor,NaviPosition newPosition,Vector2D accel,float yaw){
//	Vector2D result;	
//	return result;
//}

NaviPosition updatePidGpsPosition(PositionAnchor *anchor ,NaviPosition posi){
	NaviPosition result;
	result.lat=updatePID(&anchor->pids.pLat,posi.lat);
	result.lon=updatePID(&anchor->pids.pLon,posi.lon);
	return result;
}




NaviPosition updatePidVelo(PositionAnchor *anchor,NaviPosition velo){
	NaviPosition result;
	result.lat=updatePID(&anchor->pids.pvLat,velo.lat);
	result.lon=updatePID(&anchor->pids.pvLon,velo.lon);
	return result;
}




void changSpVeloPid(PositionAnchor *anchor,NaviPosition veloSp){
	setSetPoint(&anchor->pids.pvLat,veloSp.lat);
	setSetPoint(&anchor->pids.pvLon,veloSp.lon);
	
}




void initPositionAnchor(PositionAnchor *anchor,PIDConfig posiPidConfig,PIDConfig veConfig){
	initPidWithConfig(&anchor->pids.pLat,posiPidConfig);
	initPidWithConfig(&anchor->pids.pLon,posiPidConfig);
	initPidWithConfig(&anchor->pids.pvLat,veConfig);
	initPidWithConfig(&anchor->pids.pvLon,veConfig);
	
	disablePositionAnchor(anchor);
}

void enablePositionAnchor(PositionAnchor *anchor,NaviPosition position){
	anchor->isEnable=1;
}

void disablePositionAnchor(PositionAnchor *anchor){
	resetPID(&anchor->pids.pLat);
	resetPID(&anchor->pids.pLon);
	resetPID(&anchor->pids.pvLat);
	resetPID(&anchor->pids.pvLon);
	anchor->isEnable=0;
	
}


Vector2D updatePositionAnchor(PositionAnchor *anchor,NaviPosition posi,NaviPosition velo,float yaw){
	
	NaviPosition veloSp;
	NaviPosition veloError;
	Vector2D res;
	
	if(!isPositionAnchorEnable(*anchor))
		return res;
	
	veloSp=updatePidGpsPosition(anchor,posi);
	changSpVeloPid(anchor,veloSp);
	veloError=updatePidVelo(anchor,velo);
	return earthNaviBodyNavi(veloError,yaw);

}

int isPositionAnchorEnable(PositionAnchor anchor){
	return anchor.isEnable;
}

