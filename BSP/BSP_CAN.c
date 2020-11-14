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
  |--FileName    : BSP_CAN.c                                              
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
#include "BSP_CAN.h" 


/**
  * @Data    2019-03-22 20:30
  * @brief   CAN1��ʼ��
  * @param   void
  * @retval  void
  */
void CAN1_QuickInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(CAN1_RX_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    /*����CAN1��TX����*/
    GPIO_InitStructure.GPIO_Pin = CAN1_TX_Pin;
    GPIO_Init(CAN1_TX_GPIO_PORT, &GPIO_InitStructure);
    /* ���� IO �� CAN1_Tx*/
    GPIO_PinAFConfig(CAN1_TX_GPIO_PORT, CAN1_TX_PINSOURCE, GPIO_AF_CAN1);


    /*����CAN1��RX����*/
    GPIO_InitStructure.GPIO_Pin = CAN1_RX_Pin;
    GPIO_Init(CAN1_RX_GPIO_PORT, &GPIO_InitStructure);
    /*���ӵ�CAN1_Rx*/
    GPIO_PinAFConfig(CAN1_RX_GPIO_PORT, CAN1_RX_PINSOURCE, GPIO_AF_CAN1);

    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = ENABLE;
    CAN_InitStructure.CAN_AWUM = ENABLE;		   
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	  

    /*��Ԫʱ�䳤��=45/(1+3+5)/5=1 Mbps*/
    CAN_InitStructure.CAN_SJW = CAN1_SJW;
    CAN_InitStructure.CAN_BS1 = CAN1_BS1;
    CAN_InitStructure.CAN_BS2 = CAN1_BS2;
    CAN_InitStructure.CAN_Prescaler = CAN1_Prescaler;
    CAN_Init(CAN1, &CAN_InitStructure);

    /*��Ƶ������*/
    CAN_FilterInitStructure.CAN_FilterNumber = 0;									
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;					
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;				
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0 ;			
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			

    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; 				
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;			
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			

    CAN_FilterInit(&CAN_FilterInitStructure);

    /*�ж�����*/
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&NVIC_InitStructure);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
		
}


/**
  * @Data    2019-03-22 20:30
  * @brief   CAN2��ʼ��
  * @param   void
  * @retval  void
  */
void CAN2_QuickInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* ʹ�� GPIO ʱ�� */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//ʹ��CAN2ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	
	/* GPIO��ʼ�� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* ����Tx����  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* ����Rx���� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* ���� IO �� CAN2_Tx*/
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);

	/*  ���� IO �� CAN2_Rx*/
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
	
	/************************CAN ģʽ����*********************************************/
	CAN_InitStructure.CAN_TTCM = DISABLE;			   //MCR-TTCM  ʱ�䴥��ͨ��ģʽ
	CAN_InitStructure.CAN_ABOM = ENABLE;			   //MCR-ABOM  �Զ����߹��� 
	CAN_InitStructure.CAN_AWUM = ENABLE;			   //MCR-AWUM  ʹ���Զ�����ģʽ
	CAN_InitStructure.CAN_NART = DISABLE;			   //MCR-NART  ��ֹ�����Զ��ش�	  DISABLE-�Զ��ش�
	CAN_InitStructure.CAN_RFLM = DISABLE;			   //MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���  
	CAN_InitStructure.CAN_TXFP = DISABLE;			   //MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ��
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	   //Mode  ����ģʽ
	
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;		   	   //BTR-SJW ����ͬ����Ծ��� 2��ʱ�䵥Ԫ
	
	/* ss=1 bs1=5 bs2=3 λʱ����Ϊ(1+9+4) �����ʼ�Ϊʱ������tq*(1+9+4)  */
	CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;		   //BTR-TS1 ʱ���1 ռ����6��ʱ�䵥Ԫ
	CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;		   //BTR-TS1 ʱ���2 ռ����3��ʱ�䵥Ԫ	
	
	/* CAN Baudrate = 1 MBps (1MBps��Ϊstm32��CAN�������) (CAN ʱ��Ƶ��Ϊ APB 1 = 42 MHz) */
	CAN_InitStructure.CAN_Prescaler = 5;		   ////BTR-BRP �����ʷ�Ƶ��  ������ʱ�䵥Ԫ��ʱ�䳤�� 42/(1+9+4)/3=1 Mbps
	CAN_Init(CAN2, &CAN_InitStructure);
	
	/*********************CANɸѡ����ʼ��***********************************************/
	CAN_FilterInitStructure.CAN_FilterNumber = 14;									//ɸѡ����0
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;					//������ID����ģʽ
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;				//ɸѡ��λ��Ϊ����32λ��
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;			//ɸѡ����������FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			//ʹ��ɸѡ��
	/* ʹ��ɸѡ�������ձ�־�����ݽ��бȶ�ɸѡ����չID�������µľ����������ǵĻ��������FIFO0�� */
	
	//�����й���
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				//Ҫɸѡ��ID��λ 
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; 				//Ҫɸѡ��ID��λ 
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;			//ɸѡ����16λÿλ����ƥ��
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			//ɸѡ����16λÿλ����ƥ��
	
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	/* FIFO0 message pending interrupt */
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
}


