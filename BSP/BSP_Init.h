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
  |--FileName    : BSP_Init.h                                                
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
/*DBUS遥控器缓冲长度*/
#define RC_BUFFSIZE (18+2)

/*陀螺仪数据缓冲长度*/
#define GYIMU_BUFFSIZE 30

/*陀螺仪数据有效数据长度*/
#define GYIMU_PACKSIZE 18

/*裁判系统缓冲长度*/
#define Judge_BuffSIZE 300u

/*视觉缓冲长度*/
#define VISION_BUFFSIZE 16

/*新视觉缓冲长度*/
#define VISION_NEW_BUFFERSIZE 12

extern uint8_t DBUS_DataBuff[RC_BUFFSIZE];
extern uint8_t GYIMU_RXBuff[GYIMU_BUFFSIZE];
extern uint8_t Judge_DataBuff[Judge_BuffSIZE];
extern uint8_t Vision_DataBuff[VISION_BUFFSIZE];
extern uint8_t Vision_DataBufferNew[VISION_NEW_BUFFERSIZE];
/* =========================== Module_Length of end =========================== */


/*BSP初始化*/
void Devices_Init(void);

/*摩擦轮初始化*/
void FrictionBSP_Init(void);

/*陀螺仪初始化*/
void IMUBSP_Init(void);

/*DR16遥控器初始化*/
void DR16BSP_Init(void);

/*裁判系统初始化*/
void JudgeBSP_Init(void);

/*视觉初始化*/
void VisionBSP_Init(void);

/*舵机初始化*/
void ServoBSP_Init(void);
#endif	// __BSP_INIT_H
/*-----------------------------------file of end------------------------------*/


