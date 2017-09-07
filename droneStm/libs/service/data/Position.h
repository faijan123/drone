#ifndef Position_h_
#define Position_h_
#include "Vector2D.h"
typedef struct NaviPosition{
	float lon,lat;
}NaviPosition;



void initNaviaPosition(NaviPosition *position, float lon,float lat);
float getDistance(NaviPosition firtPoint,NaviPosition secondPoint);
Vector2D subNaviposition(NaviPosition firstPoint,NaviPosition secondPoint);
Vector2D add2DPosition(Vector2D position,float deltaX,float deltaY);
NaviPosition add2DToNaviPosition(NaviPosition navi,Vector2D posi);
#endif


