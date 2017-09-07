#ifndef UartReceiver_h_
#define UartReceiver_h_
#include "stm32f4xx.h"


uint8_t readByteViaUart4(void);
uint8_t readByteViaUart6(void);
uint8_t readByteViaUart7(void);
uint8_t readByteViaUart(int uart);

void readBytesViaUart4(uint8_t *out,int length);
void readBytesViaUart6(uint8_t *out,int length);
void readBytesViaUart7(uint8_t *out,int length);
void readBytesViaUart(int uart,u8 *out,int length);




u32 readBytesViaUart4WithTimeout(u8 *out,int length,u32 timeout);
u32 readBytesViaUart6WithTimeout(u8 *out,int length,u32 timeout);
u32 readBytesViaUart7WithTimeout(u8 *out,int length,u32 timeout);
u32 readBytesViaUartWithTimeout(int uart,u8 *out,int length,u32 timeout);
#endif
