//#include "PinStateReader.h"

//uint16_t pinStateReader_I;
//uint16_t pinStateReader_U;

//void initDMA(void){
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
//    DMA_InitTypeDef  DMA_InitStructure;
//    //reset DMA1 channe1 to default values;
//    DMA_DeInit(DMA1_Stream0);
//    //channel will be used for memory to memory transfer
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//    //setting normal mode (non circular)
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
//    //medium priority
//    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//    //source and destination data size word=32bit
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//    //automatic memory destination increment enable.
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//    //source address increment disable
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//    //Location assigned to peripheral register will be source
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//    //chunk of data to be transfered
//    DMA_InitStructure.DMA_BufferSize = ARRAYSIZE;
//    //source and destination start addresses
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR;
//    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_values;
//    //send values to DMA registers
//    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
//    // Enable DMA1 Channel Transfer Complete interrupt
//    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
//    DMA_Cmd(DMA1_Channel1, ENABLE); //Enable the DMA1 - Channel1
//    NVIC_InitTypeDef NVIC_InitStructure;
//    //Enable DMA1 channel IRQ Channel */
//    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
// 
//}
//void initPinStateReaderWithDMA(void){

//}

//uint16_t getI(void){

//}
//uint16_t getU(void){

//}


