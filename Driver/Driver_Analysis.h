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
  |--FileName    : Driver_Analysis.h                                                
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
#ifndef __DRIVER_ANALYSIS_H 
#define __DRIVER_ANALYSIS_H 



#include "stm32f4xx.h"
#include "string.h"

#define PLATFORM_A_TURN 8192
#define UNDULATION_A_TURN 8192

/*对应电机ID宏定义*/
#define Receive_MotorLeftFront 0x201
#define Receive_MotorRightFront 0x202
#define Receive_MotorRightBack 0x203
#define Receive_MotorLeftBack 0x204
#define Receive_CloudYAW 0x205
#define Receive_CloudPITCH 0x206
#define Receive_Carriage 0x207
#define Receive_Galvanoment 0x401
#define Receive_SCCM 0x600
#define Recrive_CloudIMU 0x413 
#define Receive_ChassisIMU 0x414
/* =========================== RM3508 of begin =========================== */
typedef struct
{
	/*反馈（输入）部分*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realCurrent;
	int16_t realTempeture;
	
	/*赋值（输出）部分*/
	int16_t targetSpeed;
	int16_t targetAngle;
	int16_t outCurrent;
	
	/*帧率控制（判断是否离线）*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
	
}RM3508_t;
/* =========================== RM3508 of end =========================== */

/* =========================== RM6623 of begin =========================== */
typedef struct
{
	/*反馈（输入）部分*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realTorque;
	int16_t realTempeture;
	
	int16_t realCurrent;
	int16_t feedbackCurrent;
	
	/*赋值（输出）部分*/
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
	/*帧率控制（判断是否离线）*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}RM6020_t;
/* =========================== RM6623 of end =========================== */

/* =========================== RM2006 of begin =========================== */
typedef struct
{
	/*反馈（输入）部分*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realTorque;
	
	/*赋值（输出）部分*/
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetSpeed;
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
	/*帧率控制（判断是否离线）*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}RM2006_t;    
/* =========================== RM2006 of end =========================== */


//typedef struct
//{
//		/*反馈（输入）部分*/
//	int16_t realAngle;
//	int16_t realSpeed;
//	int16_t realTorque;
//	
//	/*赋值（输出）部分*/
//	int32_t totalAngle;
//	int16_t turnCount;
//	
//	int32_t targetSpeed;
//	int32_t targetAngle;
//	int32_t lastAngle;
//	int16_t outCurrent;
//	
//	/*帧率控制（判断是否离线）*/
//	uint8_t UpdateFlag;
//	uint16_t UpdateFrame;
//	uint8_t OFFLINE_SET;
//}RMTEST;
/*对应的四个轮子*/
extern RM3508_t RM3508s[4];
/*对应的两个云台*/
extern RM6020_t RM6020s[2];
/*对应的拨弹电机*/
extern RM2006_t RM2006s[1];

/*CAN1串口解析*/
void CAN_Analysis(CanRxMsg CANReceiveMsg);

/*过零处理M6623*/
void M6623_ZeroDealing_platform(int8_t id);

/*过零处理M2006*/
void M2006_ZeroDealing_platform(int8_t id);

#endif	// __DRIVER_ANALYSIS_H
/*-----------------------------------file of end------------------------------*/


