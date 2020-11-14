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
  |--FileName    : BSP_TIM.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
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
/*TIM5��ʼ��*/
void TIM_PWM_Init(uint16_t prescaler, uint16_t period, uint16_t Pulse);

/*TIM1��ʼ��*/
void TIM1_PWM_Init(u16 prescaler, u16 period, u16 Pulse);

/*������زٿ�*/
void LIDSwitch(uint8_t mode);

/* =========================== functions of end =========================== */


#endif	// __BSP_TIM_H
/*-----------------------------------file of end------------------------------*/


