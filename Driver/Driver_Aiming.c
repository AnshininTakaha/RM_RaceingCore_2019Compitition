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
  |--FileName    : Control_Aiming.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ���� & �                                                     
  |--Date        : 2019-03-26             
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
 
#include "Driver_Aiming.h" 

#include "Task_Control.h"
#include "Driver_Filter.h"
#include "Driver_IMU.h"
#include "Driver_Analysis.h"
#include "Driver_CRC.h"
#include "Control_PC.h"
#include "BSP_Init.h"
/*�������ݴ���ṹ��*/
CV_t CV;



int SHOOTCOUNTER;
/*Ԥ��ƫ����*/
float CVOffset_x = 0,CVOffset_y = 0;
//float YtempSet = 60;
float FrameCounter,Frame;
int16_t vision_offset_y = 130;

/**
  * @Data    2019-03-26 20:00
  * @brief   �����������
  * @param   uint8_t *InputData ��������
  * @retval  void
  */

float vision_forecast_coe = 0.0f;
float YP = -50,XP = 0;
float YPF = -80;
void AimingControl(uint8_t *InputData)
{
		if(InputData == NULL)
		{
				return;
		}
		
		/*Ԥ��ֵ*/
		
		
		/*��λ��CRCУ��λ*/
		uint8_t CRCBuffer = Checksum_CRC8(InputData,12);
		/*��λ��CRC��ֵ*/
		uint8_t CRCSenderBuffer = ((InputData[12]-48)*100)+\
																	 		((InputData[13]-48)*10) + \
																			((InputData[14]-48)*1); 
		
		/*�ж�֡β��CRC8У���Ƿ���ȷ*/
		if(InputData[15] == 'E' && CRCBuffer == CRCSenderBuffer)
		{
				/*CRC��֡βʶ����ȷ������ж�*/
				GPIO_ToggleBits(GPIOE,GPIO_Pin_12);
				CV.Input_x = ((InputData[3]-48)*100+(InputData[4]-48)*10+(InputData[5]-48));
				CV.Input_y = ((InputData[6]-48)*100+(InputData[7]-48)*10+(InputData[8]-48));
				CV.Input_z = ((InputData[9]-48)*100+(InputData[10]-48)*10+(InputData[11]-48));
				
				/*��ȥ�е�*/
				CV.Input_x -=320;
				CV.Input_y -=240;
			
				/*�ڴ����������£������ƶ�����������¼�������*/
				if(CV.Input_y != 0 && SEDV_BIGER == 1)
				{
						CV.Input_y += YP;
				}
				
				/*������һ֡�����ݱ仯�ʴ�С*/
				CV.ErrorC_x = CV.Input_x - CV.LastInput_x;
				CV.ErrorC_y = CV.Input_y - CV.LastInput_y;
			
				/*�ж���һ֡����Ƿ�Ϊ��*/
				if(CV.Input_z != 0)
				{
						/*y��ƫ�����������matlab����ó����;�����һ����ϵ*/
						CVOffset_y = 0.002 * CV.Input_z * CV.Input_z - 0.8668 * CV.Input_z + vision_offset_y;

						/*�����ݹ�*/
						CV.LastInput_x = CV.Input_x;
						CV.LastInput_y = CV.Input_y;
						
				}
				else
				{
						CV.LastInput_x = CVOffset_x;
						CV.LastInput_y = CVOffset_y;
				}
				
//				CV.LastInput_x = CV.Input_x;
//				CV.LastInput_y = CV.Input_y;
				/*֡�ʿ���*/
				CV.UpdateFrame++;
				FrameCounter++;
		}
		
		/*����ͷ֡�ʼ���*/
		if(TimeCounter >= 200)
		{
				TimeCounter = 0;
				Frame = FrameCounter;
				FrameCounter = 0;
		}
		
		if(InputData[1] == '1')
		{
				CV.RealFrontSet = 1;
		}
		else if(InputData[1] == '0')
		{
				CV.RealFrontSet = 0;
		}
		
		/*���ݴ���*/
		CV.Output_x = CV.Input_x;
		CV.Output_y = CV.Input_y;
		CV.Output_z = CV.Input_z;
		
}


