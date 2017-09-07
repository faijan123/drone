#include "Translate.h"
#include "EulerUtil.h"


Vector2D rotation2D(Vector2D position,float al){
	Vector2D res;
	res.x=position.x*CosDeg(al)-position.y*SinDeg(al);
	res.y=position.x*SinDeg(al)+position.y*CosDeg(al);
	return res;
}
