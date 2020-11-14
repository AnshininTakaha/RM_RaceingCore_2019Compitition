#ifndef __JUDGESYSTEM_H
#define __JUDGESYSTEM_H

#include "stm32f4xx.h"
#include "string.h"
#pragma anon_unions

#define JudgeBufferLength       200	//204

#define JudgeFrameLength_001      12
#define JudgeFrameLength_002      10
#define JudgeFrameLength_003      11
#define JudgeFrameLength_101      13
#define JudgeFrameLength_102      13
#define JudgeFrameLength_103      12
#define JudgeFrameLength_201      24
#define JudgeFrameLength_202      23
#define JudgeFrameLength_203    	25
#define JudgeFrameLength_204    	10
#define JudgeFrameLength_205    	12
#define JudgeFrameLength_206    	10
#define JudgeFrameLength_207    	15

#define JudgeFrameLength_301    	119

#define JudgeFrameHeader        0xA5        //帧头
//#define JudageDataOffset		    0x07		//数据偏移量


//比赛状态数据
typedef __packed struct
{
	uint8_t game_type : 4;
	uint8_t game_progress : 4;
	uint16_t stage_remain_time;
} ext_game_state_t;

//比赛结果数据
typedef __packed struct
{
	uint8_t winner;
} ext_game_result_t;


//机器人存活数据
typedef __packed struct
{
	uint16_t robot_legion;
} ext_game_robot_survivors_t;


//场地事件数据
/*裁判系统手册7*/
typedef __packed struct
{
	uint32_t event_type;
} ext_event_data_t;

//补给站动作标识
typedef __packed struct
{
	uint8_t supply_projectile_id;
	uint8_t supply_robot_id;
	uint8_t supply_projectile_step;
	uint8_t supply_projectile_num;
} ext_supply_projectile_action_t;

//补给站预约子弹
typedef __packed struct
{
	uint8_t supply_projectile_id;
	uint8_t supply_num;
} ext_supply_projectile_booking_t;

//比赛机器人状态
typedef __packed struct
{
	uint8_t robot_id;
	uint8_t robot_level;
	uint16_t remain_HP;
	uint16_t max_HP;
	uint16_t shooter_heat0_cooling_rate;
	uint16_t shooter_heat0_cooling_limit;
	uint16_t shooter_heat1_cooling_rate;
	uint16_t shooter_heat1_cooling_limit;
	uint8_t mains_power_gimbal_output : 1;
	uint8_t mains_power_chassis_output : 1;
	uint8_t mains_power_shooter_output : 1;
} ext_game_robot_state_t;

//实时功率热量数据
typedef __packed struct
{
	uint16_t chassis_volt;
	uint16_t chassis_current;
	float chassis_power;
	uint16_t chassis_power_buffer;
	uint16_t shooter_heat0;//17mm枪口热量
	uint16_t shooter_heat1;
} ext_power_heat_data_t;

//机器人位置
typedef __packed struct
{
	float x;
	float y;
	float z;
	float yaw;
} ext_game_robot_pos_t;

//机器人增益
typedef __packed struct
{
	uint8_t power_rune_buff;
}ext_buff_musk_t;

//空中机器人能量状态
typedef __packed struct
{
	uint8_t energy_point;
	uint8_t attack_time;
} aerial_robot_energy_t;

//伤害数据
typedef __packed struct
{
	uint8_t armor_id : 4;
	uint8_t hurt_type : 4;
} ext_robot_hurt_t;


//实时射击信息
typedef __packed struct
{
	uint8_t bullet_type;
	uint8_t bullet_freq;
	float bullet_speed;
} ext_shoot_data_t;

typedef struct
{
		union
		{
			 uint8_t databuff[13];
				__packed struct
				{
						float data1;
						float data2;
						float data3;
						uint8_t mask;
				};
		}data;

}extShowData_t;




typedef enum 
{
	Power_Normal,
	OverPower_Little,
	OverPower_Many,
	OverPower_OverMany,
	OverPower_Dying,
	OverPower_Die,
}ChassPowerStatus_e;	

typedef union
{
		float data;
		uint8_t TurnToFloat[4];
		
}CustomsData_t;

