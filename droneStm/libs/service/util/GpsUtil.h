#ifndef GpsUtil_h_
#define GpsUtil_h_
#include "Position.h"

Vector2D earthNaviBodyNavi(NaviPosition pos,float yaw);
NaviPosition bodyNaviToEarthNavi(Vector2D vec,float yaw);
#endif
