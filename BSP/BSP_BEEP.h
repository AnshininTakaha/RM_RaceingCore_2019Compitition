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
  |--FileName    : BSP_BEEP.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-03-22               
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
#ifndef __BSP_BEEP_H 
#define __BSP_BEEP_H

#include "Switch.h"
#include "stm32f4xx.h"
#include "RTOSinclude.h"

/* =========================== functions of begin =========================== */
/*蜂鸣器初始化*/
void BEEP_Init(uint32_t psc, uint32_t arr);

/*快速设置TIM12的对应的数值*/
void SetBeepValue(uint16_t value);

/*设置蜂鸣器信号*/
void SetBeepSignal(uint8_t mode);
/* =========================== functions of end =========================== */


#endif	// __BSP_BEEP_H
/*-----------------------------------file of end------------------------------*/


