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
  |--FileName    : Driver_IMU.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无 & 璨                                                     
  |--Date        : 2019-03-24             
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
#include "Driver_IMU.h" 


#include "Control_Cloud.h"
#include "Driver_Filter.h"

/*IMU数据储存体*/
IMU_t IMU;
CANIMU_t IMU_Chassis;
CANIMU_t IMU_Cloud;
/**
  * @Data    2019-03-24 13:18
  * @brief   IMU数据解码
  * @param   uint8_t* buff, uint16_t dataLength, IMU_t* dataOut
  * @retval  void
  */
//	int Counter = 0;
void IMU_Process(uint8_t* buff, uint16_t dataLength, IMU_t* dataOut)
{
    for(uint16_t n = 0; n < dataLength; )
  {
    if( (buff[n] == 0x5A) && (buff[n+1] == 0x5A) )
		  {
        if(GY_IMU_Checksum(&buff[n]))
			  {
          int16_t DATA[6];
          DATA[0]=(buff[n+4]<<8) | buff[n+5];
          DATA[1]=(buff[n+6]<<8) | buff[n+7];
          DATA[2]=(buff[n+8]<<8) | buff[n+9];
          DATA[3]=(buff[n+10]<<8) | buff[n+11];
          DATA[4]=(buff[n+12]<<8) | buff[n+13];
          DATA[5]=(buff[n+14]<<8) | buff[n+15];
          
          dataOut->gyro.x = (float)DATA[0]/100;
          dataOut->gyro.y = (float)DATA[1]/100;
          dataOut->gyro.z = (float)DATA[2]/100;
          
          dataOut->eular.yaw = (float)((uint16_t)DATA[3])/100;
          dataOut->eular.roll = (float)DATA[4]/100;
          dataOut->eular.pitch = (float)DATA[5]/100;
          
          dataOut->devStatus = buff[n+16];

					
          /*计算总角度（防止一开始的过零问题）*/
          if(dataOut->eular.yaw - dataOut->lastYaw < -300)
					{
						dataOut->turnCount++;
					}
					
					if(dataOut->lastYaw - dataOut->eular.yaw < -300)
					{
						dataOut->turnCount--;
					}
					
					/*新PID计算*/
//					if(dataOut->eular.yaw - dataOut->lastYaw < -300)
//					{
//							dataOut->totalYaw = (dataOut->eular.yaw + 360) - dataOut->lastYaw;
//					}
//					if(dataOut->lastYaw - dataOut->eular.yaw < -300)
//					{
//							dataOut->totalYaw = dataOut->eular.yaw - (dataOut->lastYaw+360);
//					}
					
					dataOut->lastYaw =  dataOut->eular.yaw;
					
					dataOut->totalYaw = dataOut->eular.yaw + (360.0f * dataOut->turnCount);
					
					dataOut->UpdateFrame++;
					dataOut->UpdateFlag = 1;
					

				
				  return;

        }
        else
        {
          n++;
        }
        
      }
      else
      {
        n++;
      }
  }
}



/**
  * @Data    2019-02-24 14:32
  * @brief   IMU校验
  * @param   uint8_t* buff
  * @retval  uint8_t
  */
uint8_t GY_IMU_Checksum(uint8_t* buff)
{
  uint8_t sum = 0;
	
	for(uint8_t i=0; i<GYIMU_PACKSIZE-1; i++)
    {
		  sum += buff[i]; 
	  }
	
	if(sum == buff[GYIMU_PACKSIZE-1])
    {
		//校验通过
		  return 1;
	  }
	else
    {
		  return 0;
	  }
}
/*-----------------------------------file of end------------------------------*/


