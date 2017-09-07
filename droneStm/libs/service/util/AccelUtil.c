#include "AccelUtil.h"
#include "EulerUtil.h"
#include "Constance.h"

float getRealAccelX(float ax,float pitch){
	if(pitch==90)
		return 0;
	return (ax-G*SinDeg(-pitch))/CosDeg(pitch);
}
float getRealAccelY(float ay,float roll){
	if(roll==90)
		return 0;
	return (ay-G*SinDeg(roll))/CosDeg(roll);
}


