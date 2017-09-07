#include "FlashReader.h"
#include "stm32f4xx_flash.h"


int initFlashReader(){
//	FLASH_Unlock();
//	return FLASH_GetStatus()==FLASH_COMPLETE;
	return 0;
}
int readFromFlash(uint32_t addr,uint8_t *buffer,int offset,int lenhth){
	return 0;
}
void closeReader(){
	return;
}
