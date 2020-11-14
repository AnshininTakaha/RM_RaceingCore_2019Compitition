/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无 & 璨，                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Driver_IMU.h                                                
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
#ifndef __DRIVER_IMU_H 
#define __DRIVER_IMU_H 



#include "BSP_Init.h"
#include "stm32f4xx.h"
#pragma anon_unions
#define RATIO 1
typedef struct 
{
		float x;
		float y;
		float z;
}vector_t;

typedef struct 
{
	float roll;
	float pitch;
	float yaw;
}eular_t;

typedef struct
{
	vector_t gyro;
	eular_t eular;
	
	float realYaw;
	float lastYaw;
	float totalYaw;
	int16_t turnCount;
	uint8_t devStatus; 
	
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}IMU_t;


typedef struct{
	union {
		uint8_t dataBuff[8];
		struct{
						uint16_t euler_yaw;
						int16_t gyro_z;
						int16_t euler_pitch;
						int16_t gyro_x;		
					};
	}data;
	
	float lastYaw;
	float totalYaw;
	int16_t turnCount;
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
} CANIMU_t;

/*IMU数据储存体*/
extern IMU_t IMU;
extern CANIMU_t IMU_Chassis;
extern CANIMU_t IMU_Cloud;
/*IMU解码*/
void IMU_Process(uint8_t* buff, uint16_t dataLength, IMU_t* dataOut);

/*IMU校验*/
uint8_t GY_IMU_Checksum(uint8_t* buff);

#endif	// __DRIVER_IMU_H
/*-----------------------------------file of end------------------------------*/


