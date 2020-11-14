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
  |--FileName    : Switch.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
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

/*ʹ��FreeRTOSϵͳ*/
#define SYSTEM_SUPPORT_OS 1
/*���Ӻ궨���Լ�*/
#define BoardSelfChecking 1
/*����궨���Լ�*/
#define AimingSelfChecking 1
/*����ANO���ݲ��β鿴(�������Ӱ�������Ӧ�Ĳ����ʣ�������Ϊ115200��)*/
#define ANOUse 1
/*������ֹ������תģʽ*/
//#define BAN_NoneHead 
///*��̨���ڽ��*/
//#define Cloud_IN_RANGE
/*����֡�ʼ���Զ�ʧ��*/
//#define BAN_RM3508sFlash
//#define BAN_RM6623sFlash
#define BAN_RM2006sFlash

/* =========================== AllSwitch of begin =========================== */
/*RM�ٷ��ð���A��*/
//#define RMOfficialBoardA 
/*Ұ�Ƕ��ð��ӵ�һ�汾*/
#define WildWolfOfficialBoard_F  
/*ʹ�þ������ж�*/
//#define OldAimingUsing
/*ʹ���������ж�*/
#define NewAimingUsing
/*ʹ��ʮ��λ�����������*/
//#define SixteenintAimingUsing
/*��̨ʹ�ö���ʽ�˲�����*/
//#define FilterUSEPolynomial
/*��̨ʹ�õ�ͨ�˲�����*/
//#define FilterUSELowerPower
/*���̲���ֵ��������ģʽ*/
//#define ChassisDebugMode 
///*��̨����ֵ��������ģʽ*/
//#define CloudDebugMode
/*�����������ֵ��������ģʽ*/
//#define ShootDebugMode
/*ʹ�������Ǳջ�*/
//#define LoopByGyroscope
/*ʹ�õ��̽��ٶȱջ�*/
//#define LoopByMotorSpeed
/* =========================== AllSwitch of end =========================== */

/* =========================== Steering of begin =========================== */
/*ʹ��UART���ƶ��*/
#define Using_Servoe_ByUART
/*ʹ�ö�ʱ�����ƵĶ��*/
#define Using_Serove_ByTIM
/* =========================== Steering of begin =========================== */

/* =========================== Board Select of begin =========================== */
/*���Ӷ����ʼ���Լ��ը(���ȶ���ΪRM�ٷ�����)*/
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
/*Aiming��׼�궨���ʼ���Լ��ը*/
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


