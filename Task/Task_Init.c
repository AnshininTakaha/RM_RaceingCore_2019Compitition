/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无 & 璨,                         |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)      |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Task_Init.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无 & 璨                                                     
  |--Date        : 2019-03-23             
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
#include "Task_Init.h" 

#include "Task_CAN.h"
#include "Task_Control.h"

#include "Control_Cloud.h"
#include "Control_PC.h"

//#include "Driver_Power.h"

#include "BSP_Init.h"

/*开始任务句柄*/
TaskHandle_t StartTaskHandler = NULL;

/**
  * @Data    2019-02-18 20:50
  * @brief   开始任务函数
  * @param   void *pvParameters
  * @retval  void
  */
void TaskStart(void *pvParameters)
{
	/*进入临界区*/
	taskENTER_CRITICAL();
	
	/*底层数据初始化*/
	Devices_Init();
	
	/*PC控制初始化*/
	PC_Init();
	
	/*延时保证IMU数据稳定*/
  vTaskDelay(2000 / portTICK_RATE_MS);
	
	/*创建CAN任务*/
	CAN_TaskCreate();
	
	/*创建控制任务*/
	Control_TaskCreate();
	
	/*舵机初始化的时候不动*/
	LIDSwitch(1);
	/*功率初始化*/
	
	
	/*删除初始化任务*/
  vTaskDelete(StartTaskHandler);
	
	/*退出临界区*/
  taskEXIT_CRITICAL();
	
	
	
	
	
}

/*-----------------------------------file of end------------------------------*/


