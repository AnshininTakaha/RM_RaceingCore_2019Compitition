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
  |--FileName    : Driver_Galvanoment.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-03-26               
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
#ifndef __DRIVER_GALVANOMENT_H 
#define __DRIVER_GALVANOMENT_H 

#pragma anon_unions


#include "RTOSinclude.h"
#include  "stm32f4xx.h"

typedef struct 
{
  union
  {
    uint8_t Galvanometer_Buff[8];
    struct 
    {
      /*功率基本数值*/
      float chassisVolt;
			float chassisCurrent;
			float chassisPower;
			float chassisPowerBuffer;

      /*缓冲功率*/
      float ExpectPowerTiring;
      /*上一次功率数值*/
      float LastchassisPowerBuffer;
			float LLastchassisPowerBuffer;
      /*增长斜率*/
      float Growthslope;
      
      /*预测功率*/
      float ForecastPower;

      /*超功率标志位*/
      float OverPowerState;

      /*准备超功率标志位*/
      float PreOverPowerState;

    };
  }data;
			/*帧率控制（判断是否离线）*/
				uint8_t UpdateFlag;
				uint16_t UpdateFrame;
				uint8_t OFFLINE_SET;
}Galvanometer_t;

/*电流计的基本数值储存体*/
extern Galvanometer_t Galvanometer;

/*超功率算法*/
void Galvanometer_Calculation(Galvanometer_t* Galvanometer);

#endif	// __DRIVER_GALVANOMENT_H
/*-----------------------------------file of end------------------------------*/


