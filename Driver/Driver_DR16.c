/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无 & 璨,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Driver_DR16.c                                              
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
#include "Driver_DR16.h" 

/*遥控器储存结构体*/
DR16_t DR16;

/*遥控器模型数值储存结构体*/
RCRocket_t RCRocket;

/*电脑PC赋值*/
PCRocket_t PCRocket;

/*键鼠按下志位*/
uint32_t KeyMouse_Press;

/*键鼠单击18位标志位*/
uint32_t KeyMouse_Click;

/*键鼠长按18位标志位*/
uint32_t KeyMouse_LongPress;

/*键鼠按下时间*/
uint32_t PressTime[KEYMOUSE_AMOUNT] = {0};

/**
  * @Data    2019-03-23 20:07
  * @brief   DR16遥控器解码函数
  * @param   uint8_t *pData
  * @retval  void
  */
void DR16_Process(uint8_t *pData)
{
    /*空值返回*/
	if(pData == NULL)
	{
		return;
	}

  /*遥控器*/
	DR16.rc.ch0 = (pData[0] | (pData[1] << 8)) & 0x07FF;
	DR16.rc.ch1 = ((pData[1] >> 3) | (pData[2] << 5)) & 0x07FF;
	DR16.rc.ch2 = ((pData[2] >> 6) | (pData[3] << 2) | (pData[4] << 10)) & 0x07FF;
	DR16.rc.ch3 = ((pData[4] >> 1) | (pData[5] << 7)) & 0x07FF;
  DR16.rc.ch5_wheel = (pData[16] | (pData[17] << 8)) & 0x07FF;
	DR16.rc.s_left = ((pData[5] >> 4) & 0x000C) >> 2;
	DR16.rc.s_right = ((pData[5] >> 4) & 0x0003);
	
	/*鼠标*/
	DR16.mouse.x = (pData[6]) | (pData[7] << 8);
	DR16.mouse.y = (pData[8]) | (pData[9] << 8);
	DR16.mouse.z = (pData[10]) | (pData[11] << 8);
	DR16.mouse.keyLeft = pData[12];
	DR16.mouse.keyRight = pData[13];
	DR16.keyBoard.key_code = (pData[14] | pData[15] <<8);

  /*通道数字调零*/
  DR16.rc.ch0 -= 1024;
	DR16.rc.ch1 -= 1024;
	DR16.rc.ch2 -= 1024;
	DR16.rc.ch3 -= 1024;
	DR16.rc.ch5_wheel -=1024;
	
  /*通道值滤抖*/
  DR16.rc.ch0 = Data_Suppers(DR16.rc.ch0);
	DR16.rc.ch1 = Data_Suppers(DR16.rc.ch1);
	DR16.rc.ch2 = Data_Suppers(DR16.rc.ch2);
	DR16.rc.ch3 = Data_Suppers(DR16.rc.ch3);
  DR16.rc.ch5_wheel = Data_Suppers(DR16.rc.ch5_wheel);
	
	/*遥控器传输*/
  Rocket_transport(DR16.rc.ch3,-DR16.rc.ch2,DR16.rc.ch0,DR16.rc.ch1,\
  DR16.rc.ch5_wheel,&RCRocket);
	
	/*按键(鼠标键盘判定)判定*/
	KeyAction_Process();
	
	/*DR16帧率叠加*/
	DR16.UpdateFrame++;
	
}

/**
  * @Data    2019-02-21 11:09
  * @brief   DR16通道值滤抖处理
  * @param   int16_t data
  * @retval  int
  */
int Data_Suppers(int16_t data)
{
    if(ABS(data) < 20)
	{
		data = 0;
	}
	return data;
}


/**
  * @Data    2019-02-21 11:13
  * @brief   摇杆模型赋值
  * @param   float POSLeft_x, 
  *          float POSLeft_y,
  *          float POSRight_x,
  *          float POSRight_y,
  *          Rocket_t *rocket
  * @retval  void
  */
void Rocket_transport(float POSLeft_x, float POSLeft_y,float POSRight_x,\
float POSRight_y,float Flatwheel,RCRocket_t *rocket)
{
    /*摇杆赋值*/
    rocket->Left_x = POSLeft_x;
    rocket->Left_y = POSLeft_y;
    rocket->Right_x = POSRight_x;
    rocket->Right_y = POSRight_y;

    rocket->Left_radian = atan2(rocket->Left_y,rocket->Left_x);
    rocket->Right_radian = atan2(rocket->Right_y,rocket->Right_x);

    rocket->Left_degrees = rocket->Left_radian * 180.0f / PI;
    rocket->Right_degrees = rocket->Right_radian * 180.0f / PI;

    rocket->Left_distance = __sqrtf(pow(rocket->Left_x,2) + pow(rocket->Left_y,2));
    rocket->Right_distance = __sqrtf(pow(rocket->Right_x,2) + pow(rocket->Right_y,2));
    if(rocket -> Left_degrees > 180)
    {
        rocket -> Left_distance = -rocket -> Left_distance;
    }
    if(rocket ->Right_degrees > 180)
    {
        rocket -> Right_distance = -rocket -> Right_distance;
    }
		
		rocket->FlatWheel =  Flatwheel;
}


/**
  * @Data    2019-03-19 22:00
  * @brief   按键判断
  * @param   void
  * @retval  void
  */
 /*相当于创建三个用位来判断的18位标志位和一个位置相对应的数组*/
void KeyAction_Process(void)
{
  /*数据位置标志，一开始在第一个位置*/
  uint8_t Index = 0;
  /*将键盘的值和两个鼠标的点击的值排成一个32位的序列*/
	uint32_t KeyMouse = (uint32_t)DR16.keyBoard.key_code | DR16.mouse.keyLeft<<16\
  | DR16.mouse.keyRight<<17;

  for(;Index < KEYMOUSE_AMOUNT;Index++)
  {
    /*按下期间，对应的标志位为1*/
    if(KeyMouse & (1 << Index))
    {
      PressTime[Index]++;
      /*按下*/
      if(PressTime[Index] > KEYMOUSE_PRESSTIME)
      {
        /*左移动到对应的按键位*/
        KeyMouse_Press |= 1 << Index;
      }

      /*长按*/
      if(PressTime[Index] > KEYMOUSE_LONGPRESSTIME)
      {
        KeyMouse_LongPress |= 1 << Index;
      }
    }
    /*松开期间，对应的标志位不为1*/
    else
    {
      if(PressTime[Index] > KEYMOUSE_PRESSTIME && \
      PressTime[Index] < KEYMOUSE_LONGPRESSTIME)
      {
        KeyMouse_Click |= 1 << Index;
      }
      else
      {
        /*把对应的标志位置0*/
        KeyMouse_Click &= ~(1 << Index);
      }

      KeyMouse_Press &= ~(1<<Index);
			KeyMouse_LongPress &= ~(1<<Index);
			PressTime[Index] = 0;
      
    }
  }
}

/**
	* @brief  获取鼠标键盘动作
  * @param	键值  动作
  * @retval 返回键鼠动作状态  0 没有该动作 1 有该动作
  */
uint8_t GetKeyMouseAction(uint8_t KeyMouse, uint8_t Action)
{
	switch(Action)
	{
		case CLICK://单击
			return (KeyMouse_Click>>KeyMouse) & 1;
			break;
		
		case PRESS://按下
			return (KeyMouse_Press>>KeyMouse) & 1;
			break;
		
		case LONG_PRESS://长按
			return (KeyMouse_LongPress>>KeyMouse) & 1;
			break;
		
		default:
			return 0;
			break;
	}

}


/*-----------------------------------file of end------------------------------*/


