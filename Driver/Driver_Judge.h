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

#define JudgeFrameHeader        0xA5        //֡ͷ
//#define JudageDataOffset		    0x07		//����ƫ����


//����״̬����
typedef __packed struct
{
	uint8_t game_type : 4;
	uint8_t game_progress : 4;
	uint16_t stage_remain_time;
} ext_game_state_t;

//�����������
typedef __packed struct
{
	uint8_t winner;
} ext_game_result_t;


//�����˴������
typedef __packed struct
{
	uint16_t robot_legion;
} ext_game_robot_survivors_t;


//�����¼�����
/*����ϵͳ�ֲ�7*/
typedef __packed struct
{
	uint32_t event_type;
} ext_event_data_t;

//����վ������ʶ
typedef __packed struct
{
	uint8_t supply_projectile_id;
	uint8_t supply_robot_id;
	uint8_t supply_projectile_step;
	uint8_t supply_projectile_num;
} ext_supply_projectile_action_t;

//����վԤԼ�ӵ�
typedef __packed struct
{
	uint8_t supply_projectile_id;
	uint8_t supply_num;
} ext_supply_projectile_booking_t;

//����������״̬
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

//ʵʱ������������
typedef __packed struct
{
	uint16_t chassis_volt;
	uint16_t chassis_current;
	float chassis_power;
	uint16_t chassis_power_buffer;
	uint16_t shooter_heat0;//17mmǹ������
	uint16_t shooter_heat1;
} ext_power_heat_data_t;

//������λ��
typedef __packed struct
{
	float x;
	float y;
	float z;
	float yaw;
} ext_game_robot_pos_t;

//����������
typedef __packed struct
{
	uint8_t power_rune_buff;
}ext_buff_musk_t;

//���л���������״̬
typedef __packed struct
{
	uint8_t energy_point;
	uint8_t attack_time;
} aerial_robot_energy_t;

//�˺�����
typedef __packed struct
{
	uint8_t armor_id : 4;
	uint8_t hurt_type : 4;
} ext_robot_hurt_t;


//ʵʱ�����Ϣ
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

/*JUDGEMENT����ϵͳ֡�ʼ��*/
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

/*����ϵͳ�Զ���*/
void Judge_Init(void);

/*�������ݱ��Ĵ���*/
void JudgeInfo_Process(uint8_t *JudgeInfo, uint16_t length);

/*�������ݵ��ͻ���*/
void Judge_sendPC(float Userdata1,float Userdata2,float Userdata3);


void *datacpy(void *memTo, const void *memFrom, unsigned int size);

/******************************************************************************************************************************************/
//#pragma anon_unions

//#define JUDGESYSTEM_PACKSIZE 				150u		//����ϵͳ����С
//#define JUDGESYSTEM_FRAMEHEADER    	0xA5        //֡ͷ

///* ����ϵͳCmdID */
//#define JUDGESYS_CMDID_GAMESTATUS     0x0001     /* ����״̬���ݣ�1Hz ���ڷ��� */
//#define JUDGESYS_CMDID_GAMERESULT     0x0002     /* ����������ݣ������������� */
//#define JUDGESYS_CMDID_ROBOTLIVEINFO  0x0003     /* ���������˴�����ݣ�1Hz ���ڷ��� */
//#define JUDGESYS_CMDID_AREAEVENT      0x0101     /* �����¼����ݣ��¼��ı���� */
//#define JUDGESYS_CMDID_SUPPLYACTION   0x0102     /* ���ز���վ������ʶ���ݣ������ı���� */
//#define JUDGESYS_CMDID_SUPPLYREQ      0x0103     /* ���󲹸�վ�������ݣ��ɲ����ӷ��ͣ����� 10Hz����RM �Կ�����δ���ţ� */
//#define JUDGESYS_CMDID_ROBOTSTATUS    0x0201     /* ������״̬���ݣ�10Hz ���ڷ��� */
//#define JUDGESYS_CMDID_POWERHEAT      0x0202     /* ʵʱ�����������ݣ�50Hz ���ڷ��� */
//#define JUDGESYS_CMDID_POSITION       0x0203     /* ������λ�����ݣ�10Hz ���� */
//#define JUDGESYS_CMDID_BUFFER         0x0204     /* �������������ݣ�����״̬�ı���� */
//#define JUDGESYS_CMDID_AERIALENERGY   0x0205     /* ���л���������״̬���ݣ�10Hz ���ڷ��ͣ�ֻ�п��л��������ط��� */
//#define JUDGESYS_CMDID_HURTINFO       0x0206     /* �˺�״̬���ݣ��˺��������� */
//#define JUDGESYS_CMDID_SHOOTINFO      0x0207     /* ʵʱ������ݣ��ӵ�������� */
//#define JUDGESYS_CMDID_ROBOTCOMINFO   0x0301     /* �����˼佻�����ݣ����ͷ��������ͣ����� 10Hz */

