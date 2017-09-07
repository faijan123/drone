#include "FlashWriter.h"
#include "stm32f4xx_flash.h"


int writeByteToFlash(uint32_t addr,uint8_t val){
//	FLASH_Status status;
//	status=FLASH_EraseSector(addr,val);
//	FLASH_ProgramByte(addr,val);
//	return status==FLASH_COMPLETE; 
	
	return 0;
}

int initFlashWriter(){
//	FLASH_Unlock();
	
	return 1;
}

int writeToFlash(uint32_t addr,uint8_t *buffer,int offset,int length){
//	int numberByte;
//	if(FLASH_GetStatus()!=FLASH_COMPLETE)
//		return 0;
//	do{
//		if(!writeByteToFlash(addr+numberByte,buffer[offset+numberByte]))
//			return numberByte;
//	}while(numberByte<length);
//	return numberByte;
	return 0;
}

void closeWriter(){
//	FLASH_Lock(); 
}


