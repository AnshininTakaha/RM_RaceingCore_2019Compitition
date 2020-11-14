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
  |--FileName    : Driver_SCCM.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
  |--Date        : 2019-04-20               
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
#ifndef __DRIVER_SCCM_H 
#define __DRIVER_SCCM_H 

#include "stm32f4xx.h"
#pragma anon_unions

//1.0�汾���ݳ������
#define SCCM_Charge_MAX 80.0f
#define UseTo_Charge 60.0f
/*��������*/
typedef union
{
  uint8_t data[8];
  struct
	{
    float chassis_power;    /* ���̹��ʣ���λ��W */
    uint8_t chassis_buff;   /* ���̹��ʻ��� */
    uint8_t cap_usable;    /* ���ݿ��Խ������ */
		int8_t cap_level;      /*�����ٷֱ�*/
  };
} SCCM_ReceiveData_t;

/*��������*/
typedef union{
  uint8_t data[8];
  struct{
    float charge_power;    /* ��繦�ʣ���λ��W ,��Χ 0-80W */
    uint8_t charge_enable; /* ���ʹ�� */
    uint8_t is_cap_output;  /* ʹ�õ��ݹ��� */
  };
}SCCM_SendData_t;

/*�ܽṹ��*/
typedef struct{
  SCCM_ReceiveData_t receiveData;
  SCCM_SendData_t sendData;
  
  uint16_t UpdateFrame;   /* ֡�� */
  uint8_t UpdateFlag;     /* ���±�־ */
  uint8_t OFFLINE_SET;        /* ���߱�� */
}SCCM_t;

extern SCCM_t SCCM;

/*�������ݹ���*/
void SCCM_StateSetting(float UseToCharge, uint8_t ChargeSet, uint8_t CapOutputSet);

#endif	// __DRIVER_SCCM_H
/*-----------------------------------file of end------------------------------*/


