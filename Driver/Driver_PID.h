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
  |--FileName    : Driver_PID.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
  |--Date        : 2019-03-23               
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
#ifndef __DRIVER_PID_H 
#define __DRIVER_PID_H 



#include "stm32f4xx.h"

/* =========================== INC_PID of begin =========================== */
typedef struct incrementalpid_t
{
	float Kp;
	float Ki;
	float Kd;
	uint32_t MaxOutput;
	uint32_t IntegralLimit;
	float Target_speed;       
	float Measured_speed;
	float error;
	float last_error;
	float beforelast_error;
	float Kp_Output;
	float Ki_Output;
	float Kd_Output;
	float PWM;
	void (*Inc_Calc)(struct incrementalpid_t *pid,float target,float measured);
}incrementalpid_t;


/* =========================== INC_PID of end =========================== */

/* =========================== POS_PID of begin =========================== */
typedef struct positionpid_t
{
	float Kp;
	float Ki;
	float Kd;
	float KpRule[4];
	float KiRule[4];
	float KdRule[4];
	uint32_t MaxOutput;
	uint32_t IntegralLimit;
	float Target;
	float Measured;
	float error;
	float last_error;
	float Add_error;
	float ec_error; /*���仯��*/ 
	float Kp_Output;
	float Ki_Output;
	float Kd_Output;
	float PWM;
	/*ָ�뺯��*/
	void (*Pos_Calc)(struct positionpid_t *pid,float target,float measured);
}positionpid_t;


/* =========================== POS_PID of end =========================== */

/*����ʽPID����*/
void IncrementalPID_Calculation(incrementalpid_t *pid, float target, float measured);

/*λ��ʽPID����*/
void PositionPID_Calculation(positionpid_t *pid, float target, float measured);

/*ģ��λ��ʽPID����*/
void FuzzyPID_PosCalculation(positionpid_t *pid,float target, float measured);

/* =========================== FUZZYCAL of begin =========================== */
/*kpģ��ֵ�Ƶ�*/
float fuzzy_kp(float e, float ec, float InputKpRule[4]);

/*kiģ��ֵ�Ƶ�*/
float fuzzy_ki(float e, float ec, float InputKiRule[4]);

/*Kdģ��ֵ�Ƶ�*/
float fuzzy_kd(float e, float ec, float InputKdRule[4]);

/* =========================== FUZZYCAL of end =========================== */

#endif	// __DRIVER_PID_H
/*-----------------------------------file of end------------------------------*/


