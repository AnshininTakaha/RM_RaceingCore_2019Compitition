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
  |--FileName    : BSP_Init.h                                                
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
#ifndef __BSP_INIT_H 
#define __BSP_INIT_H 

#include "BSP_CAN.h"
#include "BSP_USART.h"
#include "BSP_LED.h"
#include "BSP_LASER.h"
#include "BSP_BEEP.h"
#include "BSP_TIM.h"
#include "BSP_MATH.h"

/* =========================== Module_Length of begin =========================== */
/*DBUSң�������峤��*/
#define RC_BUFFSIZE (18+2)

/*���������ݻ��峤��*/
#define GYIMU_BUFFSIZE 30

/*������������Ч���ݳ���*/
#define GYIMU_PACKSIZE 18

/*����ϵͳ���峤��*/
#define Judge_BuffSIZE 300u

/*�Ӿ����峤��*/
#define VISION_BUFFSIZE 16

/*���Ӿ����峤��*/
#define VISION_NEW_BUFFERSIZE 12

extern uint8_t DBUS_DataBuff[RC_BUFFSIZE];
extern uint8_t GYIMU_RXBuff[GYIMU_BUFFSIZE];
extern uint8_t Judge_DataBuff[Judge_BuffSIZE];
extern uint8_t Vision_DataBuff[VISION_BUFFSIZE];
extern uint8_t Vision_DataBufferNew[VISION_NEW_BUFFERSIZE];
/* =========================== Module_Length of end =========================== */


/*BSP��ʼ��*/
void Devices_Init(void);

/*Ħ���ֳ�ʼ��*/
void FrictionBSP_Init(void);

/*�����ǳ�ʼ��*/
void IMUBSP_Init(void);

/*DR16ң������ʼ��*/
void DR16BSP_Init(void);

/*����ϵͳ��ʼ��*/
void JudgeBSP_Init(void);

/*�Ӿ���ʼ��*/
void VisionBSP_Init(void);

/*�����ʼ��*/
void ServoBSP_Init(void);
#endif	// __BSP_INIT_H
/*-----------------------------------file of end------------------------------*/


