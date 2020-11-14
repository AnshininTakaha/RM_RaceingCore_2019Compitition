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
  |--FileName    : BSP_TIM.c                                              
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
#include "BSP_TIM.h" 
 
TIM_SetComparex_f *const TIM_SetComparex[4] =
{
    TIM_SetCompare1,
    TIM_SetCompare2,
    TIM_SetCompare3,
    TIM_SetCompare4
};

/**
  * @Data    2019-03-22 21:08
  * @brief   TIMͨ�ÿ��ٳ�ʼ��
  * @param   void
  * @retval  void
  */
void TIM_PWM_Init(u16 prescaler, u16 period, u16 Pulse)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
		TIM_OCInitTypeDef  TIM_OCInitStructure;	
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource0, GPIO_AF_TIM5);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource1, GPIO_AF_TIM5);
	
		/*���*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource2, GPIO_AF_TIM5);

		TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
		TIM_TimeBaseStructure.TIM_Period = period;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		
		TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
		TIM_OCInitStructure.TIM_Pulse = Pulse;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
		
		/*���û������PWM���ԣ���ʼ��ƽΪ��(����ҲҪ���ã�����������ܳ���)*/
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
		/*���û����������ʱ�����ƽ(����ҲҪ���ã�����������ܳ���)*/
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

		/*˫ͨ�������ʼ��*/
		TIM_OC1Init(TIM5, &TIM_OCInitStructure);
		TIM_OC2Init(TIM5, &TIM_OCInitStructure);
		TIM_OC3Init(TIM5, &TIM_OCInitStructure);

		/*ʹ�ܶ�ʱ��*/
		TIM_Cmd(TIM5, ENABLE);

}


/**
  * @Data    2019-03-22 21:08
  * @brief   ���TIM��ʼ��
  * @param   void
  * @retval  void
  */
void TIM1_PWM_Init(u16 prescaler, u16 period, u16 Pulse)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	/* ����ʱ���ṹ�� */
	TIM_OCInitTypeDef  TIM_OCInitStructure;	/*��������ȽϽṹ��*/
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//ʹ�ܶ�ʱ��ʱ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8, GPIO_AF_TIM1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_TIM1);

	//���ö�ʱ��ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//�����Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseStructure.TIM_Period = period;
	//��������ʱ��������˲���Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//���ü���ģʽ�����ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	//�������ģʽ��PWM1ģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//ʹ�����
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//��ʹ�ܻ������
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	//���ó�ʼռ�ձ�
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	//����PWM���ԣ���ʼ��ƽΪ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//���ÿ���ʱ�����ƽ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	//���û������PWM���ԣ���ʼ��ƽΪ��(����ҲҪ���ã�����������ܳ���)
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//���û����������ʱ�����ƽ(����ҲҪ���ã�����������ܳ���)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	//��ʼ��Ϊ��Ӧͨ���������ͨ��1
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	//��ʼ��Ϊ��Ӧͨ���������ͨ��1
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);

	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM1, ENABLE);

	/* �߼���ʱ����Ҫʹ��PWM��� */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}


/**
	* @brief  ���ո��ӿ�������
  * @param	0 �� 1 ��
  * @retval None
  */
void LIDSwitch(uint8_t mode)
{
	if (mode == 0)//��
	{
		TIM_SetCompare1(TIM1,500);
		TIM_SetCompare3(TIM5,500);
		
	}
	else
	{
		TIM_SetCompare1(TIM1,2500);
		TIM_SetCompare3(TIM5,1900);
	}
}
//void TIM_PWM_Init(uint16_t prescaler, uint16_t period, uint16_t Pulse)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
//		TIM_OCInitTypeDef  TIM_OCInitStructure;	
//		
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
//		
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
//		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
//		
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
//		GPIO_PinAFConfig(GPIOA,GPIO_PinSource8, GPIO_AF_TIM1);

//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
//		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_TIM1);


//		TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
//		TIM_TimeBaseStructure.TIM_Period = period;
//		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//		
//		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
//		

//		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
//		TIM_OCInitStructure.TIM_Pulse = Pulse;
//		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
//		
//		/*���û������PWM���ԣ���ʼ��ƽΪ��(����ҲҪ���ã�����������ܳ���)*/
//		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
//		/*���û����������ʱ�����ƽ(����ҲҪ���ã�����������ܳ���)*/
//		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

//			/*˫ͨ�������ʼ��*/
//		TIM_OC1Init(TIM1, &TIM_OCInitStructure);
//		TIM_OC2Init(TIM1, &TIM_OCInitStructure);

//		/*ʹ�ܶ�ʱ��*/
//		TIM_Cmd(TIM1, ENABLE);
//		/* �߼���ʱ����Ҫʹ��PWM��� */
//		TIM_CtrlPWMOutputs(TIM1, ENABLE);
//}



/*-----------------------------------file of end------------------------------*/


