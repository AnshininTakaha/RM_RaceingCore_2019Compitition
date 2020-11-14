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
  |--FileName    : Control_Cloud.h                                                
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
#ifndef __CONTROL_CLOUD_H 
#define __CONTROL_CLOUD_H 

#include "Switch.h"
#include "stm32f4xx.h"
#include "Driver_PID.h"

#define Cloud_Yaw_Min				-430.0f
#define Cloud_Yaw_Max				1892.0f
#define Cloud_Yaw_Center			2033.0f	
#define Cloud_Yaw_delta			(Cloud_Yaw_Max - Cloud_Yaw_Min)

#define Cloud_Pitch_Min				2200.0f
#define Cloud_Pitch_Max				3110.0f
#define Cloud_Pitch_Center			2765.0f
#define Cloud_Pitch_delta		(Cloud_Pitch_Max - Cloud_Pitch_Min)

#define M6623_AngleToDEG(ang)	ang/22.75f
 extern float Chassis_speed_offset;
extern float TempPushCal;
/*��̨����ṹ��*/
typedef struct 
{
  /*ң��������,��ң���ұߵ�ң��*/
  uint8_t RCmodeswitch;
	
	/*�ϲ���PC�ṹ������*/
//  /*PC����ģʽ*/
//  uint8_t PCmodeswitch;

  /*��̨������������*/
	float Yaw_Raw;
	float Yaw_PF;
	float Pitch_Raw;
	float Pitch_PF;
	
  /*IMU������������*/
	float IMUYaw_Raw;
	float IMUYaw_PF;
	float IMUPitch_Raw;
	float IMUPitch_PF;
	
  /*��̨��ֵ�Ƕ�*/
	float IMUYawAngleMax;		//��̨IMU���Ƕ�(��)
	float IMUYawAngleMin;		//��̨IMU��С�Ƕ�(��)
	float IMUPitchAngleMax;		//��̨IMU���Ƕ�(��)
	float IMUPitchAngleMin;		//��̨IMU��С�Ƕ�(��)

}Cloud_t;

/*��̨����ṹ��*/
extern Cloud_t Cloud;

/***************************IMU����ʱ��Ļ�е�Ƕȿ���***************************/
/*IMU���ߵĻ�е����*/
#define PosInit_Cloud_YAWRing_NIMU \
{\
	18.2f,\
	0.0f,\
	125.5f,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	28888,\
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
	0,\
	&PositionPID_Calculation,\
}\

#define PosInit_Cloud_YAWRing_SIMU \
{\
	18.2f,\
	0.0f,\
	125.5f,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	28888,\
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
	0,\
	&PositionPID_Calculation,\
}\

/*IMU���߻�е����*/
#define PosInit_Cloud_PITCHRing_NIMU \
{\
	18.5f,\
	0.0f,\
	48.5f,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	28888,\
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
	0,\
	&PositionPID_Calculation,\
}\

#define PosInit_Cloud_PITCHRing_SIMU \
{\
	18.5f,\
	0.0f,\
	48.5f,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	28888,\
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
	0,\
	&PositionPID_Calculation,\
}\
/***************************IMU����ʱ��Ļ�е�Ƕȿ���***************************/

/*********************************YAW��IMU����*********************************/
/*IMU�ջ�����*/
#define PosInit_Cloud_YAWOuterRing \
{\
	-0.081f,\
	-0.0f,\
	0.0f,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	28888,\
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
	0,\
	&PositionPID_Calculation,\
}\