/**
  * @brief  CAN2���ٳ�ʼ��
  * @param  None
  * @retval None
  */
//void CAN2_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	CAN_InitTypeDef CAN_InitStructure;
//	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	/* ʹ�� GPIO ʱ�� */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//	//ʹ��CAN2ʱ��
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
//	
//	/* GPIO��ʼ�� */
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	
//	/* ����Tx����  */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  
//	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	/* ����Rx���� */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//	/* ���� IO �� CAN2_Tx*/
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);

//	/*  ���� IO �� CAN2_Rx*/
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
//	
//	/************************CAN ģʽ����*********************************************/
//	CAN_InitStructure.CAN_TTCM = DISABLE;			   //MCR-TTCM  ʱ�䴥��ͨ��ģʽ
//	CAN_InitStructure.CAN_ABOM = ENABLE;			   //MCR-ABOM  �Զ����߹��� 
//	CAN_InitStructure.CAN_AWUM = ENABLE;			   //MCR-AWUM  ʹ���Զ�����ģʽ
//	CAN_InitStructure.CAN_NART = DISABLE;			   //MCR-NART  ��ֹ�����Զ��ش�	  DISABLE-�Զ��ش�
//	CAN_InitStructure.CAN_RFLM = DISABLE;			   //MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���  
//	CAN_InitStructure.CAN_TXFP = DISABLE;			   //MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ��
//	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	   //Mode  ����ģʽ
//	
//	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;		   	   //BTR-SJW ����ͬ����Ծ��� 2��ʱ�䵥Ԫ
//	
//	/* ss=1 bs1=5 bs2=3 λʱ����Ϊ(1+9+4) �����ʼ�Ϊʱ������tq*(1+9+4)  */
//	CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;		   //BTR-TS1 ʱ���1 ռ����6��ʱ�䵥Ԫ
//	CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;		   //BTR-TS1 ʱ���2 ռ����3��ʱ�䵥Ԫ	
//	
//	/* CAN Baudrate = 1 MBps (1MBps��Ϊstm32��CAN�������) (CAN ʱ��Ƶ��Ϊ APB 1 = 42 MHz) */
//	CAN_InitStructure.CAN_Prescaler = 5;		   ////BTR-BRP �����ʷ�Ƶ��  ������ʱ�䵥Ԫ��ʱ�䳤�� 42/(1+9+4)/3=1 Mbps
//	CAN_Init(CAN2, &CAN_InitStructure);
//	
//	/*********************CANɸѡ����ʼ��***********************************************/
//	CAN_FilterInitStructure.CAN_FilterNumber = 14;									//ɸѡ����0
//	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;					//������ID����ģʽ
//	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;				//ɸѡ��λ��Ϊ����32λ��
//	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;			//ɸѡ����������FIFO0
//	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			//ʹ��ɸѡ��
//	/* ʹ��ɸѡ�������ձ�־�����ݽ��бȶ�ɸѡ����չID�������µľ����������ǵĻ��������FIFO0�� */
//	
//	//�����й���
//	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				//Ҫɸѡ��ID��λ 
//	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; 				//Ҫɸѡ��ID��λ 
//	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;			//ɸѡ����16λÿλ����ƥ��
//	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			//ɸѡ����16λÿλ����ƥ��
//	
//	CAN_FilterInit(&CAN_FilterInitStructure);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	/* FIFO0 message pending interrupt */
//	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);

//}
/**
  * @Data    2019-02-19 11:42
  * @brief   ͨ��CAN����ָ���Ӧ��ID��
  * @param   CAN_TypeDef* CANx,   ��Ӧ��CAN
  *          uint8_t id_type,     ��Ӧ��IDģʽ
  *          uint32_t id,         ��Ӧ��ID
  *          uint8_t data[8]      ���������
  * @retval  void
  */
void CAN_sendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, \
uint8_t data[8])
{ 
    CanTxMsg TxMessage;

    /*ID��*/
    if(id_type == CAN_Id_Standard) 
		{
        TxMessage.StdId = id;
    }
    else 
		{
        TxMessage.ExtId = id;					 
    }

    /*ID����*/
    TxMessage.IDE = id_type;

    /*���͵�����*/					 
    TxMessage.RTR = CAN_RTR_DATA;	

    /*���ݳ����ֽ�Ϊ8*/
    TxMessage.DLC = 0x08;						 

    /*����Ҫ���͵����ݣ�������ṹ����*/
    for (uint8_t i = 0; i < 8; i++)
    {
        TxMessage.Data[i] = data[i];
    }

    /*��������*/
    CAN_Transmit(CANx, &TxMessage);
}
/*-----------------------------------file of end------------------------------*/
