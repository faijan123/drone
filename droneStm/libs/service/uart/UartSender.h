#ifndef UartSender_h_
#define UartSender_h_
#include "stm32f4xx.h"

void sendByteViaUart4(u8 value);
void sendByteViaUart6(u8 value);
void sendByteViaUart7(u8 value);
void sendByteviaUart(int uart,u8 value);

void sendBytesViaUart4(u8 *value,int length);
void sendBytesViaUart6(u8 *value,int length);
void sendBytesViaUart7(u8 *value,int length);
void sendBytesviaUart(int uart,u8 *value,int length);

u32 sendByteViaUart4WithTimeout(u8 value,u32 timeout);
u32 sendByteViaUart6WithTimeout(u8 value,u32 timeout);
u32 sendByteViaUart7WithTimeout(u8 value,u32 timeout);
u32 sendByteViaUartWithTimeout(int uart,u8 value,u32 timeout);

u32 sendBytesViaUart4WithTimeout(u8 *values,int length,u32 timeout);
u32 sendBytesViaUart6WithTimeout(u8 *values,int length,u32 timeout);
u32 sendBytesViaUart7WithTimeout(u8 *values,int length,u32 timeout);
u32 sendBytesviaUartWithTimeout(int uart,u8 *values,int length,u32 timeout);

#endif