/*JUDGEMENT裁判系统帧率检测*/
typedef struct
{
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}Judgement_t;

extern Judgement_t Judgement_Check;

extern ChassPowerStatus_e ChassPowerStatus;
extern ext_power_heat_data_t ext_power_heat_data;	
extern ext_shoot_data_t ext_shoot_data;	
extern ext_buff_musk_t ext_buff_musk;
extern ext_game_robot_state_t ext_game_robot_state;
extern ext_supply_projectile_action_t ext_supply_projectile_action;	

unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned char ucCRC8);
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
void Append_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength,uint16_t wCRC);
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
void Append_CRC16_Check_Sum(uint8_t * pchMessage,uint32_t dwLength);

/*裁判系统自定义*/
void Judge_Init(void);

/*裁判数据报文处理*/
void JudgeInfo_Process(uint8_t *JudgeInfo, uint16_t length);

/*发送数据到客户端*/
void Judge_sendPC(float Userdata1,float Userdata2,float Userdata3);


void *datacpy(void *memTo, const void *memFrom, unsigned int size);

/******************************************************************************************************************************************/
//#pragma anon_unions

//#define JUDGESYSTEM_PACKSIZE 				150u		//裁判系统包大小
//#define JUDGESYSTEM_FRAMEHEADER    	0xA5        //帧头

///* 裁判系统CmdID */
//#define JUDGESYS_CMDID_GAMESTATUS     0x0001     /* 比赛状态数据，1Hz 周期发送 */
//#define JUDGESYS_CMDID_GAMERESULT     0x0002     /* 比赛结果数据，比赛结束后发送 */
//#define JUDGESYS_CMDID_ROBOTLIVEINFO  0x0003     /* 比赛机器人存活数据，1Hz 周期发送 */
//#define JUDGESYS_CMDID_AREAEVENT      0x0101     /* 场地事件数据，事件改变后发送 */
//#define JUDGESYS_CMDID_SUPPLYACTION   0x0102     /* 场地补给站动作标识数据，动作改变后发送 */
//#define JUDGESYS_CMDID_SUPPLYREQ      0x0103     /* 请求补给站补弹数据，由参赛队发送，上限 10Hz。（RM 对抗赛尚未开放） */
//#define JUDGESYS_CMDID_ROBOTSTATUS    0x0201     /* 机器人状态数据，10Hz 周期发送 */
//#define JUDGESYS_CMDID_POWERHEAT      0x0202     /* 实时功率热量数据，50Hz 周期发送 */
//#define JUDGESYS_CMDID_POSITION       0x0203     /* 机器人位置数据，10Hz 发送 */
//#define JUDGESYS_CMDID_BUFFER         0x0204     /* 机器人增益数据，增益状态改变后发送 */
//#define JUDGESYS_CMDID_AERIALENERGY   0x0205     /* 空中机器人能量状态数据，10Hz 周期发送，只有空中机器人主控发送 */
//#define JUDGESYS_CMDID_HURTINFO       0x0206     /* 伤害状态数据，伤害发生后发送 */
//#define JUDGESYS_CMDID_SHOOTINFO      0x0207     /* 实时射击数据，子弹发射后发送 */
//#define JUDGESYS_CMDID_ROBOTCOMINFO   0x0301     /* 机器人间交互数据，发送方触发发送，上限 10Hz */

//#define JUDGESYS_DATAID_CLIENTUPLOAD  0xD180     /* 上传客户端数据显示的内容ID */
//#define JUDGESYS_DATAID_ROBOTCOM_MIN  0x0200 		 /* 机器人间数据交换的内容ID，最小值 */
//#define JUDGESYS_DATAID_ROBOTCOM_MAX  0x02FF		 /* 机器人间数据交换的内容ID，最大值 */

///* 数据基本长度  FrameHeader(5-Byte)+CmdID(2-Byte)+FrameTail(2-Byte, CRC16, 整包校验)*/
//#define JUDGESYS_DATALENGTH_BASE               9     

