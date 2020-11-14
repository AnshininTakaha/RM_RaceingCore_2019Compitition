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
  |--FileName    : BSP_USART.c                                              
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
#include "BSP_USART.h" 

#pragma import(__use_no_semihosting)    

/* =========================== supportfunctions of begin =========================== */
/*��׼����Ҫ��֧�ֺ��� */
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;  

/*����_sys_exit()�Ա���ʹ�ð�����ģʽ*/
void _sys_exit(int x) 
{ 
	x = x; 
} 

/*�����ض�����ܺ�����Ӧ����*/
static USART_TypeDef* Using_USART = USART2;

/*�ض��巢�ͺ���*/
int fputc(int ch, FILE *f)
{
    USART_SendData(Using_USART, (uint8_t) ch);
    while (USART_GetFlagStatus(Using_USART, USART_FLAG_TXE) == RESET);
    return (ch);
}

/*���¶�����ܴ���*/
int fgetc(FILE* f)
{
    while (USART_GetFlagStatus(Using_USART, USART_FLAG_RXNE) == RESET);
    return (int)USART_ReceiveData(Using_USART);
}


/* =========================== supportfunctions of end =========================== */

/* =========================== AbilityFunctions of begin =========================== */
/*����һ���ַ�*/
void USART_SendByte(USART_TypeDef*USARTx,uint8_t ch)
{
	USART_SendData(USARTx,ch);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
}

/*����һ���ַ���*/
void USART_SendString(USART_TypeDef*USARTx,char*str)
{
	unsigned int k=0;
	do{
		USART_SendByte(USARTx,*(str+k));
	    k++;	
	}while(*(str+k)!= '\0');
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET)
	{
	}
}
/* =========================== AbilityFunctions of end =========================== */

/**
  * @Data    2019-03-22 21:48
  * @brief   USART1���ٳ�ʼ����DR16��
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART1_QuickInit(uint32_t USART_BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(USART1_TX_GPIO_CLK,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    /* ����Tx����  */
    GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;
    GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

    /* ����Rx���� */
    GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
    GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);

    /* ���� PXx �� USARTx_Tx����ʵ����IO�ڸ���*/
    GPIO_PinAFConfig(USART1_TX_GPIO_PORT, USART1_TX_PINSOURCE, GPIO_AF_USART1);

    /*  ���� PXx �� USARTx_Rx����ʵ����IO�ڸ���*/
    GPIO_PinAFConfig(USART1_RX_GPIO_PORT, USART1_RX_PINSOURCE, GPIO_AF_USART1);

    /* ���ô�USART ģʽ */
    USART_InitStructure.USART_BaudRate = USART_BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    /* �����ж����ȼ����� */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

    /* ʹ�ܴ��ڿ����ж� */
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

    /* ʹ�ܴ��� */
    USART_Cmd(USART1, ENABLE);
}

/**
  * @Data    2019-03-22 21:53
  * @brief   USART1_DMA��ʼ����DR16��
  * @param   uint32_t USART1_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize)
{
    DMA_InitTypeDef DMA_InitStructure;

    /*����DMA2ʱ��*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    DMA_DeInit(USART1_RX_DMA_STREAM);

    /* ȷ��DMA��������λ��� */
    while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != DISABLE)
    {
        /*���û�и�λ��ɻ����޵Ŀ���while����*/
    }

    DMA_InitStructure.DMA_Channel = USART1_RX_DMA_CHANNEL;
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_RX_ADDR;//(uint32_t)(&USART1->DR)	//����1���ݼĴ�����ַ

    /*USART1_DMABuff_addr ->����*/
    DMA_InitStructure.DMA_Memory0BaseAddr = USART1_DMABuff_addr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;

    /*�����СDMA_BufferSize=SENDBUFF_SIZE*/
    DMA_InitStructure.DMA_BufferSize = buffsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

    /*����FIFO*/
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;

    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

    /*����DMA2��������*/
    DMA_Init(USART1_RX_DMA_STREAM, &DMA_InitStructure);

    /*ʹ��DMA*/
    DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);

    /* �ȴ�DMA��������Ч*/
    while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != ENABLE)
    {
    }

    /*ʹ��DMA��������*/
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
}

