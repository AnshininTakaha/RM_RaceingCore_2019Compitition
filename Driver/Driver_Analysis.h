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
  |--FileName    : Driver_Analysis.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
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

/*��Ӧ���ID�궨��*/
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
	/*���������룩����*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realCurrent;
	int16_t realTempeture;
	
	/*��ֵ�����������*/
	int16_t targetSpeed;
	int16_t targetAngle;
	int16_t outCurrent;
	
	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
	
}RM3508_t;
/* =========================== RM3508 of end =========================== */

/* =========================== RM6623 of begin =========================== */
typedef struct
{
	/*���������룩����*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realTorque;
	int16_t realTempeture;
	
	int16_t realCurrent;
	int16_t feedbackCurrent;
	
	/*��ֵ�����������*/
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}RM6020_t;
/* =========================== RM6623 of end =========================== */

/* =========================== RM2006 of begin =========================== */
typedef struct
{
	/*���������룩����*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realTorque;
	
	/*��ֵ�����������*/
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetSpeed;
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}RM2006_t;    
/* =========================== RM2006 of end =========================== */


//typedef struct
//{
//		/*���������룩����*/
//	int16_t realAngle;
//	int16_t realSpeed;
//	int16_t realTorque;
//	
//	/*��ֵ�����������*/
//	int32_t totalAngle;
//	int16_t turnCount;
//	
//	int32_t targetSpeed;
//	int32_t targetAngle;
//	int32_t lastAngle;
//	int16_t outCurrent;
//	
//	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
//	uint8_t UpdateFlag;
//	uint16_t UpdateFrame;
//	uint8_t OFFLINE_SET;
//}RMTEST;
/*��Ӧ���ĸ�����*/
extern RM3508_t RM3508s[4];
/*��Ӧ��������̨*/
extern RM6020_t RM6020s[2];
/*��Ӧ�Ĳ������*/
extern RM2006_t RM2006s[1];

/*CAN1���ڽ���*/
void CAN_Analysis(CanRxMsg CANReceiveMsg);

/*���㴦��M6623*/
void M6623_ZeroDealing_platform(int8_t id);

/*���㴦��M2006*/
void M2006_ZeroDealing_platform(int8_t id);

#endif	// __DRIVER_ANALYSIS_H
/*-----------------------------------file of end------------------------------*/


