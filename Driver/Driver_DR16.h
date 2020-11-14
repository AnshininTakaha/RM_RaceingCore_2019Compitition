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
  |--FileName    : Driver_DR16.h                                                
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
#ifndef __DRIVER_DR16_H 
#define __DRIVER_DR16_H 

#pragma anon_unions

#include "BSP_Init.h"
#include "stm32f4xx.h"
#include "stdbool.h"
#include "arm_math.h"
/*遥控器结构体*/
typedef struct
{
		/*遥控器变量*/
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
		
		/*电脑变量*/
    struct
    {
        int16_t x;
        int16_t y;
        int16_t z;

        uint8_t keyLeft;
        uint8_t keyRight;

    } mouse;

		/*键盘变量*/
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
		
	/*帧率控制（判断是否离线）*/
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
		
} DR16_t;

/*RC遥控模型*/
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

/*电脑按键模型*/
typedef struct 
{
    float PC_x;
    float PC_y;
    float PC_radian;
    float PC_degrees;
    float PC_distance;
    
}PCRocket_t;

/*按键状态储存体*/
enum ActionType
{
	CLICK, 
	PRESS,
	LONG_PRESS
};

/*新遥控器操作右边*/
enum RightSwitchModeNew
{
		Friction_All_OFF = 1,
		Friction_AND_Laser_ON = 3,
		Cartridge_AND_Laser_ON=2,
};

/*新操作模式切换*/
enum LeftSwitchModeNew
{
		PC_Controling_ON = 1,
		RC_Controling_ON = 3,
		None_Controling_ON = 2,
};





/*DR16遥控器储存体*/
extern DR16_t DR16;

/*遥控器赋值*/
extern RCRocket_t RCRocket;

/*电脑PC赋值*/
extern PCRocket_t PCRocket;

#define KEYMOUSE_AMOUNT 18
#define KEYMOUSE_PRESSTIME 1
#define KEYMOUSE_LONGPRESSTIME 100

/*键鼠按下志位*/
extern uint32_t KeyMouse_Press;
/*键鼠单击18位标志位*/
extern uint32_t KeyMouse_Click;
/*键鼠长按18位标志位*/
extern uint32_t KeyMouse_LongPress;
/*键鼠按下时间*/
extern uint32_t PressTime[KEYMOUSE_AMOUNT];

/*DR16遥控解码函数*/
void DR16_Process(uint8_t *pData);

/*DR16通道值滤抖处理*/
int Data_Suppers(int16_t data);

/*摇杆模型赋值*/
void Rocket_transport(float POSLeft_x, float POSLeft_y,float POSRight_x,\
float POSRight_y,float Flatwheel,RCRocket_t *rocket);

/*按键判断*/
void KeyAction_Process(void);

/*获取键盘鼠标的动作*/
uint8_t GetKeyMouseAction(uint8_t KeyMouse, uint8_t Action);



#endif	// __DRIVER_DR16_H
/*-----------------------------------file of end------------------------------*/


