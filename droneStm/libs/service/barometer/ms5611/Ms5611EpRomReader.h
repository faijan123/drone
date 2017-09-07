/*
@author:truonglx,tecasoftandtech
@des: ms5611 co chua cac config trong eprom, file Ms5611EpRomReader dinh nghia cac ham lay du lieu tu eprom ms5611.
*/


#ifndef Ms5611EpRomReader_h_
#define Ms5611EpRomReader_h_
#include "stm32f4xx.h"

typedef struct Ms5611EpromReader{
 u16 c1,c2,c3,c4,c5,c6;
}Ms5611EpromReader;

void readMs5611Eprom(Ms5611EpromReader *reader);
void copyMs5611Eprom(Ms5611EpromReader reader,u16 *out);

#endif

