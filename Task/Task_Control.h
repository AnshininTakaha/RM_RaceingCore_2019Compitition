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
  |--FileName    : Task_Control.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
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

/*任务控制初始化函数*/
void Control_TaskCreate(void);

/* =========================== Aiming of begin =========================== */
/*Aiming自瞄控制句柄*/
extern TaskHandle_t Aiming_Handler;

/*自瞄控制队列*/
extern QueueHandle_t AimingRxQueue;

/*自瞄控制函数*/
extern void Aiming_Task(void *pvParameters);
/* =========================== Aiming of end =========================== */

/* =========================== ANO of begin =========================== */
/*ANO任务控制句柄*/
extern TaskHandle_t ANO_Handler;

/*ANO任务控制函数*/
extern void ANO_Task(void *pvParameters);
/* =========================== ANO of end =========================== */

/* =========================== DeviceFlash of begin =========================== */
/*帧率刷新控制句柄*/
extern TaskHandle_t Device_FlashHandler;

/*帧率刷新控制函数*/
extern void Devices_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */

/* =========================== DeviceFlash of begin =========================== */
/*帧率刷新控制句柄*/
extern TaskHandle_t Control_Handler;

/*帧率刷新控制函数*/
extern void Control_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */

/* =========================== Judgement of begin =========================== */
/*键位变换句柄*/
extern TaskHandle_t PC_Handler;

/*键位变换控制函数控制函数*/
extern void PC_ControlTask(void *pvParameters);
/* =========================== Judgement of end =========================== */

/* =========================== Judgement of begin =========================== */
/*LED扫描提示标志位*/
extern  TaskHandle_t Single_Handler;

/*LED扫描提示标志位*/
extern void Single_Task(void *pvParameters);
/* =========================== Judgement of end =========================== */

extern float TimeCounter;
extern uint16_t BulletNumberOutput;
#endif	// __TASK_CONTROL_H
/*-----------------------------------file of end------------------------------*/


