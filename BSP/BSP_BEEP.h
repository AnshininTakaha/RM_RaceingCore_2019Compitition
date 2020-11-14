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
  |--FileName    : BSP_BEEP.h                                                
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
#ifndef __BSP_BEEP_H 
#define __BSP_BEEP_H

#include "Switch.h"
#include "stm32f4xx.h"
#include "RTOSinclude.h"

/* =========================== functions of begin =========================== */
/*��������ʼ��*/
void BEEP_Init(uint32_t psc, uint32_t arr);

/*��������TIM12�Ķ�Ӧ����ֵ*/
void SetBeepValue(uint16_t value);

/*���÷������ź�*/
void SetBeepSignal(uint8_t mode);
/* =========================== functions of end =========================== */


#endif	// __BSP_BEEP_H
/*-----------------------------------file of end------------------------------*/


