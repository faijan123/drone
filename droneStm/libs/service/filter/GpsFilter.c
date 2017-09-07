#include "GpsFilter.h"
#include "Translate.h"
#include "AccelUtil.h"
#include "Constraint.h"
#include "Filter.h"





GpsFilterState debugFilterState;



void resetGpsFilter(GpsFilter *filter){
	filter->sta.velo.x=0;
	filter->sta.velo.y=0;
	
	filter->sta.accelOffset.x=0;
	filter->sta.accelOffset.y=0;
	
	filter->sta.gpsPos.lat=0;
	filter->sta.gpsPos.lat=0;
}

GpsFilterState initGpsFilterState(Vector2D accelOffset,Vector2D velo,NaviPosition gpsPos){
	GpsFilterState res;
	res.accelOffset=accelOffset;
	res.velo=velo;
	res.gpsPos=gpsPos;
	return res;
}







Vector2D _debugDistance;


GpsFilterState  estNewGpsFilterState(GpsFilter filter,Vector2D accel,Vector3D euler,float dt){
	Vector2D distance;
	Vector2D velo;
	NaviPosition gpsPoint;

	

	
	accel.x=getRealAccelX(accel.x+0.27f,euler.pitch);
	accel.y=getRealAccelY(accel.y,euler.roll);
	
	
	
	accel=subVector2D(accel,filter.sta.accelOffset);
	accel=contraintVector2D(accel,filter.conf.aMax);
	
	

	
	
	if(__fabs(accel.x)<1)
		accel.x=0;
	if(__fabs(accel.y)<1)
		accel.y=0;
	
	

	velo.x=filter.sta.velo.x+accel.x*dt;
	
	if(__fabs(velo.x)<0.01)
		velo.x=0; 
	
	velo.y=filter.sta.velo.y+accel.y*dt;
	velo=contraintVector2D(velo,filter.conf.vMax);
	
	
	distance.x=0.5f*accel.x*dt*dt+velo.x*dt;
	distance.y=0.5f*accel.y*dt*dt+velo.x*dt;
	
		_debugDistance=distance;
	distance=rotation2D(distance,-euler.yaw+90); // quay sang he truc trai dat

	
	gpsPoint=add2DToNaviPosition(filter.sta.gpsPos,distance);
	
	return initGpsFilterState(filter.sta.accelOffset,velo,gpsPoint);
	
}



GpsFilterState correctNewGpsFilterState(GpsFilter filter,NaviPosition naviError,Vector2D bodyError,GpsFilterState estState){

	
	GpsFilterState res;
	
	
	res.gpsPos.lat=estState.gpsPos.lat+naviError.lat*filter.conf.gpsGain;
	res.gpsPos.lon=estState.gpsPos.lon+naviError.lon*filter.conf.gpsGain;
		
	res.accelOffset.x=estState.accelOffset.x+filter.conf.aGain*bodyError.x;
	res.accelOffset.y=estState.accelOffset.y+filter.conf.aGain*bodyError.y;
	res.accelOffset=contraintVector2D(res.accelOffset,filter.conf.aMax);
	
	
	res.velo.x=estState.velo.x+filter.conf.vGain*bodyError.x;
	res.velo.y=estState.velo.y+filter.conf.vGain*bodyError.y;
	res.velo=contraintVector2D(res.velo,filter.conf.vMax);
	
	
	
	return res;

}




void initGpsFilter(GpsFilter *filter,GpsFilterConfig config){
	filter->conf=config;
	resetGpsFilter(filter);
	
}
void enableGpsFilter(GpsFilter *filter,NaviPosition beginPoint){
	filter->sta.gpsPos=beginPoint;
	filter->enableFlag=1;
}
void disableGpsFiler(GpsFilter *filter){
	resetGpsFilter(filter);
	filter->enableFlag=0;
}

int isEnableGpsFilter(GpsFilter filter){
	return filter.enableFlag;
}


Vector2D _debugBodyError;
NaviPosition _debugNaviError;
GpsFilterState _debugEstState;




NaviPosition updateGpsFilter(GpsFilter *filter,NaviPosition gpsPoint,Vector2D accel,Vector3D euler,float dt){
	GpsFilterState estState;
	NaviPosition naviError;
	Vector2D bodyError;
	
	

	
	
	estState=estNewGpsFilterState(*filter,accel,euler,dt);
	_debugEstState=estState;
	
	naviError.lat=gpsPoint.lat-estState.gpsPos.lat;	
	naviError.lon=gpsPoint.lon-estState.gpsPos.lon;
	
	_debugNaviError=naviError;

	bodyError=subNaviposition(estState.gpsPos,gpsPoint);
	bodyError=rotation2D(bodyError,-90+YAW); // quay sang he truc body.
	_debugBodyError=bodyError;
	filter->sta=correctNewGpsFilterState(*filter,naviError,bodyError,estState);
	return filter->sta.gpsPos;
}

NaviPosition getPositionViaGpsFilter(GpsFilter filter){
	return filter.sta.gpsPos;
}




