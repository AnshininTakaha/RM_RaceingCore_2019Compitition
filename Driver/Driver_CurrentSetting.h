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
  |--FileName    : Driver_CurrentSetting.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-03-28               
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
#ifndef __DRIVER_CURRENTSETTING_H 
#define __DRIVER_CURRENTSETTING_H 


#include "BSP_Init.h"
#include "stm32f4xx.h"
/*底盘电流值发送*/
void Chassis_CurrentSetting(int16_t I1,int16_t I2,int16_t I3,int16_t I4);

/*云台电流和摩擦轮电流发送*/
void Cloud_And_Emitter_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch, \
int16_t I_Emitter, int16_t OVER);

/*云台电流值发送*/
void Cloud_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch);

void Cloud_CurrentSettingOnlyYaw(int16_t I_Yaw);

void Cloud_CurrentSettingOnlyPitchANDCarr(int16_t I_Pitch,int16_t I_Emitter);


/*拨弹电机电流值发送*/
void Cartridge_CurrentSetting(int16_t I_Emitter);

#endif	// __DRIVER_CURRENTSETTING_H
/*-----------------------------------file of end------------------------------*/


