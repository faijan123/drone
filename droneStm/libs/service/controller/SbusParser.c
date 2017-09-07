#include "SbusParser.h"

#define SBUS_START_BYTE 	0x0F

#define SBUS_END_BYTE 		0x00

#define SBUS_LENGTH_FRAME 	25


typedef struct SbusParserState{

  int channels[16];
  uint8_t frame[25];
  uint8_t length;  
}SbusParserState;

SbusParserState sbusParser_state;

void sbusParser_parse();

void sbusParser_update(uint8_t val){

  if(sbusParser_state.length==0&&(val==SBUS_START_BYTE)){


     sbusParser_state.frame[0]= SBUS_START_BYTE;
     sbusParser_state.length++;
     return ;
  }

  if(sbusParser_state.length==SBUS_LENGTH_FRAME-1){
     
     
     if(val==SBUS_END_BYTE) 
        sbusParser_parse();
      sbusParser_reset();
     return ;
  }


  sbusParser_state.frame[sbusParser_state.length]=val;
  sbusParser_state.length++;

}


void sbusParser_reset(){

  sbusParser_state.length=0;
}


int  sbusParser_hasNewData(){

    return 0;
}

int  sbusParser_readData(){
    
    return 0;
}

/*-------------------------------------------------------------*/



void sbusParser_parse(){

  uint8_t* buffer = sbusParser_state.frame;
  int channels[16];
  channels[0]   = ((buffer[1]|buffer[2]<<8) & 0x07FF);   
  channels[1]   = ((buffer[2]>>3|buffer[3]<<5)  & 0x07FF);
  channels[2]   = ((buffer[3]>>6 |buffer[4]<<2 |buffer[5]<<10)  & 0x07FF);
  channels[3]   = ((buffer[5]>>1 |buffer[6]<<7) & 0x07FF);
  channels[4]   = ((buffer[6]>>4 |buffer[7]<<4) & 0x07FF);
  channels[5]   = ((buffer[7]>>7 |buffer[8]<<1 |buffer[9]<<9)   & 0x07FF);
  channels[6]   = ((buffer[9]>>2 |buffer[10]<<6) & 0x07FF);
  channels[7]   = ((buffer[10]>>5|buffer[11]<<3) & 0x07FF);
  channels[8]   = ((buffer[12]   |buffer[13]<<8) & 0x07FF);
  channels[9]   = ((buffer[13]>>3|buffer[14]<<5)  & 0x07FF);
  channels[10]  = ((buffer[14]>>6|buffer[15]<<2|buffer[16]<<10) & 0x07FF);
  channels[11]  = ((buffer[16]>>1|buffer[17]<<7) & 0x07FF);
  channels[12]  = ((buffer[17]>>4|buffer[18]<<4) & 0x07FF);
  channels[13]  = ((buffer[18]>>7|buffer[19]<<1|buffer[20]<<9)  & 0x07FF);
  channels[14]  = ((buffer[20]>>2|buffer[21]<<6) & 0x07FF);
  channels[15]  = ((buffer[21]>>5|buffer[22]<<3) & 0x07FF);
}
