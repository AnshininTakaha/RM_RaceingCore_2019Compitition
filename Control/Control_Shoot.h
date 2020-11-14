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
  |--FileName    : Control_Shoot.h                                                
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
		/*热量上限*/
	  uint16_t FrictionUpdata;
	  /*摩擦轮启动*/
		uint8_t FrictionReady;
		
	  uint16_t FrictionSpeed;
		/*射击频率(射击冷却)*/
		uint8_t shootFreq;
		/*射击准备标志位（用于冷却时间计算）*/
		uint8_t shootReady;
		/*请求拨弹标志位（外部触发接口）*/
		uint8_t shootFlag;
		/*子弹装载无异常标志位*/
		uint8_t loadFinish;
		
		/*热量部分*/
		/*当前剩余热量可以发射的子弹的数量*/
		uint8_t AllowShootCount;
	  /*最大发射速度*/
		uint16_t ShootSpeedMAX;
		/*预计已经射出去的子弹数量*/
		uint16_t bulletcount;
//		/*当前子弹发射速度*/
//		float NowShootSpeed;
		/*上一发子弹发射速度*/
		float LastShootSpeed;
		/*发射子弹的热量限制标志位*/
		uint8_t HeatShootFlag;
		/*发射出去的标志位*/
		uint8_t ShootOverFlag;
		/*占领碉堡标志位*/
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


/*射击数据赋值处理*/
void Shoot_Judgement(uint8_t switchmode);

/*射击处理*/
void Shoot_Process(uint16_t firctionSpeed,uint8_t switchmode);

/*设置摩擦轮速度*/
void Firction_SpeedSetting(uint16_t speed);

#endif	// __CONTROL_SHOOT_H
/*-----------------------------------file of end------------------------------*/