/**
  * @Data    2019-03-23 10:21
  * @brief   USART2���ٳ�ʼ���������Ӿ���׼��
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART2_QuickInit(uint32_t USART_BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(USART2_TX_GPIO_CLK | USART2_RX_GPIO_CLK,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    /* ����Tx����  */
    GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;  
    GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);

    /* ����Rx���� */
    GPIO_InitStructure.GPIO_Pin = USART2_RX_Pin;
    GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
    
    /* ���� PXx �� USARTx_Tx*/
    GPIO_PinAFConfig(USART2_TX_GPIO_PORT, USART2_TX_PINSOURCE, GPIO_AF_USART2);

    /*  ���� PXx �� USARTx_Rx*/
    GPIO_PinAFConfig(USART2_RX_GPIO_PORT, USART2_RX_PINSOURCE, GPIO_AF_USART2);

    /*����USARTģʽ*/
    USART_InitStructure.USART_BaudRate = USART_BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure); 
	
	  /* �����ж����ȼ����� */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	  
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
    USART_Cmd(USART2, ENABLE);
}

/**
  * @Data    2019-03-23 10:28
  * @brief   USART2_DMA��ʼ�����Ӿ����飩
  * @param   uint32_t USART2_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize)
{
    DMA_InitTypeDef DMA_InitStructure;


    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
    DMA_DeInit(USART2_RX_DMA_STREAM);

    /* ȷ��DMA��������λ��� */
    while(DMA_GetCmdStatus(USART2_RX_DMA_STREAM) != DISABLE)
    {
    }

    DMA_InitStructure.DMA_Channel = USART2_RX_DMA_CHANNEL;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_RX_ADDR;	 
    DMA_InitStructure.DMA_Memory0BaseAddr = USART2_DMABuff_addr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
    DMA_InitStructure.DMA_BufferSize = buffsize;    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;		
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    	   
    DMA_Init(USART2_RX_DMA_STREAM, &DMA_InitStructure);
      
    /*ʹ��DMA*/
    DMA_Cmd(USART2_RX_DMA_STREAM, ENABLE);
    
    /* �ȴ�DMA��������Ч*/
    while(DMA_GetCmdStatus(USART2_RX_DMA_STREAM) != ENABLE)
    {
    }
    
    //ʹ��DMA����  
    USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); 
}

