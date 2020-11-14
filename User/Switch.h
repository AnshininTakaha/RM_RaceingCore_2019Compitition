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
  |--FileName    : Switch.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-03-22               
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
#ifndef __SWITCH_H 
#define __SWITCH_H 

/*使用FreeRTOS系统*/
#define SYSTEM_SUPPORT_OS 1
/*板子宏定义自检*/
#define BoardSelfChecking 1
/*自瞄宏定义自检*/
#define AimingSelfChecking 1
/*开启ANO数据波形查看(开启后会影响自瞄对应的波特率（启动后为115200）)*/
#define ANOUse 1
/*定义后禁止启动自转模式*/
//#define BAN_NoneHead 
///*云台处于界点*/
//#define Cloud_IN_RANGE
/*屏蔽帧率检测自动失能*/
//#define BAN_RM3508sFlash
//#define BAN_RM6623sFlash
#define BAN_RM2006sFlash

/* =========================== AllSwitch of begin =========================== */
/*RM官方用板子A型*/
//#define RMOfficialBoardA 
/*野狼队用板子第一版本*/
#define WildWolfOfficialBoard_F  
/*使用旧自瞄判断*/
//#define OldAimingUsing
/*使用新自瞄判断*/
#define NewAimingUsing
/*使用十六位进制自瞄测试*/
//#define SixteenintAimingUsing
/*云台使用多项式滤波处理*/
//#define FilterUSEPolynomial
/*云台使用低通滤波处理*/
//#define FilterUSELowerPower
/*底盘不赋值电流调试模式*/
//#define ChassisDebugMode 
///*云台不赋值电流调试模式*/
//#define CloudDebugMode
/*拨弹电机不赋值电流调试模式*/
//#define ShootDebugMode
/*使用陀螺仪闭环*/
//#define LoopByGyroscope
/*使用底盘角速度闭环*/
//#define LoopByMotorSpeed
/* =========================== AllSwitch of end =========================== */

/* =========================== Steering of begin =========================== */
/*使用UART控制舵机*/
#define Using_Servoe_ByUART
/*使用定时器控制的舵机*/
#define Using_Serove_ByTIM
/* =========================== Steering of begin =========================== */

/* =========================== Board Select of begin =========================== */
/*板子定义初始化自检防炸(优先定义为RM官方板子)*/
#if BoardSelfChecking
  #ifdef RMOfficialBoardA
      #undef WildWolfOfficialBoard_F
  #endif
  #ifdef WildWolfOfficialBoard_F
      #undef RMOfficialBoardA
  #endif
#else
  #warning SelfChecking System hasnot open,Cheaking in Switch.h
#endif
/* =========================== Board Select of end =========================== */

/* =========================== Aiming Select of begin =========================== */
/*Aiming瞄准宏定义初始化自检防炸*/
#if AimingSelfChecking
  #ifdef OldAimingUsing
  #undef NewAimingUsing
  #endif

  #ifdef NewAimingUsing
  #undef OldAimingUsing
  #endif
#else
  #warning AimingCheaking isnot open,Cheaking in Switch.h
#endif

/* =========================== Aiming Select of end =========================== */
/*Using Select*/



#endif	// __SWITCH_H
/*-----------------------------------file of end------------------------------*/


