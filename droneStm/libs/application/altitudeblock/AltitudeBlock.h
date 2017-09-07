/*
@author:truonglx
@des: AltitudeBlock, thuoc tang application.
Nhiem vu cua AltitudeBlock.
1. Cung cap cho tang tren va cac block khac thong tin ve: do cao,ap suat,nhiet do
2. La controller trung gian giua sensor va cac giai thuat cua do cao

Thay doi:
Moi su thay doi ve phan cung va giai thuat duoc thuc hien tai AltitudeBlock.

version1:

1. Sensor: Ms5611
2. Algorithm: 

version2:


*/

#ifndef AltitudeBlock_h_
#define AltitudeBlock_h_
int 		isInitAltitudeBlock(void);
void 		initAltitudeBlock(void);
void 		updateAltitudeBlock(void);
float 	getAltitudeFromAltitudeBlock(void);
#endif
