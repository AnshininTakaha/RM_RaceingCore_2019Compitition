/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无 & 璨，                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Driver_Flash.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-03-26               
  |--Libsupports : 
  |--Description :                                                       
  |--FunctionList                                                       
  |-------1. ....                                                       
  |          <version>:                                                       
  |     <modify staff>:                                                       
  |             <data>:                                                       
  |      <description>:                                                        
  |-------2. ...                                                       
  |-----------------------------declaration of end-----------------------------|
 **/
#ifndef __DRIVER_FLASH_H 
#define __DRIVER_FLASH_H 



#include "BSP_Init.h"
#include "RTOSinclude.h"

//typedef struct Flashing_Controling
//{
//	uint8_t 
//}	
/*帧率刷新*/

typedef struct
{
		uint16_t TaskControl_State;
	  uint16_t TaskControl_OfflineSet;
		uint16_t CANRecevie_State;
		uint16_t CANRecevie_OfflineSet;
		uint16_t CANSender_State;
		uint16_t CANSender_OfflineSet;
	
}TaskState_t;
extern TaskState_t TaskState;

void DeviceFlash(void);

void LEDSingleLight(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,uint8_t single, int TimeNow);
void SetLedSingle(void);
#endif	// __DRIVER_FLASH_H
/*-----------------------------------file of end------------------------------*/


