#include "UbloxParser.h"
#include "ByteConverter.h"
#include <string.h>


Content0107 parsePackage0107(u8 *content){
	Content0107 res;
	memcpy(&res.iTow,content,4);
	memcpy(&res.year,content+4,2);
	memcpy(&res.month,content+6,2);
	memcpy(&res.day,content+7,1);
	memcpy(&res.hour,content+8,1);
	memcpy(&res.min,content+9,1);
	memcpy(&res.sec,content+10,1);
	memcpy(&res.tAcc,content+12,4);
	memcpy(&res.nano,content+16,4);
	memcpy(&res.fixType,content+20,1);
	memcpy(&res.lon,content+24,4);
	memcpy(&res.lat,content+28,4);
	memcpy(&res.heightAboveElipsoid,content+32,4);
	memcpy(&res.heightAboveSea,content+36,4);
	memcpy(&res.hAcc,content+40,4);
	memcpy(&res.vAcc,content+44,4);
	memcpy(&res.ve1N,content+48,4);
	memcpy(&res.ve1E,content+52,4);
	memcpy(&res.ve1D,content+56,4);
	memcpy(&res.gSpeed,content+60,4);
	memcpy(&res.headMot,content+64,4);
	memcpy(&res.sAcc,content+68,4);
	memcpy(&res.headAcc,content+72,4);
	memcpy(&res.pDOP,content+76,2);
	memcpy(&res.headVeh,content+84,4);
	return res;
}

