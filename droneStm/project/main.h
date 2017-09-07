
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "Uart.h"
#include "FlyControlBlock.h"
#include "TimeChecker.h"
#include "i2c.h"
#include "DroneController.h"
#include "MotorControlBlock.h"
#include "ImuBlock.h"
#include "EulerBlock.h"
#include "Delay.h"
#include "TimeUtil.h"
#include "ArrayUtil.h"
#include "TcTime.h"
#include "GyroCalibrationProgram.h"
#include "AltitudeCalibrationProgram.h"
#include "AltitudeBlock.h"
#include "Buffer.h"
#include "ArrayUtil.h"
#include "Quadcore.h"
#include "GpsBlock.h"

#define FREQUENCE_UPDATE_MAIN 250

DeltaTimeChecker timeCheckerMainLoop;



#endif 
