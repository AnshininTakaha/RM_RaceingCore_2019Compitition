/**************************************************************************
作者：平衡小车之家 
淘宝店铺：http://shop114407458.taobao.com/
**************************************************************************/

#ifndef __DATA_PRTOCOL_H
#define __DATA_PRTOCOL_H
 
#include "stm32f4xx.h"

extern unsigned char DataScope_OutPut_Buffer[42];	   //待发送帧数据缓存区


void DataScope_Get_Channel_Data(float Data,unsigned char Channel);    // 写通道数据至 待发送帧数据缓存区
void DataScopeTask(void *Parameters);
unsigned char DataScope_Data_Generate(unsigned char Channel_Number);  // 发送帧数据生成函数 
void usart2_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw);
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz);
void usart2_niming_report(u8 fun,u8*data,u8 len);
void usart2_send_char(u8 c);
 
#endif 