/**
  * @Data    2019-03-26 20:00
  * @brief   ������������
  * @param   uint8_t *InputData ��������
  * @retval  void
  */
int16_t vision_offset_y;
int16_t vision_offset_x;
CVN_t VisionData;

void NEWAimingControl(uint8_t *data)
{
		if ((data[0] == 0x55) || (data[0] == 0xA5))
		{
				/*ʶ��Ŀ��*/
				VisionData.Vision_Status = 1;
			
				/*��Ӧ��Χ*/
				VisionData.vision_x = ((data[1]<<8) | data[2]) - 320;
				VisionData.vision_y = ((data[3]<<8) | data[4]) - 240;
				VisionData.vision_fps = ((data[8]<<8) | data[9]);
				VisionData.vision_depth = ((data[10]<<8) | data[11]);
				
				VisionData.vision_diff_x = VisionData.vision_x - VisionData.vision_last_x;
				VisionData.vision_diff_y = VisionData.vision_y - VisionData.vision_last_y;
				vision_offset_y = 0.0020*VisionData.vision_depth*VisionData.vision_depth - 0.8668*VisionData.vision_depth;
			
				if(ABS(VisionData.vision_diff_x) < 5)
				{
						vision_offset_x = IMU_Cloud.data.gyro_z * vision_forecast_coe;
						
				}
				else
				{
						vision_offset_x = 0;
				}
				
			VisionData.vision_last_x = VisionData.vision_x;
			VisionData.vision_last_y = VisionData.vision_y;
			
			
		}
		else if (data[0] == 0xA5)
		{
		 VisionData.Vision_Status = 0;//���ö�ʧĿ���־
		 
		 VisionData.vision_x = 0;
		 VisionData.vision_y = 0;
		 VisionData.vision_diff_x = 0;
		 VisionData.vision_diff_y = 0;
		 VisionData.vision_last_x = vision_offset_x;
		 VisionData.vision_last_y = vision_offset_y;
		}
}
//  //�����    
//  if (data[0] == 0x55)//ʶ��Ŀ��
//  {
//   VisionData.Vision_status = 1;//ʶ��Ŀ��
//   VisionData.vision_x = ((data[1]<<8) | data[2]) - 320;
//   VisionData.vision_y = ((data[3]<<8) | data[4]) - 240;
//   VisionData.vision_fps = ((data[8]<<8) | data[9]);//֡��
//   VisionData.vision_depth = ((data[10]<<8) | data[11]);//���
//   
//   //����x��y��΢��
//   VisionData.vision_diff_x = VisionData.vision_x - VisionData.vision_last_x;
//   VisionData.vision_diff_y = VisionData.vision_y - VisionData.vision_last_y;
//   vision_offset_y = 0.0020*GetVisionDepth()*GetVisionDepth() - 0.8668*GetVisionDepth() + vision_offset_error_y;
//   
//   if(ABS(VisionData.vision_diff_x) < 5)   
//   {
//    vision_offset_x = GetImuGry_Z(GY955) * vision_forecast_coe + vision_offset_error_x;
//    //vision_offset_x = (VisionData.vision_depth/2000.0f) * GetImuGry_Z(GY955) * 6.0f - 20;
//   }
//   else
//   {
//    vision_offset_x = vision_offset_error_x;
//   }
//    
//   VisionData.vision_last_x = VisionData.vision_x;
//   VisionData.vision_last_y = VisionData.vision_y;
//  }//û��ʶ��Ŀ��
//  else if (data[0] == 0xA5)
//  {
//   VisionData.Vision_status = 0;//���ö�ʧĿ���־
//   
//   VisionData.vision_x = 0;
//   VisionData.vision_y = 0;
//   VisionData.vision_diff_x = 0;
//   VisionData.vision_diff_y = 0;
//   VisionData.vision_last_x = vision_offset_x;
//   VisionData.vision_last_y = vision_offset_y;
//  }
//}

		




/*-----------------------------------file of end------------------------------*/


