#include "Position.h"
#include "EulerUtil.h"
#include <math.h>


void initNaviaPosition(NaviPosition *position, float lon,float lat){
	position->lat=lat;
	position->lon=lon;
}
float getDistance(NaviPosition firstPoint,NaviPosition secondPoint){
	float dLat=(secondPoint.lat-firstPoint.lat)*DEG_TO_RAG_GAIN;
	float dLon=(secondPoint.lon-firstPoint.lon)*DEG_TO_RAG_GAIN;
	float lat2=secondPoint.lat*DEG_TO_RAG_GAIN;
	float lat1=firstPoint.lat*DEG_TO_RAG_GAIN;
	float a=sin(dLat/2)*sin(dLat/2)+sin(dLon/2)*sin(dLon/2)*cos(lat1)*cos(lat2);
	float c=2*atan2(sqrt(a),sqrt(1-a));
	return 6378137*c;
}



Vector2D subNaviposition(NaviPosition firstPoint,NaviPosition secondPoint){
	Vector2D res;
	float d=getDistance(secondPoint,firstPoint);
	float dLat=(secondPoint.lat-firstPoint.lat)*DEG_TO_RAG_GAIN;
	float dLon=(secondPoint.lon-firstPoint.lon)*DEG_TO_RAG_GAIN;
	float alpha=atan2(dLat,dLon);
	res.x=d*cos(alpha);
	res.y=d*sin(alpha);
	return res;
}


Vector2D add2DPosition(Vector2D position,float deltaX,float deltaY){
	Vector2D res;
	return res;
}
NaviPosition add2DToNaviPosition(NaviPosition navi,Vector2D posi){
	navi.lat+=posi.y/6378137*RAD_TO_DEG_GAIN;
	navi.lon+=posi.x/6378137*RAD_TO_DEG_GAIN;
	return navi;
}
