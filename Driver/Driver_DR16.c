/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,���� & �,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Driver_DR16.c                                              
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
#include "Driver_DR16.h" 

/*ң��������ṹ��*/
DR16_t DR16;

/*ң����ģ����ֵ����ṹ��*/
RCRocket_t RCRocket;

/*����PC��ֵ*/
PCRocket_t PCRocket;

/*������־λ*/
uint32_t KeyMouse_Press;

/*���󵥻�18λ��־λ*/
uint32_t KeyMouse_Click;

/*���󳤰�18λ��־λ*/
uint32_t KeyMouse_LongPress;

/*������ʱ��*/
uint32_t PressTime[KEYMOUSE_AMOUNT] = {0};

/**
  * @Data    2019-03-23 20:07
  * @brief   DR16ң�������뺯��
  * @param   uint8_t *pData
  * @retval  void
  */
void DR16_Process(uint8_t *pData)
{
    /*��ֵ����*/
	if(pData == NULL)
	{
		return;
	}

  /*ң����*/
	DR16.rc.ch0 = (pData[0] | (pData[1] << 8)) & 0x07FF;
	DR16.rc.ch1 = ((pData[1] >> 3) | (pData[2] << 5)) & 0x07FF;
	DR16.rc.ch2 = ((pData[2] >> 6) | (pData[3] << 2) | (pData[4] << 10)) & 0x07FF;
	DR16.rc.ch3 = ((pData[4] >> 1) | (pData[5] << 7)) & 0x07FF;
  DR16.rc.ch5_wheel = (pData[16] | (pData[17] << 8)) & 0x07FF;
	DR16.rc.s_left = ((pData[5] >> 4) & 0x000C) >> 2;
	DR16.rc.s_right = ((pData[5] >> 4) & 0x0003);
	
	/*���*/
	DR16.mouse.x = (pData[6]) | (pData[7] << 8);
	DR16.mouse.y = (pData[8]) | (pData[9] << 8);
	DR16.mouse.z = (pData[10]) | (pData[11] << 8);
	DR16.mouse.keyLeft = pData[12];
	DR16.mouse.keyRight = pData[13];
	DR16.keyBoard.key_code = (pData[14] | pData[15] <<8);

  /*ͨ�����ֵ���*/
  DR16.rc.ch0 -= 1024;
	DR16.rc.ch1 -= 1024;
	DR16.rc.ch2 -= 1024;
	DR16.rc.ch3 -= 1024;
	DR16.rc.ch5_wheel -=1024;
	
  /*ͨ��ֵ�˶�*/
  DR16.rc.ch0 = Data_Suppers(DR16.rc.ch0);
	DR16.rc.ch1 = Data_Suppers(DR16.rc.ch1);
	DR16.rc.ch2 = Data_Suppers(DR16.rc.ch2);
	DR16.rc.ch3 = Data_Suppers(DR16.rc.ch3);
  DR16.rc.ch5_wheel = Data_Suppers(DR16.rc.ch5_wheel);
	
	/*ң��������*/
  Rocket_transport(DR16.rc.ch3,-DR16.rc.ch2,DR16.rc.ch0,DR16.rc.ch1,\
  DR16.rc.ch5_wheel,&RCRocket);
	
	/*����(�������ж�)�ж�*/
	KeyAction_Process();
	
	/*DR16֡�ʵ���*/
	DR16.UpdateFrame++;
	
}

/**
  * @Data    2019-02-21 11:09
  * @brief   DR16ͨ��ֵ�˶�����
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
  * @brief   ҡ��ģ�͸�ֵ
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
    /*ҡ�˸�ֵ*/
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
  * @brief   �����ж�
  * @param   void
  * @retval  void
  */
 /*�൱�ڴ���������λ���жϵ�18λ��־λ��һ��λ�����Ӧ������*/
void KeyAction_Process(void)
{
  /*����λ�ñ�־��һ��ʼ�ڵ�һ��λ��*/
  uint8_t Index = 0;
  /*�����̵�ֵ���������ĵ����ֵ�ų�һ��32λ������*/
	uint32_t KeyMouse = (uint32_t)DR16.keyBoard.key_code | DR16.mouse.keyLeft<<16\
  | DR16.mouse.keyRight<<17;

  for(;Index < KEYMOUSE_AMOUNT;Index++)
  {
    /*�����ڼ䣬��Ӧ�ı�־λΪ1*/
    if(KeyMouse & (1 << Index))
    {
      PressTime[Index]++;
      /*����*/
      if(PressTime[Index] > KEYMOUSE_PRESSTIME)
      {
        /*���ƶ�����Ӧ�İ���λ*/
        KeyMouse_Press |= 1 << Index;
      }

      /*����*/
      if(PressTime[Index] > KEYMOUSE_LONGPRESSTIME)
      {
        KeyMouse_LongPress |= 1 << Index;
      }
    }
    /*�ɿ��ڼ䣬��Ӧ�ı�־λ��Ϊ1*/
    else
    {
      if(PressTime[Index] > KEYMOUSE_PRESSTIME && \
      PressTime[Index] < KEYMOUSE_LONGPRESSTIME)
      {
        KeyMouse_Click |= 1 << Index;
      }
      else
      {
        /*�Ѷ�Ӧ�ı�־λ��0*/
        KeyMouse_Click &= ~(1 << Index);
      }

      KeyMouse_Press &= ~(1<<Index);
			KeyMouse_LongPress &= ~(1<<Index);
			PressTime[Index] = 0;
      
    }
  }
}

/**
	* @brief  ��ȡ�����̶���
  * @param	��ֵ  ����
  * @retval ���ؼ�����״̬  0 û�иö��� 1 �иö���
  */
uint8_t GetKeyMouseAction(uint8_t KeyMouse, uint8_t Action)
{
	switch(Action)
	{
		case CLICK://����
			return (KeyMouse_Click>>KeyMouse) & 1;
			break;
		
		case PRESS://����
			return (KeyMouse_Press>>KeyMouse) & 1;
			break;
		
		case LONG_PRESS://����
			return (KeyMouse_LongPress>>KeyMouse) & 1;
			break;
		
		default:
			return 0;
			break;
	}

}


/*-----------------------------------file of end------------------------------*/


