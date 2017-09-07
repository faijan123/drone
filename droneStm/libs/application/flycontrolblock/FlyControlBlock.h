/*
@author: truonglx,tecasoftandtech
@des: Dieu khien qua trinh bay quadcopter.
buoc 1. Nhan du tin hieu dieu khien
buoc 2. Phan tich tin hieu, dua ra quyet dinh phu hop.

FlyControlBlock bao gom cac thanh phan
1. AnalystControl: Phan tich tin hieu dieu khien, dua ra action phu hop
2. GenaralControl: Cac ham dung chung, la cac ham ma o che do bay nao cung su dung toi
3. FlyMode: Cac che bo bay
3.1. BasicFlyMode: Che do bay co ban
3.2. HoldAltitudeMode: Che bo bay treo do cao.




/----------------------quan li version----------------------------/

Version(FlyControlBlock.h)=1

*/


#ifndef FlyControlBlock_h_
#define FlyControlBlock_h_
void initFlyControlBlock(void);
void updateFlyControlBlock(float *pwmOut);
#endif
