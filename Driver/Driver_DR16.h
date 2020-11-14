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
  |--FileName    : Driver_DR16.h                                                
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
#ifndef __DRIVER_DR16_H 
#define __DRIVER_DR16_H 

#pragma anon_unions

#include "BSP_Init.h"
#include "stm32f4xx.h"
#include "stdbool.h"
#include "arm_math.h"
/*ң�����ṹ��*/
typedef struct
{
		/*ң��������*/
    struct 
		{
        int16_t ch0;//RX
        int16_t ch1;//RY
        int16_t ch2;//LX
        int16_t ch3;//LY
        int16_t ch5_wheel;
        uint8_t s_left;
        uint8_t s_right;
    } rc;
		
		/*���Ա���*/
    struct
    {
        int16_t x;
        int16_t y;
        int16_t z;

        uint8_t keyLeft;
        uint8_t keyRight;

    } mouse;

		/*���̱���*/
    union
    {
        uint16_t key_code;
        struct 
				{
					
					 
			
            bool press_W:1;
            bool press_S:1;
            bool press_A:1;
            bool press_D:1;
						bool press_Shift:1;
            bool press_Ctrl:1;
            bool press_Q:1;
            bool press_E:1;
   
			
            bool press_R:1;
            bool press_F:1;
            bool press_G:1;
            bool press_Z:1;
            bool press_X:1;
            bool press_C:1;
            bool press_V:1;
            bool press_B:1;
           
        };
    } keyBoard;
		
	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
		
} DR16_t;

/*RCң��ģ��*/
typedef struct 
{   
    float Left_x;
    float Left_y;
    float Left_radian;
    float Left_degrees;
    float Left_distance;

    float Right_x;
    float Right_y;
    float Right_radian;
    float Right_degrees;
    float Right_distance;

    float FlatWheel;
}RCRocket_t;

/*���԰���ģ��*/
typedef struct 
{
    float PC_x;
    float PC_y;
    float PC_radian;
    float PC_degrees;
    float PC_distance;
    
}PCRocket_t;

/*����״̬������*/
enum ActionType
{
	CLICK, 
	PRESS,
	LONG_PRESS
};

/*��ң���������ұ�*/
enum RightSwitchModeNew
{
		Friction_All_OFF = 1,
		Friction_AND_Laser_ON = 3,
		Cartridge_AND_Laser_ON=2,
};

/*�²���ģʽ�л�*/
enum LeftSwitchModeNew
{
		PC_Controling_ON = 1,
		RC_Controling_ON = 3,
		None_Controling_ON = 2,
};





/*DR16ң����������*/
extern DR16_t DR16;

/*ң������ֵ*/
extern RCRocket_t RCRocket;

/*����PC��ֵ*/
extern PCRocket_t PCRocket;

#define KEYMOUSE_AMOUNT 18
#define KEYMOUSE_PRESSTIME 1
#define KEYMOUSE_LONGPRESSTIME 100

/*������־λ*/
extern uint32_t KeyMouse_Press;
/*���󵥻�18λ��־λ*/
extern uint32_t KeyMouse_Click;
/*���󳤰�18λ��־λ*/
extern uint32_t KeyMouse_LongPress;
/*������ʱ��*/
extern uint32_t PressTime[KEYMOUSE_AMOUNT];

/*DR16ң�ؽ��뺯��*/
void DR16_Process(uint8_t *pData);

/*DR16ͨ��ֵ�˶�����*/
int Data_Suppers(int16_t data);

/*ҡ��ģ�͸�ֵ*/
void Rocket_transport(float POSLeft_x, float POSLeft_y,float POSRight_x,\
float POSRight_y,float Flatwheel,RCRocket_t *rocket);

/*�����ж�*/
void KeyAction_Process(void);

/*��ȡ�������Ķ���*/
uint8_t GetKeyMouseAction(uint8_t KeyMouse, uint8_t Action);



#endif	// __DRIVER_DR16_H
/*-----------------------------------file of end------------------------------*/