///* 数据帧的长度 Data(n-Byte)*/
//#define JUDGESYS_DATALENGTH_GAMESTATUS    	   3
//#define JUDGESYS_DATALENGTH_GAMERESULT     	   1
//#define JUDGESYS_DATALENGTH_ROBOTLIVEINFO 	   2
//#define JUDGESYS_DATALENGTH_AREAEVENT     	 	 4
//#define JUDGESYS_DATALENGTH_SUPPLYACTION  		 4
//#define JUDGESYS_DATALENGTH_SUPPLYREQ      	   3
//#define JUDGESYS_DATALENGTH_ROBOTSTATUS        15
//#define JUDGESYS_DATALENGTH_POWERHEAT     	   14
//#define JUDGESYS_DATALENGTH_ROBOTPOS 					 16
//#define JUDGESYS_DATALENGTH_BUFF         			 1
//#define JUDGESYS_DATALENGTH_AERIALENERGY  		 3
//#define JUDGESYS_DATALENGTH_HURTINFO     		   1
//#define JUDGESYS_DATALENGTH_SHOOTINFO    		   6
//#define JUDGESYS_DATALENGTH_CLIENTUPLOADINFO	 19
//#define JUDGESYS_DATALENGTH_ROBOTCOMINFO  	 	 119

///* 整个数据帧的长度，FrameHeader(5-Byte)+CmdID(2-Byte)+Data(n-Byte)+FrameTail(2-Byte, CRC16, 整包校验) */
//#define JUDGESYS_FULLDATALENGTH_GAMESTATUS		 	 (JUDGESYS_DATALENGTH_GAMESTATUS + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_GAMERESULT 			 (JUDGESYS_DATALENGTH_GAMERESULT + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_ROBOTLIVEINFO 	 (JUDGESYS_DATALENGTH_ROBOTLIVEINFO + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_AREAEVENT 			 (JUDGESYS_DATALENGTH_AREAEVENT + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_SUPPLYACTION 		 (JUDGESYS_DATALENGTH_SUPPLYACTION + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_SUPPLYREQ 			 (JUDGESYS_DATALENGTH_SUPPLYREQ + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_ROBOTSTATUS 		 (JUDGESYS_DATALENGTH_ROBOTSTATUS + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_POWERHEAT 			 (JUDGESYS_DATALENGTH_POWERHEAT + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_ROBOTPOS 				 (JUDGESYS_DATALENGTH_POSITION + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_BUFF 						 (JUDGESYS_DATALENGTH_BUFFER + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_AERIALENERGY 		 (JUDGESYS_DATALENGTH_AERIALENERGY + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_HURTINFO 				 (JUDGESYS_DATALENGTH_HURTINFO + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_SHOOTINFO			   (JUDGESYS_DATALENGTH_SHOOTINFO + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_CLIENTUPLOADINFO (JUDGESYS_DATALENGTH_CLIENTUPLOADINFO + JUDGESYS_DATALENGTH_BASE)
//#define JUDGESYS_FULLDATALENGTH_ROBOTCOMINFO  	 (JUDGESYS_DATALENGTH_ROBOTCOMINFO + JUDGESYS_DATALENGTH_BASE)

///* 比赛状态数据，发送频率：10Hz, CmdID 0x0001 */
//typedef struct{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_GAMESTATUS];
//		struct{
//			uint8_t game_type : 4; 			/* 比赛类型 */
//			uint8_t game_progress : 4;	/* 当前比赛阶段 */
//			uint16_t stage_remain_time; /* 当前阶段剩余时间 */
//		};
//	}data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_GameStatus_t;

///* 比赛结果数据，比赛结束时推送 CmdID 0x0002 */
//typedef struct
//{
//	uint8_t winner; 	/* 比赛结果 */
//	uint8_t infoUpdateFlag;
//}JudgeSYS_GameResult_t;

///* 机器人存活数据，发送频率：1Hz, CmdID 0x0002 */
///* 对应的 bit 数值置 1 代表机器人存活，数值置 0 代表机器人死亡或者未上场 */
//typedef struct
//{
//	union {
//		uint16_t dataBuff;
//		struct{
//			uint8_t redHero : 1;
//			uint8_t redEngineer : 1;
//			uint8_t redInfantry1 : 1;
//			uint8_t redInfantry2 : 1;
//			uint8_t redInfantry3 : 1;
//			uint8_t redAerial : 1;
//			uint8_t redSentry : 1;
//			uint8_t reserve7 : 1;
//			uint8_t blueHero : 1;
//			uint8_t blueEngineer : 1;
//			uint8_t blueInfantry1 : 1;
//			uint8_t blueInfantry2 : 1;
//			uint8_t blueInfantry3 : 1;
//			uint8_t blueAerial : 1;
//			uint8_t blueSentry : 1;
//			uint8_t reserve15 : 1;
//		};
//	}data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_RobotLiveInfo_t;

