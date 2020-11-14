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
  |--FileName    : Control_PC.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-04-03               
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
#ifndef __CONTROL_PC_H 
#define __CONTROL_PC_H 

#include "Driver_DR16.h"
#include "stm32f4xx.h"

#define Speed_Low 1500
#define Speed_Normal 6000
#define Speed_Fast 8000
#define Speed_Packages 750


extern float SEDV_BIGER;
extern float SEDV_Swing;
extern float SECV_BIGModule;
extern float SEDV_NoneHeadMode;

typedef struct 
{
  /*模式和初始化标志位*/
  uint8_t PCMode;
  uint8_t InitState;

  /*Shift状态标志位和Ctrl状态标志位*/
  uint16_t ShiftState;
  uint16_t CtrlState;
	uint16_t NoneHeadState;
	uint16_t DamnBigState;
	
  uint16_t AimingState;
	uint16_t ChangeFrictionSpeedINIT;
	uint16_t ChangeFrictionSpeed;
	uint16_t TurnState;
	uint16_t SwingState;
	uint16_t Toggle_SEV;
	uint16_t BIGState;
	uint16_t BIGMODULEState;

  uint16_t LeftPressState;
	uint16_t LeftLongPressState;
	uint16_t RightPressState;
	uint16_t RightLongPressState;
}PC_t;

extern PC_t PC;

/*PC电脑控制状态*/
typedef enum
{
  PC_NoneHead = 1,
  PC_CloudPlatfrom = 2,
  PC_Sevrel = 3,
	PC_AUTO = 4,
  
}PCControl_Mode;

extern PC_t PC;

enum KEYMOUSE
{	
	KEYBOARD_PRESSED_W,/*0*/
	KEYBOARD_PRESSED_S,/*1*/
	KEYBOARD_PRESSED_A,/*2*/
	KEYBOARD_PRESSED_D,/*3*/
	KEYBOARD_PRESSED_SHIFT,/*4*/
	KEYBOARD_PRESSED_CTRL,/*5*/
	KEYBOARD_PRESSED_Q,/*6*/
	KEYBOARD_PRESSED_E,/*7*/
	KEYBOARD_PRESSED_R,/*8*/
	KEYBOARD_PRESSED_F,/*9*/
	KEYBOARD_PRESSED_G,/*10*/
	KEYBOARD_PRESSED_Z,/*11*/
	KEYBOARD_PRESSED_X,/*12*/
	KEYBOARD_PRESSED_C,/*13*/
	KEYBOARD_PRESSED_V,/*14*/
	KEYBOARD_PRESSED_B,/*15*/
	MOUSE_PRESS_L,/*16*/
	MOUSE_PRESS_R /*17*/
};

/*相应模式按键*/

/*Ctrl + B*/
#define PC_CloudPlatfromChange (KeyMouse_Press & (1 << KEYBOARD_PRESSED_B))

/*Ctrl + V*/
#define PC_NoneHeadChange (KeyMouse_Press & (1 << KEYBOARD_PRESSED_V))

/*Ctrl + C*/
#define PC_SwingChange (KeyMouse_Press & (1 << KEYBOARD_PRESSED_C))

/*Ctrl + F*/
#define PC_SevrelChange (KeyMouse_Press & (1 << KEYBOARD_PRESSED_F))

/*电脑初始化*/
void PC_Init(void);

/*PC总控制处理*/
void PCControl_Process(void);

/*特殊功能键位判定*/
void SpeicalKey_Process(void);

/*模式改变判定*/
void Modechange_Judgement(void);

/*方向和速度判定处理*/
void Derection_Process(PCRocket_t *rocket);


#endif	// __CONTROL_PC_H
/*-----------------------------------file of end------------------------------*/


