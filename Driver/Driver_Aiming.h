/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,���� & 貣�                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Control_Aiming.h                                                
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
#ifndef __CONTROL_AIMING_H 
#define __CONTROL_AIMING_H 


#include "Switch.h"
#include "stm32f4xx.h"
//#include "arm_math.h"
#include "math.h"

/*����ƫ����*/
#define X_threshold 6
#define Y_threshold 12

#define X_BigStatethreshold 2         //10
#define Y_BigStatethreshold 2       

/*�Ƕȱ䳤��*/
#define Length_TOAngle 57.2958f
#define Gravity 9.87f
#define GUNSpeed 23.5f
#define AUTOAIM 0
#define BIGWHEEL 1

typedef struct
{
		/*�Ӿ�ģʽ*/
		uint8_t Vision_Mode;
		
    int Input_x;
    int Input_y;
    int Input_z;
    int Output_x;
    int Output_y;
    int Output_z;
		
		/*��֡���仯��*/
		int ErrorC_x;
		int ErrorC_y;
		int ErrorC_z;
		
		/*��һ������������*/
		int LastInput_x;
		int LastInput_y;
		int LastInput_z;
	
		/*���ݱ�־λ*/
		int RealFrontSet;
	
		/*֡�ʿ���*/
		uint16_t UpdateFrame;   /* ֡�� */
		uint8_t UpdateFlag;     /* ���±�־ */
		uint8_t OFFLINE_SET;        /* ���߱�� */
}CV_t;

typedef struct
{
		uint8_t Vision_Status;
		int16_t vision_x;
		int16_t vision_y;
		int16_t vision_Depth;
		int16_t vision_fps;
		int16_t vision_depth;
		
		int16_t vision_diff_x;
		int16_t vision_diff_y;
		
		int16_t vision_last_x;
		int16_t vision_last_y;
		
}CVN_t;

void BIGAimingControl(uint8_t *data);

/*�������ݴ���ṹ��*/
extern CV_t CV;

extern float CVOffset_x,CVOffset_y;

extern int SHOOTCOUNTER;

extern CVN_t VisionData;
extern int16_t vision_offset_y;
extern int16_t vision_offset_x;
/*����*/
void AimingControl(uint8_t *InputData);
void NEWAimingControl(uint8_t *data);

#endif	// __CONTROL_AIMING_H
/*-----------------------------------file of end------------------------------*/


