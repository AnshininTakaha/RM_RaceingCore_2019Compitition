/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/


#include "Task_Init.h"

#include "Task_Control.h"
#include "Task_CAN.h"

#include "Driver_DR16.h"
#include "Driver_IMU.h"
#include "Driver_Judge.h"

#include "BSP_Init.h"
#include "RTOSinclude.h"
#include "stm32f4xx_it.h"
extern void xPortSysTickHandler( void );
/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)
	{
		xPortSysTickHandler();
	}
}



		



/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s).    */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  USART1 DR16 ң��������
	* @mode   �ж϶�ʱ��ϵͳ
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
	{
			if(USART_GetITStatus(USART1,USART_IT_IDLE) != RESET)
			{
				DMA_Cmd(DMA2_Stream2,DISABLE);
				
				if(DMA_GetCurrDataCounter(DMA2_Stream2) == 4)
				{
					DR16_Process(DBUS_DataBuff);
				}
				
				DMA_SetCurrDataCounter(DMA2_Stream2,18u+4);
				DMA_Cmd(DMA2_Stream2,ENABLE);
				
				/*USART1�����ж�*/
				(void)USART1->DR;
				(void)USART1->SR;
			}
	}


/**
  * @brief  USART2 �����ж�
	* @mode  	����ϵͳ
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
    /*�����ж��Ƿ���������ȼ��������״̬λ*/
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		if(USART_GetITStatus(USART2,USART_IT_IDLE) != RESET)
		{
			DMA_Cmd(USART2_RX_DMA_STREAM, DISABLE);
			
			/*�ӿ��ж��ٶȣ����ж϶��ƶ�����������ȥ*/
			xQueueSendFromISR(AimingRxQueue,&Vision_DataBuff,&xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			DMA_SetCurrDataCounter(USART2_RX_DMA_STREAM,VISION_BUFFSIZE);
			DMA_Cmd(USART2_RX_DMA_STREAM, ENABLE);

			/*���USART2���жϱ�־λ*/
			(void)USART2->DR;
			(void)USART2->SR;
		}
}

	
/**
  * @brief  USART2 �����ж�
	* @mode  	����ϵͳ
  * @param  None
  * @retval None
  */
uint16_t Judgement_Count;
void USART3_IRQHandler(void)
{
		/*�����ж��Ƿ���������ȼ��������״̬λ*/
//		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		if(USART_GetITStatus(USART3,USART_IT_IDLE) != RESET)
		{
				
				DMA_Cmd(DMA1_Stream1, DISABLE);
//				Judge_sendPC(110,0,0,0);
//				Judgement_Count = DMA_GetCurrDataCounter(DMA1_Stream1);
			/*DMAֱ�ӷ���Ȼ�����������洦��*/
//				Judgement_Check.UpdateFlag = 1;
//				xQueueSendFromISR(JudgementQueue,&Judge_DataBuff,&xHigherPriorityTaskWoken);
//				portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
				JudgeInfo_Process(Judge_DataBuff, Judge_BuffSIZE - DMA_GetCurrDataCounter(DMA1_Stream1));
				
				DMA_SetCurrDataCounter(DMA1_Stream1,Judge_BuffSIZE);
				DMA_Cmd(DMA1_Stream1, ENABLE);
				(void)USART3->DR;
				(void)USART3->SR;
		}	
}
/**
	* @name 	USART6��̨�������ж�
	* @mode 	�ж϶�ʱ��ϵͳ
	* @brief 	�������ж�
	* @param 	None
	* @retval
*/
uint16_t s_U6dataLength = 0;
void USART6_IRQHandler(void)
{
		/*�����ж��Ƿ���������ȼ��������״̬λ*/
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		if(USART_GetITStatus(USART6,USART_IT_IDLE)!= RESET)
		{
				
			DMA_Cmd(USART6_RX_DMA_STREAM,DISABLE);
			
			xQueueSendFromISR(AimingRxQueue,&Vision_DataBuff,&xHigherPriorityTaskWoken);
//			xQueueSendFromISR(AimingRxQueue,&Vision_DataBufferNew,&xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			DMA_SetCurrDataCounter(USART6_RX_DMA_STREAM,VISION_BUFFSIZE);
			DMA_Cmd(USART6_RX_DMA_STREAM, ENABLE);
	//		uint16_t DMA_Counter = DMA_GetCurrDataCounter(USART6_RX_DMA_STREAM);
	//		s_U6dataLength = GYIMU_BUFFSIZE - DMA_Counter;
	//		IMU_Process(GYIMU_RXBuff,s_U6dataLength,&IMU);
	//		GPIO_ToggleBits(GPIOE,GPIO_Pin_11);
	//		DMA_SetCurrDataCounter(USART6_RX_DMA_STREAM,GYIMU_BUFFSIZE);
			DMA_Cmd(USART6_RX_DMA_STREAM, ENABLE);
			
			(void)USART6->DR;
			(void)USART6->SR;
		}	
}

/**
  * @brief  CAN1 FIFO0 ���ݽ����ж�
	* @mode   �ж϶�ʱ��ϵͳ
  * @param  None
  * @retval None
  */
void CAN1_RX0_IRQHandler(void)
	{
			CAN_RXPrarm_t CANFeedback_MsgPrarm;
			BaseType_t xHigherPriorityTaskWoken = pdFALSE;
      if(CAN_GetITStatus(CAN1,CAN_IT_FMP0))
      {
          CAN_Receive(CAN1,CAN_FIFO0,&CANFeedback_MsgPrarm.RxMessage);
					CANFeedback_MsgPrarm.CANSet = 1;
          /*���д�����Ƿ����������ȼ�*/
          xQueueSendFromISR(xCanReciver,&CANFeedback_MsgPrarm,&xHigherPriorityTaskWoken);
          portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
          CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
      }
	}

	
/**
  * @brief  CAN2 FIFO0 ���ݽ����ж�
	* @mode   �ж϶�ʱ��ϵͳ
  * @param  None
  * @retval None
  */
void CAN2_RX0_IRQHandler(void)
	{
			CAN_RXPrarm_t CANFeedback_MsgPrarm;
			BaseType_t xHigherPriorityTaskWoken = pdFALSE;
      if(CAN_GetITStatus(CAN2,CAN_IT_FMP0))
      {
          CAN_Receive(CAN2,CAN_FIFO0,&CANFeedback_MsgPrarm.RxMessage);
					CANFeedback_MsgPrarm.CANSet = 2;
          /*���д�����Ƿ����������ȼ�*/
          xQueueSendFromISR(xCanReciver,&CANFeedback_MsgPrarm,&xHigherPriorityTaskWoken);
          portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
          CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
      }
	}
/**
  * @brief  TIM6 DAC �?�?服务函数
  * @param  None
  * @retval None
  */
//void TIM6_DAC_IRQHandler(void)//各�?�模式�?�应的速度模型处理
//{
//	
//}


/**
  * @}
  */ 

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
