#ifndef UbloxParser_h_
#define UbloxParser_h_
#include "UBXPackage.h"
#include "Ublox.h"

typedef struct Content0107{
	long iTow;
	u16 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 min;
	u8 sec;
	u32 tAcc;
	long nano;
	u8 fixType;
	long lon,lat;
	long heightAboveElipsoid;
	long heightAboveSea;
	u32 hAcc;
	u32 vAcc;
	long ve1N;
	long ve1E;
	long ve1D;
	long gSpeed;
	long headMot;
	u32 sAcc;
	u32 headAcc;
	u16 pDOP;
	long headVeh;
}Content0107;

Content0107 parsePackage0107(u8 *content);

#endif
