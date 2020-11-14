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
  |--FileName    : Control_Chassis.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-03-27               
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
#ifndef __CONTROL_CHASSIS_H 
#define __CONTROL_CHASSIS_H 

#include "stm32f4xx.h"
#include "Driver_PID.h"
#include "Driver_Analysis.h"

/*低通滤波参数*/
#define Fif_Factor 0.1f  
#define Filter_LowFilter 0.4f

/*电流计算变换单位*/
#define CurrentUnit 1000
/*最大速度控制*/
#define Chassis_MaxSpeed_Y	8000.0f		
#define Chassis_MaxSpeed_X	8000.0f		
#define Chassis_MaxSpeed_W	8000.0f		
extern float AngleRead,IMUAngleRead,IMU_PI_AngleRead;;
extern float TempPush;
extern float angle;
extern float swing_time;
typedef struct
{
	/*遥控模式，用遥控右遥杆*/
	uint8_t RCmodeswitch;
	
	/*合并到PC结构体里面*/
//	/*PC的控制模式*/
//	uint8_t PCmodeswitch;

	float Filter_LPFfactor;
	float xPF;
	float yPF;
	float zPF;
	
  /*跟随相关数据*/
	positionpid_t Fowllow_Attitude_pid;
	float FollowYawRaw;
	float FollowYawLPF;
	
	/*超功率标志位*/
	uint8_t Power_OverflowFlag;
  /*预超功率标志位*/
  uint8_t PrePower_OverflowFlag;
	
}Chassis_t;

extern Chassis_t Chassis;

/*底盘PID初始化*/
#define IncInit_Wheel \
{\
	5.5,\
	2.5f,\
	0.0f,\
	16000,\
	1000,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	&IncrementalPID_Calculation,\
}\

/*底盘PID初始化*/
#define IncInit_WheelLow \
{\
	1.5f,\
	2.5f,\
	0.0f,\
	16000,\
	1000,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	&IncrementalPID_Calculation,\
}\

/*底盘跟随PID初始化*/
#define PosInit_Follow \
{\
	7000.0f,\
	0.0f,\
	0.0f,\
	{0,0,0,0},\
	{0,0,0,0},\
	{0,0,0,0},\
	8000,\
	500,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	&PositionPID_Calculation,\
}\


#define PosInit_FollowSwing \
{\
	7000.0f,\
	0.0f,\
	0.0f,\
	{0,0,0,0},\
	{0,0,0,0},\
	{0,0,0,0},\
	8000,\
	500,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	0,\
	&PositionPID_Calculation,\
}\

/*获取遥控器对底盘的数据赋值*/
void Chassis_Judgement(uint8_t switchmode);

/*底盘处理函数*/
void Chassis_Process(float Input_Vx, float Input_Vy, float Input_VOmega, \
uint8_t switchmode);

/*麦轮解算*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);

/*功率限制*/
void Power_Limited(void);

///*功率限制*/
//void Chassis_PowerLimit(RM3508_t *RM3508, float CurrentLimit);

///*功率限制新*/
//void Power_Limit(float Cur_limit);

#endif	// __CONTROL_CHASSIS_H
/*-----------------------------------file of end------------------------------*/


