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
  |--FileName    : Control_Shoot.h                                                
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
#ifndef __CONTROL_SHOOT_H 
#define __CONTROL_SHOOT_H 



#include "BSP_Init.h"
#include "stm32f4xx.h"

#define frictionSpeedMax 2000
#define frictionSpeedMin 1000
#define Fire_Round		49152
#define FrictionHighSpeed 1280
#define FrictionLowSpeed 1150
extern int SEV_Delta;
extern int ChangeSEVPoint;
typedef struct
{
		/*��������*/
	  uint16_t FrictionUpdata;
	  /*Ħ��������*/
		uint8_t FrictionReady;
		
	  uint16_t FrictionSpeed;
		/*���Ƶ��(�����ȴ)*/
		uint8_t shootFreq;
		/*���׼����־λ��������ȴʱ����㣩*/
		uint8_t shootReady;
		/*���󲦵���־λ���ⲿ�����ӿڣ�*/
		uint8_t shootFlag;
		/*�ӵ�װ�����쳣��־λ*/
		uint8_t loadFinish;
		
		/*��������*/
		/*��ǰʣ���������Է�����ӵ�������*/
		uint8_t AllowShootCount;
	  /*������ٶ�*/
		uint16_t ShootSpeedMAX;
		/*Ԥ���Ѿ����ȥ���ӵ�����*/
		uint16_t bulletcount;
//		/*��ǰ�ӵ������ٶ�*/
//		float NowShootSpeed;
		/*��һ���ӵ������ٶ�*/
		float LastShootSpeed;
		/*�����ӵ����������Ʊ�־λ*/
		uint8_t HeatShootFlag;
		/*�����ȥ�ı�־λ*/
		uint8_t ShootOverFlag;
		/*ռ��ﱤ��־λ*/
		uint8_t BunkerFlag;
		
}NewFriction_t;

extern NewFriction_t FrictionNew;

#define Cartridge_OuterRing \
{\
	0.5f,\
	0.0f,\
	0.0f,\
	{0,0,0,0},\
	{0,0,0,0},\
	{0,0,0,0},\
	16000,\
	2000,\
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

#define Cartridge_InnerRing \
{\
	0.8f,\
	0.0f,\
	3.5f,\
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


/*������ݸ�ֵ����*/
void Shoot_Judgement(uint8_t switchmode);

/*�������*/
void Shoot_Process(uint16_t firctionSpeed,uint8_t switchmode);

/*����Ħ�����ٶ�*/
void Firction_SpeedSetting(uint16_t speed);

#endif	// __CONTROL_SHOOT_H
/*-----------------------------------file of end------------------------------*/


