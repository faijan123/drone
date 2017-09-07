#include "Printer.h"
#include "Uart.h"

struct __FILE 
{
  int handle;                 
};
FILE __stdout;
FILE __stdin;

int fputc(int ch1, FILE *f) 
{
  sendByteViaUart4((uint8_t)ch1);
  return ch1;
}

void initPrinter(void)
{
	initUart4(9600);
}


void printVector(Vector3D vector)
{
	printf("%f %f %f ",vector.roll,vector.pitch,vector.yaw);
}

void printVectorInt16_t(Vector3DInt16_t vector)
{
	printf("%d %d %d ",vector.roll,vector.pitch,vector.yaw);
}