/**
  * @Data    2019-03-23 10:31
  * @brief   USART3���ٳ�ʼ��������ϵͳ��
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART3_QuickInit(uint32_t USART_BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(USART3_TX_GPIO_CLK | USART3_RX_GPIO_CLK,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    
    GPIO_InitStructure.GPIO_Pin = USART3_TX_Pin;  
    GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART3_RX_Pin;
    GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);
    

    GPIO_PinAFConfig(USART3_TX_GPIO_PORT, USART3_TX_PINSOURCE, GPIO_AF_USART3);
    GPIO_PinAFConfig(USART3_RX_GPIO_PORT, USART3_RX_PINSOURCE, GPIO_AF_USART3);
    
    USART_InitStructure.USART_BaudRate = USART_BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure); 


    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//�����ж�
    USART_Cmd(USART3, ENABLE);
}

/**
  * @Data    2019-03-23 10:32
  * @brief   USART3_DMA������ϵͳ��
  * @param   uint32_t USART1_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize)
{
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
      
    DMA_DeInit(USART3_RX_DMA_STREAM);

    while(DMA_GetCmdStatus(USART3_RX_DMA_STREAM) != DISABLE)
    {
    }

    DMA_InitStructure.DMA_Channel = USART3_RX_DMA_CHANNEL;
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART3_RX_ADDR;
    DMA_InitStructure.DMA_Memory0BaseAddr = USART3_DMABuff_addr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = buffsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(USART3_RX_DMA_STREAM, &DMA_InitStructure);

    DMA_Cmd(USART3_RX_DMA_STREAM, ENABLE);
  
    while(DMA_GetCmdStatus(USART3_RX_DMA_STREAM) != ENABLE)
    {
    }
    
    USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);

}


/**
  * @Data    2019-03-23 10:43
  * @brief   USART6��ʼ���������ǣ�
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART6_QuickInit(uint32_t USART_BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(USART6_TX_GPIO_CLK | USART6_RX_GPIO_CLK,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = USART6_TX_Pin;  
    GPIO_Init(USART6_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART6_RX_Pin;
    GPIO_Init(USART6_RX_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(USART6_TX_GPIO_PORT, USART6_TX_PINSOURCE, GPIO_AF_USART6);
    GPIO_PinAFConfig(USART6_RX_GPIO_PORT, USART6_RX_PINSOURCE, GPIO_AF_USART6);

    USART_InitStructure.USART_BaudRate = USART_BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART6, &USART_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);//�����ж�
    
    USART_Cmd(USART6, ENABLE);
}

/**
  * @Data    2019-03-23 11:03
  * @brief   USART6_DMA��ʼ���������ǣ�
  * @param   uint32_t USART6_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize)
{
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    DMA_DeInit(USART6_RX_DMA_STREAM);

    /* ȷ��DMA��������λ��� */
    while(DMA_GetCmdStatus(USART6_RX_DMA_STREAM) != DISABLE)
    {
    }

    DMA_InitStructure.DMA_Channel = USART6_RX_DMA_CHANNEL;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART6_RX_ADDR;	 
    DMA_InitStructure.DMA_Memory0BaseAddr = USART6_DMABuff_addr;	
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
    DMA_InitStructure.DMA_BufferSize = buffsize;	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
		   
    DMA_Init(USART6_RX_DMA_STREAM, &DMA_InitStructure);
      

    DMA_Cmd(USART6_RX_DMA_STREAM, ENABLE);
    

    while(DMA_GetCmdStatus(USART6_RX_DMA_STREAM) != ENABLE)
    {
    }
    
    USART_DMACmd(USART6,USART_DMAReq_Rx,ENABLE);
}