///* 场地事件数据，事件改变后发送 CmdID 0x0101 */
//typedef struct
//{
//	union {
//		uint32_t dataBuff;
//		struct
//		{
//			uint8_t apron : 2;		/* 己方停机坪占领状态,0未占领，1占领未停浆，2占领已停浆 */
//			uint8_t recoveryPoint1 : 1; /* 己方补血点1,2,3占领状态, 1 为已占领 */
//			uint8_t recoveryPoint2 : 1;
//			uint8_t recoveryPoint3 : 1;
//			uint8_t energyAgency : 2; /* 己方能量机关状态,0未占领未激活，1占领未激活，2未占领已激活，3占领已激活 */
//			uint8_t gateway : 1;			/* 己方关口占领状态, 1 为已占领 */
//			uint8_t blockhouse : 1;		/* 己方碉堡占领状态, 1 为已占领 */
//			uint8_t resource_island : 1; /* 己方资源岛占领状态, 1 为已占领 */
//			uint8_t base_status : 2;		 /* 己方基地状态,0无防御，1有哨兵防御，2 100%防御 */
//			uint8_t ICRA_red_buff : 2;
//			uint8_t ICRA_blue_buff : 2;
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_AeraEvent_t;

///* 补给站动作标识，动作改变后发送 CmdID 0x0102 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_SUPPLYACTION];
//		struct
//		{
//			uint8_t supply_id;			 		/* 补给站口 ID */
//			uint8_t supply_robot_id; 		/* 补弹机器人 ID */
//			uint8_t supply_status;			/* 出弹口开闭状态 */
//			uint8_t supply_bullet_num;	/* 补弹数量 */
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_SupplyAction_t;

///* 请求补给站补弹子弹，发送频率：上限10Hz CmdID 0x0103 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_SUPPLYREQ];
//		struct
//		{
//			uint8_t supply_id;				 /* 补给站口 ID */
//			uint8_t supply_robot_id;	 /* 补弹机器人 ID */
//			uint8_t supply_bullet_num; /* 补弹数量 */
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_SupplyReq_t;

///* 比赛机器人状态，发送频率10Hz CmdID 0x0201 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_ROBOTSTATUS];
//		struct
//		{
//			uint8_t robot_id;
//			uint8_t robot_level;
//			uint16_t remain_HP;
//			uint16_t max_HP;
//			uint16_t shooter_heat0_cooling_rate;
//			uint16_t shooter_heat0_cooling_limit;
//			uint16_t shooter_heat1_cooling_rate;
//			uint16_t shooter_heat1_cooling_limit;
//			uint8_t mains_power_gimbal_output : 1;
//			uint8_t mains_power_chassis_output : 1;
//			uint8_t mains_power_shooter_output : 1;
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_RobotStatus_t;

///* 实时功率和热量数据，发送频率50Hz CmdID 0x0202 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_POWERHEAT];
//		struct
//		{
//			uint16_t chassis_volt; 					/* 底盘输出电压 单位 毫伏 */
//			uint16_t chassis_current; 			/* 底盘输出电流 单位 毫安 */
//			float chassis_power;						/* 底盘输出功率 单位 瓦 */
//			uint16_t chassis_power_buffer;  /* 底盘功率缓冲 单位 焦耳 */
//			uint16_t shooter_heat0;				  /* 17mm 枪口热量 */
//			uint16_t shooter_heat1;				  /* 42mm 枪口热量 */
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_PowerHeatData_t;

///* 机器人位置和枪口朝向信息，发送频率10Hz CmdID 0x0203 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_ROBOTPOS];
//		struct
//		{
//			float x;			/* x位置坐标，单位 m */
//			float y;			/* y位置坐标，单位 m */
//			float z;			/* z位置坐标，单位 m */
//			float yaw; 		/* 枪口朝向角度，单位 度 */
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_RobotPos_t;

