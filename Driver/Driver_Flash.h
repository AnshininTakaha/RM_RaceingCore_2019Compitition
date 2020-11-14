/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,���� & 貣�                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Driver_Flash.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
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
/*֡��ˢ��*/

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


