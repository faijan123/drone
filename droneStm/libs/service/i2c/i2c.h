#ifndef i2c_h_
#define i2c_h_
#include "stm32f4xx.h"
#define i2cPointer I2C2
void initI2C(void);
void stopI2C(void);
void requestI2C(u8 address,u8 reg);
void readBytesViaI2C(u8 address,u8 *buffer,int length);
u8   readByteViaI2C(u8 address);
u8 	 requestAndReadByteViaI2C(u8 address,u8 reg);
void requestAndReadBytesViaI2C(u8 address,u8 reg,u8 *buffer,int length);
void writeBytesViaI2C(u8 address,u8 reg,u8 *buffer,int length);
void writeByteViaI2C(u8 address,u8 reg,u8 val);
void writeByteWithOutRegViaI2c(u8 address,u8 val);
void writeBytesWithOutRegViaI2c(u8 address,u8 *buffer,int length);


void requestI2CWithTimeOut(u8 address,u8 reg,int32_t *timeout);
void readBytesViaI2CWithTimeOut(u8 address,u8 *buffer,int length,int32_t *timeout);
u8   readByteViaI2CWithTimeOut(u8 address,int32_t *timeout);
u8 	 requestAndReadByteViaI2CWithTimeOut(u8 address,u8 reg,int32_t *timeout);
void requestAndReadBytesViaI2CWithTimeOut(u8 address,u8 reg,u8 *buffer,int length,int32_t *timeout);
void writeBytesViaI2CWithTimeOut(u8 address,u8 reg,u8 *buffer,int length,int32_t* timeout);
void writeByteViaI2CWithTimeOut(u8 address,u8 reg,u8 val,int32_t *timeout);
void writeByteWithOutRegViaI2cWithTimeOut(u8 address,u8 val,int32_t *timeout);
void writeBytesWithOutRegViaI2cWithTimeOut(u8 address,u8 *buffer,int length,int32_t *timeout);



#endif

