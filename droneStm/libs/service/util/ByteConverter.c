#include "ByteConverter.h"
#include <string.h>
float getFloat(u8 *data){
	float res;
	memcpy(&res,data,sizeof(float));
	return res;
}

long getLong(u8 *data){
	long res;
	memcpy(&res,data,sizeof(long));
	return res;
}


