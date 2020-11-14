
#include "Driver_MiniBalanceShowData.h"
#include "Driver_IMU.h"
#include "Driver_PID.h"
#include "Driver_Analysis.h"
#include "Driver_Aiming.h"
#include "Driver_Judge.h"
#include "Driver_Filter.h"
#include "Driver_DR16.h"
//#include "Driver_Power.h"
#include "Control_Cloud.h"
#include "Control_Chassis.h"
#include "Control_Shoot.h"

unsigned char DataScope_OutPut_Buffer[42] = {0};	   //串口发送缓冲区
unsigned char i;          //计数变量
unsigned char Send_Count; //串口需要发送的数据个数

//函数说明：将单精度浮点数据转成4字节数据并存入指定地址 
//附加说明：用户无需直接操作此函数 
//target:目标单精度数据
//buf:待写入数组
//beg:指定从数组第几个元素开始写入
//函数无返回 
void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;	  //得到float的地址
    buf[beg]   = point[0];
    buf[beg+1] = point[1];
    buf[beg+2] = point[2];
    buf[beg+3] = point[3];
}
 
 
//函数说明：将待发送通道的单精度浮点数据写入发送缓冲区
//Data：通道数据
//Channel：选择通道（1-10）
//函数无返回 
void DataScope_Get_Channel_Data(float Data,unsigned char Channel)
{
	if ( (Channel > 10) || (Channel == 0) ) return;  //通道个数大于10或等于0，直接跳出，不执行函数
  else
  {
     switch (Channel)
		{
      case 1:  Float2Byte(&Data,DataScope_OutPut_Buffer,1); break;
      case 2:  Float2Byte(&Data,DataScope_OutPut_Buffer,5); break;
		  case 3:  Float2Byte(&Data,DataScope_OutPut_Buffer,9); break;
		  case 4:  Float2Byte(&Data,DataScope_OutPut_Buffer,13); break;
		  case 5:  Float2Byte(&Data,DataScope_OutPut_Buffer,17); break;
		  case 6:  Float2Byte(&Data,DataScope_OutPut_Buffer,21); break;
		  case 7:  Float2Byte(&Data,DataScope_OutPut_Buffer,25); break;
		  case 8:  Float2Byte(&Data,DataScope_OutPut_Buffer,29); break;
		  case 9:  Float2Byte(&Data,DataScope_OutPut_Buffer,33); break;
		  case 10: Float2Byte(&Data,DataScope_OutPut_Buffer,37); break;
		}
  }	 
}


//函数说明：生成 DataScopeV1.0 能正确识别的帧格式
//Channel_Number，需要发送的通道个数
//返回发送缓冲区数据个数
//返回0表示帧格式生成失败 
unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
{
	if ( (Channel_Number > 10) || (Channel_Number == 0) ) { return 0; }  //通道个数大于10或等于0，直接跳出，不执行函数
  else
  {	
	 DataScope_OutPut_Buffer[0] = '$';  //帧头
		
	 switch (Channel_Number)   
   { 
		 case 1:   DataScope_OutPut_Buffer[5]  =  5; return  6;  
		 case 2:   DataScope_OutPut_Buffer[9]  =  9; return 10;
		 case 3:   DataScope_OutPut_Buffer[13] = 13; return 14; 
		 case 4:   DataScope_OutPut_Buffer[17] = 17; return 18;
		 case 5:   DataScope_OutPut_Buffer[21] = 21; return 22;  
		 case 6:   DataScope_OutPut_Buffer[25] = 25; return 26;
		 case 7:   DataScope_OutPut_Buffer[29] = 29; return 30; 
		 case 8:   DataScope_OutPut_Buffer[33] = 33; return 34; 
		 case 9:   DataScope_OutPut_Buffer[37] = 37; return 38;
     case 10:  DataScope_OutPut_Buffer[41] = 41; return 42; 
   }	 
  }
	return 0;
}

//extern PIDRegulator_t CloudYaw_OPID,CloudYaw_IPID;
//extern FuzzyPID_t YawFuzzyPID;
//extern float errorrate;
//extern  IMU_Param_t MPU6050_Data;
//extern short aacx1;
//extern float baro;
//extern VisionData_t VisionData;
//extern Filter_t filter_x;
//extern Filter_t filter_y;
//extern  RammerParam_t  RammerParam;
//extern kalman_filter_t kalman_filter;
//extern NDOF055Data_t NDOF055_data;
//extern Rammer_Param_t  Ram mer_Param;
//int16_t tesss,tesss1;
//extern CloudParam_t CloudParam;
//extern Filter_t filter1;
//extern Filter_LPF_t Filter_LPFp;
//extern Filter_LPF_t Filter_LPFp1;
//extern NDOF055Data_t ChassisNDOF055_data;
//extern float readangle,angle,temp2;


void DataScopeTask(void *Parameters)
{   
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	for(;;)
	{
		//float tt = NDOF055_data.data.gyro_z/GetCloudMotorRotate(Yaw);
		//DataScope_Get_Channel_Data(kalman_filter.filtered_value[0], 1 );
		//DataScope_Get_Channel_Data(tesss1, 2 );  
//			DataScope_Get_Channel_Data(AngleRead,1);
//			DataScope_Get_Channel_Data(IMUAngleRead,2);
//			DataScope_Get_Channel_Data(IMU_PI_AngleRead,3);
//			DataScope_Get_Channel_Data(RM6020s[0].outCurrent,4);
//			DataScope_Get_Channel_Data(TempPush,5);
//			DataScope_Get_Channel_Data(TempPushCal,6);
//				DataScope_Get_Channel_Data(Chassis_speed_offset ,1);
//				DataScope_Get_Channel_Data(IMU_Chassis.data.gyro_z*16 ,2);
//				DataScope_Get_Channel_Data(Yaw_InnerRing.PWM ,3);
//				DataScope_Get_Channel_Data(RM6020s[0].outCurrent,4);
//				DataScope_Get_Channel_Data(angle,5);
//				DataScope_Get_Channel_Data(state,1);
//				DataScope_Get_Channel_Data(LOOKsuminput,2);
				DataScope_Get_Channel_Data(RM3508s[0].outCurrent,3);
				DataScope_Get_Channel_Data(RM3508s[1].outCurrent,4);
				DataScope_Get_Channel_Data(RM3508s[2].outCurrent,5);
				DataScope_Get_Channel_Data(RM3508s[3].outCurrent,6); 
		//DataScope_Get_Channel_Data(Filter_LPFp1.Output, 5); 		
		//DataScope_Get_Channel_Data(Filter_LPFp.Output, 2 );
		Send_Count = DataScope_Data_Generate(8);
		for ( i = 0 ; i < Send_Count; i++) 
		{
			while ((USART2->SR&0X40)==0);  
			USART2->DR = DataScope_OutPut_Buffer[i]; 
		}
		vTaskDelayUntil(&xLastWakeTime, 20);
	}
}






 




