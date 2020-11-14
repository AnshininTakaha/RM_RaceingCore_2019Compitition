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
  |--FileName    : Task_Control.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
  |--Date        : 2019-03-24               
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
#ifndef __TASK_CONTROL_H 
#define __TASK_CONTROL_H 


#include "Switch.h"
#include "RTOSinclude.h"
#include "stm32f4xx.h"

/*������Ƴ�ʼ������*/
void Control_TaskCreate(void);

/* =========================== Aiming of begin =========================== */
/*Aiming������ƾ��*/
extern TaskHandle_t Aiming_Handler;

/*������ƶ���*/
extern QueueHandle_t AimingRxQueue;

/*������ƺ���*/
extern void Aiming_Task(void *pvParameters);
/* =========================== Aiming of end =========================== */

/* =========================== ANO of begin =========================== */
/*ANO������ƾ��*/
extern TaskHandle_t ANO_Handler;

/*ANO������ƺ���*/
extern void ANO_Task(void *pvParameters);
/* =========================== ANO of end =========================== */

/* =========================== DeviceFlash of begin =========================== */
/*֡��ˢ�¿��ƾ��*/
extern TaskHandle_t Device_FlashHandler;

/*֡��ˢ�¿��ƺ���*/
extern void Devices_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */

/* =========================== DeviceFlash of begin =========================== */
/*֡��ˢ�¿��ƾ��*/
extern TaskHandle_t Control_Handler;

/*֡��ˢ�¿��ƺ���*/
extern void Control_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */

/* =========================== Judgement of begin =========================== */
/*��λ�任���*/
extern TaskHandle_t PC_Handler;

/*��λ�任���ƺ������ƺ���*/
extern void PC_ControlTask(void *pvParameters);
/* =========================== Judgement of end =========================== */

/* =========================== Judgement of begin =========================== */
/*LEDɨ����ʾ��־λ*/
extern  TaskHandle_t Single_Handler;

/*LEDɨ����ʾ��־λ*/
extern void Single_Task(void *pvParameters);
/* =========================== Judgement of end =========================== */

extern float TimeCounter;
extern uint16_t BulletNumberOutput;
#endif	// __TASK_CONTROL_H
/*-----------------------------------file of end------------------------------*/


