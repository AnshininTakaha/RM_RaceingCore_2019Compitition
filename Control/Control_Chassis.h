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
  |--FileName    : Control_Chassis.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
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

/*��ͨ�˲�����*/
#define Fif_Factor 0.1f  
#define Filter_LowFilter 0.4f

/*��������任��λ*/
#define CurrentUnit 1000
/*����ٶȿ���*/
#define Chassis_MaxSpeed_Y	8000.0f		
#define Chassis_MaxSpeed_X	8000.0f		
#define Chassis_MaxSpeed_W	8000.0f		
extern float AngleRead,IMUAngleRead,IMU_PI_AngleRead;;
extern float TempPush;
extern float angle;
extern float swing_time;
typedef struct
{
	/*ң��ģʽ����ң����ң��*/
	uint8_t RCmodeswitch;
	
	/*�ϲ���PC�ṹ������*/
//	/*PC�Ŀ���ģʽ*/
//	uint8_t PCmodeswitch;

	float Filter_LPFfactor;
	float xPF;
	float yPF;
	float zPF;
	
  /*�����������*/
	positionpid_t Fowllow_Attitude_pid;
	float FollowYawRaw;
	float FollowYawLPF;
	
	/*�����ʱ�־λ*/
	uint8_t Power_OverflowFlag;
  /*Ԥ�����ʱ�־λ*/
  uint8_t PrePower_OverflowFlag;
	
}Chassis_t;

extern Chassis_t Chassis;

/*����PID��ʼ��*/
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

/*����PID��ʼ��*/
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

/*���̸���PID��ʼ��*/
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

/*��ȡң�����Ե��̵����ݸ�ֵ*/
void Chassis_Judgement(uint8_t switchmode);

/*���̴�����*/
void Chassis_Process(float Input_Vx, float Input_Vy, float Input_VOmega, \
uint8_t switchmode);

/*���ֽ���*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);

/*��������*/
void Power_Limited(void);

///*��������*/
//void Chassis_PowerLimit(RM3508_t *RM3508, float CurrentLimit);

///*����������*/
//void Power_Limit(float Cur_limit);

#endif	// __CONTROL_CHASSIS_H
/*-----------------------------------file of end------------------------------*/


