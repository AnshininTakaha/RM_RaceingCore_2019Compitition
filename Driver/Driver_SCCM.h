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
  |--FileName    : Driver_SCCM.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-04-20               
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
#ifndef __DRIVER_SCCM_H 
#define __DRIVER_SCCM_H 

#include "stm32f4xx.h"
#pragma anon_unions

//1.0版本电容充电上限
#define SCCM_Charge_MAX 80.0f
#define UseTo_Charge 60.0f
/*接受数据*/
typedef union
{
  uint8_t data[8];
  struct
	{
    float chassis_power;    /* 底盘功率，单位：W */
    uint8_t chassis_buff;   /* 底盘功率缓冲 */
    uint8_t cap_usable;    /* 电容可以进行输出 */
		int8_t cap_level;      /*电量百分比*/
  };
} SCCM_ReceiveData_t;

/*发送数据*/
typedef union{
  uint8_t data[8];
  struct{
    float charge_power;    /* 充电功率，单位：W ,范围 0-80W */
    uint8_t charge_enable; /* 充电使能 */
    uint8_t is_cap_output;  /* 使用电容供电 */
  };
}SCCM_SendData_t;

/*总结构体*/
typedef struct{
  SCCM_ReceiveData_t receiveData;
  SCCM_SendData_t sendData;
  
  uint16_t UpdateFrame;   /* 帧率 */
  uint8_t UpdateFlag;     /* 更新标志 */
  uint8_t OFFLINE_SET;        /* 掉线标记 */
}SCCM_t;

extern SCCM_t SCCM;

/*超级电容管理*/
void SCCM_StateSetting(float UseToCharge, uint8_t ChargeSet, uint8_t CapOutputSet);

#endif	// __DRIVER_SCCM_H
/*-----------------------------------file of end------------------------------*/


