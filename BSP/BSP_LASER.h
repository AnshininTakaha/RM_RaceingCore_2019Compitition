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
  |--FileName    : BSP_LASER.h                                                
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
#ifndef __BSP_LASER_H 
#define __BSP_LASER_H 

#include "Switch.h"
#include "stm32f4xx.h"

/* =========================== functions of begin =========================== */
/*�����ʼ��*/
void Laser_Init(void);

#define LASER_ON()				GPIO_SetBits(GPIOA, GPIO_Pin_12)
#define LASER_OFF()				GPIO_ResetBits(GPIOA, GPIO_Pin_12)
#define LASER(isOn) 			GPIO_WriteBit(GPIOA,GPIO_Pin_12,(BitAction)isOn)
/* =========================== functions of end =========================== */


#endif	// __BSP_LASER_H
/*-----------------------------------file of end------------------------------*/


