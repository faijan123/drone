#ifndef ImuCalibrate_h_
#define ImuCalibrate_h_
#include <Vector3D.h>

typedef struct ImuCalibrator
{
	Vector3DInt16_t offset;
}ImuCalibrator;

void 							initImuCalibrator(ImuCalibrator *calibrator,Vector3DInt16_t offset);
Vector3DInt16_t 	calibrate(ImuCalibrator calibrator,Vector3DInt16_t in);
#endif
