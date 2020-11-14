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
  |--FileName    : BSP_TIM.h                                                
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
#ifndef __BSP_TIM_H 
#define __BSP_TIM_H 

#include "Switch.h"
#include "stm32f4xx.h"

typedef void TIM_SetComparex_f(TIM_TypeDef* TIMx, uint32_t Compare);
extern TIM_SetComparex_f *const TIM_SetComparex[4];

/* =========================== functions of begin =========================== */
/*TIM5初始化*/
void TIM_PWM_Init(uint16_t prescaler, uint16_t period, uint16_t Pulse);

/*TIM1初始化*/
void TIM1_PWM_Init(u16 prescaler, u16 period, u16 Pulse);

/*舵机开关操控*/
void LIDSwitch(uint8_t mode);

/* =========================== functions of end =========================== */


#endif	// __BSP_TIM_H
/*-----------------------------------file of end------------------------------*/


