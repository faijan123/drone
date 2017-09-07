#ifndef UBXPackage_h_
#define UBXPackage_h_


#define SYMBOL_1 0xB5
#define SYMBOL_2 0x62

#include "stm32f4xx.h"

typedef struct UbxHeader{
	u8 _class;
	u8 id;
	u16 length;
}UbxHeader;


typedef struct UbxChecksum{
	u8 ckA,ckB;
}UbxChecksum;


typedef struct UbxPackage{
	UbxHeader header;
	u8 *content;
	UbxChecksum checksum;
}UbxPackage;



void initUbxHeader(UbxHeader *header,u8 _class,u8 id,u16 length);
void createUbxPackage(UbxPackage *package,UbxHeader header,u8 *content);
void createUbxPackageWithoutContent(UbxPackage *package,UbxHeader header);
void copyUbxPackage(UbxPackage *des,UbxPackage source);
void reCreateUbxPackage(UbxPackage *package,UbxHeader header);

void deleteUbxPackage(UbxPackage *package);

int isUbxPackageNull(UbxPackage *package);


int equalUbxPackage(UbxPackage package1,UbxPackage package2);
int equalUbxHeader(UbxHeader spec1,UbxHeader spec2);
int equalUbxChecksum(UbxChecksum cs1,UbxChecksum cs2);

void ubxPackageToBytes(UbxPackage package,u8 *out);
int getSizeUbxPackage(UbxPackage package);

#endif
