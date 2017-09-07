#include "GpsUtil.h"
#include "Translate.h"

Vector2D earthNaviBodyNavi(NaviPosition pos,float yaw){
	Vector2D tem;
	tem.x=pos.lon;
	tem.y=pos.lat;
	return rotation2D(tem,-90+yaw);
}


NaviPosition bodyNaviToEarthNavi(Vector2D vec,float yaw){
	Vector2D tem;
	NaviPosition navi;
	tem=rotation2D(vec,90-yaw);
	navi.lon=tem.x;
	navi.lat=tem.y;
	return navi;
}

