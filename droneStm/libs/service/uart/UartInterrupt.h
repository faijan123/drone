#ifndef UartInterrupt_h_
#define UartInterrupt_h_
#include "stm32f4xx.h"






int readBytesBufferOfUart4(uint8_t *out,int length);
int readBytesBufferOfUart6(uint8_t *out,int length);
int readBytesBufferOfUart7(u8 *out,int length);
int readBytesBufferOfUart(int uart,u8 *out,int length);

u8 readByteBufferOfUart4(void);
u8 readByteBufferOfUart6(void);
u8 readByteBufferOfUart7(void);
u8 readByteBufferOfUart(int uart);

u8 getByteBufferOfUart4(int position);
u8 getByteBufferOfUart6(int position);
u8 getByteBufferOfUart7(int position);
u8 getByteBufferOfUart(int uart,int position);

u8 getBytesBufferOfUart4(u8 *out,int position,int length);
u8 getBytesBufferOfUart6(u8 *out,int position,int length);
u8 getBytesBufferOfUart7(u8 *out,int position,int length);
u8 getBytesBufferOfUart(int uart,u8 *out,int position,int length);



int getNumberByteInBufferOfUart(int uart);
int getNumberByteInBufferOfUart4(void);
int getNumberByteInBufferOfUart6(void);
int getNumberByteInBufferOfUart7(void);


void removeBytesInBufferOfUart(int uart,int length);
void removeBytesInBufferOfUart4(int length);
void removeBytesInBufferOfUart6(int length);
void removeBytesInBufferOfUart7(int length);


void clearBufferOfUart(int uart);
void clearBufferOfUart4(void);
void clearBufferOfUart6(void);
void clearBufferOfUart7(void);

int isBufferOfUartEmpty(int uart);
int isBufferOfUart4Empty(void);
int isBufferOfUart6Empty(void);
int isBufferOfUart7Empty(void);

int isDataInBufferOfUartReadlly(int uart);
int isDataInBufferOfUart4Readlly(void);
int isDataInBufferOfUart6Readlly(void);
int isDataInBufferOfUart7Readlly(void);

int findSubArrayInBufferOffUart(int uart,u8 *subArray,int length);

#endif
