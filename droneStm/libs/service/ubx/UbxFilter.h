#ifndef UbxFilter
#define UbxFilter
#include "UbxPackage.h"



typedef struct UBXFilter{
	UbxHeader *headers;
	int sizeFilter;
	int numberSpec;
	int enableFlag;
}UBXFilter;


void initUBXFilter(UBXFilter *filter);
void addUBXSpec(UBXFilter *filter,UbxHeader spec);
void removeUBXSpec(UBXFilter *filter,UbxHeader spec);
int passPackage(UBXFilter filter,UbxHeader spec);
void deleteUBXFilter(UBXFilter *filter);
int isEnableUBXFilter(UBXFilter filter);
void copyFilter(UBXFilter *des,UBXFilter *source);
void enableUBXFilter(UBXFilter *filter);
void disableUBXFilter(UBXFilter *filter);
#endif