//#define JUDGESYS_DATAID_CLIENTUPLOAD  0xD180     /* �ϴ��ͻ���������ʾ������ID */
//#define JUDGESYS_DATAID_ROBOTCOM_MIN  0x0200 		 /* �����˼����ݽ���������ID����Сֵ */
//#define JUDGESYS_DATAID_ROBOTCOM_MAX  0x02FF		 /* �����˼����ݽ���������ID�����ֵ */

///* ���ݻ�������  FrameHeader(5-Byte)+CmdID(2-Byte)+FrameTail(2-Byte, CRC16, ����У��)*/
//#define JUDGESYS_DATALENGTH_BASE               9     

///* ����֡�ĳ��� Data(n-Byte)*/
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

///* ��������֡�ĳ��ȣ�FrameHeader(5-Byte)+CmdID(2-Byte)+Data(n-Byte)+FrameTail(2-Byte, CRC16, ����У��) */
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

///* ����״̬���ݣ�����Ƶ�ʣ�10Hz, CmdID 0x0001 */
//typedef struct{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_GAMESTATUS];
//		struct{
//			uint8_t game_type : 4; 			/* �������� */
//			uint8_t game_progress : 4;	/* ��ǰ�����׶� */
//			uint16_t stage_remain_time; /* ��ǰ�׶�ʣ��ʱ�� */
//		};
//	}data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_GameStatus_t;

///* ����������ݣ���������ʱ���� CmdID 0x0002 */
//typedef struct
//{
//	uint8_t winner; 	/* ������� */
//	uint8_t infoUpdateFlag;
//}JudgeSYS_GameResult_t;

///* �����˴�����ݣ�����Ƶ�ʣ�1Hz, CmdID 0x0002 */
///* ��Ӧ�� bit ��ֵ�� 1 ��������˴���ֵ�� 0 �����������������δ�ϳ� */
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

///* �����¼����ݣ��¼��ı���� CmdID 0x0101 */
//typedef struct
//{
//	union {
//		uint32_t dataBuff;
//		struct
//		{
//			uint8_t apron : 2;		/* ����ͣ��ƺռ��״̬,0δռ�죬1ռ��δͣ����2ռ����ͣ�� */
//			uint8_t recoveryPoint1 : 1; /* ������Ѫ��1,2,3ռ��״̬, 1 Ϊ��ռ�� */
//			uint8_t recoveryPoint2 : 1;
//			uint8_t recoveryPoint3 : 1;
//			uint8_t energyAgency : 2; /* ������������״̬,0δռ��δ���1ռ��δ���2δռ���Ѽ��3ռ���Ѽ��� */
//			uint8_t gateway : 1;			/* �����ؿ�ռ��״̬, 1 Ϊ��ռ�� */
//			uint8_t blockhouse : 1;		/* �����ﱤռ��״̬, 1 Ϊ��ռ�� */
//			uint8_t resource_island : 1; /* ������Դ��ռ��״̬, 1 Ϊ��ռ�� */
//			uint8_t base_status : 2;		 /* ��������״̬,0�޷�����1���ڱ�������2 100%���� */
//			uint8_t ICRA_red_buff : 2;
//			uint8_t ICRA_blue_buff : 2;
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_AeraEvent_t;

///* ����վ������ʶ�������ı���� CmdID 0x0102 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_SUPPLYACTION];
//		struct
//		{
//			uint8_t supply_id;			 		/* ����վ�� ID */
//			uint8_t supply_robot_id; 		/* ���������� ID */
//			uint8_t supply_status;			/* �����ڿ���״̬ */
//			uint8_t supply_bullet_num;	/* �������� */
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_SupplyAction_t;

///* ���󲹸�վ�����ӵ�������Ƶ�ʣ�����10Hz CmdID 0x0103 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_SUPPLYREQ];
//		struct
//		{
//			uint8_t supply_id;				 /* ����վ�� ID */
//			uint8_t supply_robot_id;	 /* ���������� ID */
//			uint8_t supply_bullet_num; /* �������� */
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_SupplyReq_t;

