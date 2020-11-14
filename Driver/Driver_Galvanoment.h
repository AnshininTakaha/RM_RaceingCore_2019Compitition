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
  |--FileName    : Driver_Galvanoment.h                                                
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
#ifndef __DRIVER_GALVANOMENT_H 
#define __DRIVER_GALVANOMENT_H 

#pragma anon_unions


#include "RTOSinclude.h"
#include  "stm32f4xx.h"

typedef struct 
{
  union
  {
    uint8_t Galvanometer_Buff[8];
    struct 
    {
      /*���ʻ�����ֵ*/
      float chassisVolt;
			float chassisCurrent;
			float chassisPower;
			float chassisPowerBuffer;

      /*���幦��*/
      float ExpectPowerTiring;
      /*��һ�ι�����ֵ*/
      float LastchassisPowerBuffer;
			float LLastchassisPowerBuffer;
      /*����б��*/
      float Growthslope;
      
      /*Ԥ�⹦��*/
      float ForecastPower;

      /*�����ʱ�־λ*/
      float OverPowerState;

      /*׼�������ʱ�־λ*/
      float PreOverPowerState;

    };
  }data;
			/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
				uint8_t UpdateFlag;
				uint16_t UpdateFrame;
				uint8_t OFFLINE_SET;
}Galvanometer_t;

/*�����ƵĻ�����ֵ������*/
extern Galvanometer_t Galvanometer;

/*�������㷨*/
void Galvanometer_Calculation(Galvanometer_t* Galvanometer);

#endif	// __DRIVER_GALVANOMENT_H
/*-----------------------------------file of end------------------------------*/


