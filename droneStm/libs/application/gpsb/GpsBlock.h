#ifndef GpsBlock_h_
#define GpsBlock_h_
#include "Position.h"
void initGpsBlock(void);
int isGpsBlockReadly(void);
int updateGpsBlock(void);
NaviPosition getPositionViaGpsBlock(void);
void enableGpsBlock(void);
void disableGpsBlock(void);
int isGpsBlockEnable(void);
#endif