#define PosInit_Cloud_YAWInnerRing \
{\
	450.0f,\
	0.0f,\
	630.0f,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	28888,\
	8000,\
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

/*********************************YAW��IMU����*********************************/

/*******************************YAW���е�Ƕȿ���*******************************/
/*��е�Ƕȱջ�����*/
//#define PosInit_Cloud_YAWOuterRing \
//{\
//	-1.5f,\
//	-0.0f,\
//	-0.5f,\
//	{0.0,0.0,0.0,0.0},\
//	{0.0,0.0,0.0,0.0},\
//	{0.0,0.0,0.0,0.0},\
//	28888,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	&PositionPID_Calculation,\
//}\

//#define PosInit_Cloud_YAWInnerRing \
//{\
//	800.0f,\
//	0.0f,\
//	0.0f,\
//	{0.0,0.0,0.0,0.0},\
//	{0.0,0.0,0.0,0.0},\
//	{0.0,0.0,0.0,0.0},\
//	28888,\
//	8000,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	&PositionPID_Calculation,\
//}\

/*******************************YAW���е�Ƕȿ���*******************************/


/******************************PITCH���е�Ƕȿ���******************************/

//#define PosInit_Cloud_PitchOuterRing \
//{\
//	0,\
//	0,\
//	0,\
//	{0.148,0.186,0.229,0.287},\
//	{0.0,0.0,0.0,0.0},\
//	{0.092,0.062,0.0089,0.0135},\
//	28888,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	&FuzzyPID_PosCalculation,\
//}\

/**/
#define PosInit_Cloud_PitchOuterRing \
{\
	0.15f,\
	0,\
	0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	28888,\
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
	0,\
	&PositionPID_Calculation,\
}\


#define PosInit_Cloud_PitchInnerRing \
{\
  300.0f,\
	0.0f,\
	0.0f,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	28888,\
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
	0,\
	&PositionPID_Calculation,\
}\

/******************************PITCH���е�Ƕȿ���******************************/


//#define PosInit_Cloud_AimingYaw \
//{\
//	0,\
//	0,\
//	0,\
//	{0.487,0.633,0.656,0.684},\
//	{0.0,0.0,0.0,0.0},\
//	{1.768,1.889,1.985,2.02},\
//	1000,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	&FuzzyPID_PosCalculation,\
//}\


//#define PosInit_Cloud_AimingPitch \
//{\
//	0,\
//	0,\
//	0,\
//	{-0.387,-0.533,-0.606,-0.726},\
//	{0.0,0.0,0.0,0.0},\
//	{-1.768,-1.889,-1.985,-2.02},\
//	500,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	0,\
//	&FuzzyPID_PosCalculation,\
//}\

/**********************************Aiming**************************************/
/**********************************���������**************************************/
#define PosInit_Cloud_AimingYaw \
{\
	0.12,\
	0,\
	-0.0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\

#define PosInit_Cloud_AimingYawSeconrd \
{\
	15,\
	0,\
	0.0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\

/**********************************�������**************************************/

//0.14 12 20
#define PosInit_Cloud_AimingFollowYaw \
{\
	0.2,\
	0,\
	0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\

#define PosInit_Cloud_AimingFollowYawSeconrd \
{\
	17,\
	0,\
	0.0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\

#define PosInit_Cloud_AimingFollowYawJZ \
{\
	0.13,\
	0,\
	0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\

#define PosInit_Cloud_AimingFollowYawSeconrdJZ \
{\
	16,\
	0,\
	0.0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\


/**********************************���������**************************************/
#define PosInit_Cloud_AimingPitch \
{\
	0.3,\
	0,\
	-0.0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\


#define PosInit_Cloud_AimingPitchSeconrd \
{\
	8,\
	0,\
	0.0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\


/**********************************�������**************************************/
#define PosInit_Cloud_AimingFollowPitch \
{\
	0.35,\
	0,\
	-0.0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\


#define PosInit_Cloud_AimingFollowPitchSeconrd \
{\
	8,\
	0,\
	0.0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\


#define PosInit_Cloud_AimingFollowPitchJZ \
{\
	0.2,\
	0,\
	-0.0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\


#define PosInit_Cloud_AimingFollowPitchSeconrdJZ \
{\
	6,\
	0,\
	0.0,\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	{0.0,0.0,0.0,0.0},\
	10000,\
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
	0,\
	&PositionPID_Calculation,\
}\



/**********************************Aiming**************************************/

extern positionpid_t Yaw_OuterRing;
extern positionpid_t Yaw_InnerRing;
extern positionpid_t Pitch_OuterRing;
extern positionpid_t Pitch_InnerRing;
extern positionpid_t Yaw_AimimgRing;
extern positionpid_t Pitch_AimingRing;


/*��̨����ֵ*/
void Cloud_Judgement(uint8_t switchmode);

/*��̨����*/
void Cloud_Process(float Delta_YAW, float Detla_Pitch,uint8_t switchmode);

/*IMU������̨����*/
void Cloud_NormalProcess(float Delta_YAW, float Detla_Pitch,uint8_t switchmode);


/*��ȡ��̨��YAW��PITCH�൱�������ǵĽǶ�*/
float GetYAW_withCenter(void);
float GetYAW_withLeft(void);
float GetPitch_withCenter(void);
float GetPitch_withDown(void);

/*Pitch���е�Ƕ��趨Ŀ����*/
void M6623_setTargetAngle(int Moto_Id,int32_t Target_Angle);


#endif	// __CONTROL_CLOUD_H
/*-----------------------------------file of end------------------------------*/


