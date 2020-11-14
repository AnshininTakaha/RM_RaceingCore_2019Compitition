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
  |--FileName    : BSP_LASER.c                                              
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
#include "BSP_LASER.h" 

/**
  * @Data    2019-03-22 20:55
  * @brief   LASER�����ʼ��
  * @param   void
  * @retval  void
  */
void Laser_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA |RCC_AHB1Periph_GPIOG | \
    RCC_AHB1Periph_GPIOH ,ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ù���
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//����
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz

    #ifdef RMOfficialBoardA
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
		GPIO_Init(GPIOG,&GPIO_InitStructure);//��ʼ��
    #endif

    #ifdef WildWolfOfficialBoard_F
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��
    #endif
//    GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_SET);
		
}



/*-----------------------------------file of end------------------------------*/


