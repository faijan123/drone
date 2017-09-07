#include "ImuCalibrate.h"


void initImuCalibrator(ImuCalibrator *calibrator,Vector3DInt16_t offset){
	calibrator->offset=offset;
}

Vector3DInt16_t debug_In,debugOut,deBug_offset;

Vector3DInt16_t calibrate(ImuCalibrator calibrator,Vector3DInt16_t in){
	return subVector3D16(in,calibrator.offset);
}