///* 机器人增益，状态改变后发送 CmdID 0x0204 */
//typedef struct{
//	union {
//		uint8_t dataBuff;
//		struct{
//			uint8_t recovery_buff : 1;			/* 机器人血量补血状态 */
//			uint8_t heat_cooling_buff : 1;	/* 枪口热量冷却加速 */
//			uint8_t defense_buff : 1;				/* 机器人防御加成 */
//			uint8_t attack_buff : 1;				/* 机器人攻击加成 */
//		};
//	}data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_RobotBuff_t;

///* 空中机器人能量状态,发送频率10Hz CmdID 0x0205 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_AERIALENERGY];
//		struct
//		{
//			uint8_t energy_point; /* 积累的能量点 */
//			uint8_t attack_time;	/* 可攻击时间 单位 s */
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_AerialEnergy_t;

///* 伤害状态，伤害发生后发送 CmdID 0x0206 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff;
//	  struct
//		{
//			uint8_t armor_id : 4;
//			uint8_t hurt_type : 4;
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//} JudgeSYS_HurtInfo_t;

////实时射击数据，射击后发送 CmdID 0x0207 */
//typedef struct{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_SHOOTINFO];
//		struct{
//			uint8_t bulletType;		/* 弹丸类型 1：17mm 弹丸 2：42mm 弹丸 */
//			uint8_t bulletFreq;		/* 弹丸射频，单位：Hz */
//			float bulletSpeed;		/* 弹丸射速，单位：米每秒 */
//		};
//	}data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_ShootInfo_t;


////参赛队自定义数据，用于显示在操作界面，限频 10Hz CmdID 0x0301
//typedef struct{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_CLIENTUPLOADINFO];
//		struct{
//			uint16_t data_cmd_id; /* 数据段的内容 ID  */
//			uint16_t send_ID;			/* 发送者的 ID  */
//			uint16_t receiver_ID; /* 接收者的 ID  */
//			float data1;
//			float data2;
//			float data3;
//			uint8_t mask;
//		};
//	}data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_ClientUploadInfo_t;

////参赛队自定义数据，用于机器人间数据通信，限频 10Hz CmdID 0x0301
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_ROBOTCOMINFO];
//		struct
//		{
//			uint16_t data_cmd_id; /* 数据段的内容 ID  */
//			uint16_t send_ID;			/* 发送者的 ID  */
//			uint16_t receiver_ID; /* 接收者的 ID  */
//			uint8_t data[113];
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_RobotComInfo_t;

////裁判系统数据
//typedef struct{
//	JudgeSYS_GameStatus_t GameStatus;
//	JudgeSYS_GameResult_t GameResult;
//	JudgeSYS_RobotLiveInfo_t RobotLiveInfo;
//	JudgeSYS_AeraEvent_t AeraEvent;
//	JudgeSYS_SupplyAction_t SupplyAction;
//	JudgeSYS_SupplyReq_t SupplyReq;
//	JudgeSYS_RobotStatus_t RobotStatus;
//	JudgeSYS_PowerHeatData_t PowerHeatData;
//	JudgeSYS_RobotPos_t RobotPos;
//	JudgeSYS_RobotBuff_t RobotBuff;
//	JudgeSYS_AerialEnergy_t AerialEnergy;
//	JudgeSYS_HurtInfo_t HurtInfo;
//	JudgeSYS_ShootInfo_t ShootInfo;
//	JudgeSYS_ClientUploadInfo_t ClientUploadInfo;
//	JudgeSYS_RobotComInfo_t RobotComInfo_RX;
//  JudgeSYS_RobotComInfo_t RobotComInfo_TX;
//	uint16_t UpdateFrame; //帧率
//	uint8_t OFFLINE_SET;		//设备离线标志
//}JudgeSYS_t;




//extern JudgeSYS_t JudgeSYS;

//void JudgeSystem_Init(void);
//void Judge_getInfo(uint16_t dataLength);
//void Judge_sendInfo(void);



#endif /* __JUDGESYSTEM_H */