/**
  * @Data    2019-03-23 11:03
  * @brief   USART7��ʼ�����������鱸ѡ��
  * @param   uint32_t USART6_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART7_QuickInit(uint32_t USART_BaudRate)
{
		//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE); //ʹ��GPIODʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7,ENABLE);//ʹ��USART2ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_UART7); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_UART7); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_7; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOE,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = USART_BaudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(UART7, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(UART7, ENABLE);  //ʹ�ܴ���2 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_ITConfig(UART7, USART_IT_IDLE, ENABLE);//�����ж�
	//USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=5;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}


/**
  * @Data    2019-03-23 11:03
  * @brief   USART7_DMA��ʼ���������ǣ�
  * @param   uint32_t USART6_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART7_RXDMA_Config(uint32_t USART7_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//����DMA1ʱ��
	  
	DMA_DeInit(DMA1_Stream3);// ��λ��ʼ��DMA������ 

	while(DMA_GetCmdStatus(DMA1_Stream3) != DISABLE);//ȷ��DMA��������λ���
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_5; //usart6 rx��Ӧdma1��ͨ��5��������1 	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART7->DR);	//����DMAԴ���������ݼĴ�����ַ 	
	DMA_InitStructure.DMA_Memory0BaseAddr = USART7_DMABuff_addr;//���ַ(Ҫ����ı�����ָ��)
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//���򣺴����赽�ڴ�		
	DMA_InitStructure.DMA_BufferSize = buffsize;	//�����СDMA_BufferSize=SENDBUFF_SIZE		
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ����    	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݵ�λ		
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//�ڴ����ݵ�λ 8bit	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMAģʽ������ѭ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//���ȼ�����	     
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//����FIFO       
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//�洢��ͻ������ 16 ������   	
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //����ͻ������ 1 ������ 
	DMA_Init(DMA1_Stream3, &DMA_InitStructure);//����DMA2��������		 
	  
	DMA_Cmd(DMA1_Stream3, ENABLE);//ʹ��DMA
  
	while(DMA_GetCmdStatus(DMA1_Stream3) != ENABLE);// �ȴ�DMA��������Ч
  
	USART_DMACmd(UART7,USART_DMAReq_Rx,ENABLE); 	//ʹ��DMA����
}



/**
  * @Data    2019-03-23 10:43
  * @brief   USART8��ʼ���������ǣ�
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART8_QuickInit(uint32_t USART_BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(USART8_TX_GPIO_CLK | USART8_RX_GPIO_CLK,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);
  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = USART8_TX_Pin;  
    GPIO_Init(USART8_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART8_RX_Pin;
    GPIO_Init(USART8_RX_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(USART8_TX_GPIO_PORT, USART8_TX_PINSOURCE, GPIO_AF_UART8);
    GPIO_PinAFConfig(USART8_RX_GPIO_PORT, USART8_RX_PINSOURCE, GPIO_AF_UART8);

    USART_InitStructure.USART_BaudRate = USART_BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART8, &USART_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(UART8, USART_IT_IDLE, ENABLE);//�����ж�
    
    USART_Cmd(UART8, ENABLE);
}


void USART8_RXDMA_Config(uint32_t USART8_DMABuff_addr, uint32_t buffsize)
{
		DMA_InitTypeDef DMA_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
		DMA_DeInit(DMA1_Stream6);
		while(DMA_GetCmdStatus(DMA1_Stream6) != DISABLE)
		{
		}
		DMA_InitStructure.DMA_Channel = DMA_Channel_5; //usart6 rx��Ӧdma1��ͨ��5��������1 	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART8->DR);	//����DMAԴ���������ݼĴ�����ַ 	
	DMA_InitStructure.DMA_Memory0BaseAddr = USART8_DMABuff_addr;//���ַ(Ҫ����ı�����ָ��)
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//���򣺴����赽�ڴ�		
	DMA_InitStructure.DMA_BufferSize = buffsize;	//�����СDMA_BufferSize=SENDBUFF_SIZE		
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ����    	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݵ�λ		
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//�ڴ����ݵ�λ 8bit	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMAģʽ������ѭ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//���ȼ�����	     
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//����FIFO       
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//�洢��ͻ������ 16 ������   	
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //����ͻ������ 1 ������ 
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);//����DMA2��������

	DMA_Cmd(DMA1_Stream6, ENABLE);//ʹ��DMA
  
	while(DMA_GetCmdStatus(DMA1_Stream6) != ENABLE)
	{
			
	}
  
	USART_DMACmd(UART8,USART_DMAReq_Rx,ENABLE); 	//ʹ��DMA����  		
}
/**
	* @Data    2019-03-15 16:54
	* @brief   ANO����ר�ý�����
	* @param   USART_TypeDef* USARTx,char ch
	* @retval  void
	*/
void ANO_SendChar(USART_TypeDef* USARTx,char ch)
{
	USART_SendData(USARTx, (uint8_t) ch);
	while (USART_GetFlagStatus(Using_USART, USART_FLAG_TXE) == RESET);	  
}

void USART_sendChar(USART_TypeDef* USARTx,char ch)
{
	USART_SendData(USARTx, (uint8_t) ch);
	while (USART_GetFlagStatus(Using_USART, USART_FLAG_TXE) == RESET);	  
}

void USART3_sendChar(USART_TypeDef* USARTx,char ch)
{
	USART_SendData(USARTx, (uint8_t) ch);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	  
}

void USART_ALLFSendChar(USART_TypeDef* USARTx,char*str)
{
	unsigned int k=0;
	do{
		USART_SendByte(USARTx,*(str+k));
	    k++;	
	}while(*(str+k)!= '\0');
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET)
	{
	}
}

/*-----------------------------------file of end------------------------------*/


