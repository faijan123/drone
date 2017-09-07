#include "SystemTick.h"
#include "stdio.h"
#define SystemTickClock 1000000
SystemTickSubcriber *systemTickSubcriber[100];
int numberSubcriber=0;
int flagInitSystemTick=0;


void disableSystemTickInterrupt()
{
	SysTick->CTRL=0;
}


void initSystemTick()
{

	SysTick_Config(SystemCoreClock / SystemTickClock);
	flagInitSystemTick=1;
}


void checkAndInitSystemTick()
{
	if(!flagInitSystemTick)
		initSystemTick();
}

int checkSystemTickSubcriber(SystemTickSubcriber *subcriber)
{
	return subcriber->available&&(subcriber->current>0||(subcriber->current==0&&subcriber->unit>=0));
}


void SysTick_Handler(void)
{
	
		for(int i=0;i<numberSubcriber;i++)
			if(checkSystemTickSubcriber(systemTickSubcriber[i]))
				systemTickSubcriber[i]->current+=systemTickSubcriber[i]->unit;
}




/*---------------------------------------------public-----------------------------------------------------------*/
void registerSystemTickSubcriber(SystemTickSubcriber *subcriber)
{
	checkAndInitSystemTick();
	systemTickSubcriber[numberSubcriber]=subcriber;
	numberSubcriber++;
}


void disableSystemTickSubcriber(SystemTickSubcriber *subcriber)
{
	subcriber->available=0;
}


void enableSystemTichSubcriber(SystemTickSubcriber *subcriber)
{
	subcriber->available=1;
}