///* ����������״̬������Ƶ��10Hz CmdID 0x0201 */
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

///* ʵʱ���ʺ��������ݣ�����Ƶ��50Hz CmdID 0x0202 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_POWERHEAT];
//		struct
//		{
//			uint16_t chassis_volt; 					/* ���������ѹ ��λ ���� */
//			uint16_t chassis_current; 			/* ����������� ��λ ���� */
//			float chassis_power;						/* ����������� ��λ �� */
//			uint16_t chassis_power_buffer;  /* ���̹��ʻ��� ��λ ���� */
//			uint16_t shooter_heat0;				  /* 17mm ǹ������ */
//			uint16_t shooter_heat1;				  /* 42mm ǹ������ */
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_PowerHeatData_t;

///* ������λ�ú�ǹ�ڳ�����Ϣ������Ƶ��10Hz CmdID 0x0203 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_ROBOTPOS];
//		struct
//		{
//			float x;			/* xλ�����꣬��λ m */
//			float y;			/* yλ�����꣬��λ m */
//			float z;			/* zλ�����꣬��λ m */
//			float yaw; 		/* ǹ�ڳ���Ƕȣ���λ �� */
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_RobotPos_t;

///* ���������棬״̬�ı���� CmdID 0x0204 */
//typedef struct{
//	union {
//		uint8_t dataBuff;
//		struct{
//			uint8_t recovery_buff : 1;			/* ������Ѫ����Ѫ״̬ */
//			uint8_t heat_cooling_buff : 1;	/* ǹ��������ȴ���� */
//			uint8_t defense_buff : 1;				/* �����˷����ӳ� */
//			uint8_t attack_buff : 1;				/* �����˹����ӳ� */
//		};
//	}data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_RobotBuff_t;

///* ���л���������״̬,����Ƶ��10Hz CmdID 0x0205 */
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_AERIALENERGY];
//		struct
//		{
//			uint8_t energy_point; /* ���۵������� */
//			uint8_t attack_time;	/* �ɹ���ʱ�� ��λ s */
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_AerialEnergy_t;

///* �˺�״̬���˺��������� CmdID 0x0206 */
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

////ʵʱ������ݣ�������� CmdID 0x0207 */
//typedef struct{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_SHOOTINFO];
//		struct{
//			uint8_t bulletType;		/* �������� 1��17mm ���� 2��42mm ���� */
//			uint8_t bulletFreq;		/* ������Ƶ����λ��Hz */
//			float bulletSpeed;		/* �������٣���λ����ÿ�� */
//		};
//	}data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_ShootInfo_t;


////�������Զ������ݣ�������ʾ�ڲ������棬��Ƶ 10Hz CmdID 0x0301
//typedef struct{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_CLIENTUPLOADINFO];
//		struct{
//			uint16_t data_cmd_id; /* ���ݶε����� ID  */
//			uint16_t send_ID;			/* �����ߵ� ID  */
//			uint16_t receiver_ID; /* �����ߵ� ID  */
//			float data1;
//			float data2;
//			float data3;
//			uint8_t mask;
//		};
//	}data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_ClientUploadInfo_t;

////�������Զ������ݣ����ڻ����˼�����ͨ�ţ���Ƶ 10Hz CmdID 0x0301
//typedef struct
//{
//	union {
//		uint8_t dataBuff[JUDGESYS_DATALENGTH_ROBOTCOMINFO];
//		struct
//		{
//			uint16_t data_cmd_id; /* ���ݶε����� ID  */
//			uint16_t send_ID;			/* �����ߵ� ID  */
//			uint16_t receiver_ID; /* �����ߵ� ID  */
//			uint8_t data[113];
//		};
//	} data;
//	uint8_t infoUpdateFlag;
//}JudgeSYS_RobotComInfo_t;

////����ϵͳ����
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
//	uint16_t UpdateFrame; //֡��
//	uint8_t OFFLINE_SET;		//�豸���߱�־
//}JudgeSYS_t;




//extern JudgeSYS_t JudgeSYS;

//void JudgeSystem_Init(void);
//void Judge_getInfo(uint16_t dataLength);
//void Judge_sendInfo(void);



#endif /* __JUDGESYSTEM_H */

