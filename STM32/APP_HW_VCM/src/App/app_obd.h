/**
  ******************************************************************************
  * SVN revision information:
  * @file    $URL: https://icar-firmware.googlecode.com/svn/app_v07/src_comm/App/app_obd.h $ 
  * @version $Rev: 279 $
  * @author  $Author: cn0086.info@gmail.com $
  * @date    $Date: 2012-10-18 13:02:30 +0800 (周四, 2012-10-18) $
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_OBD_H
#define __APP_OBD_H

/* Includes ------------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#ifdef DEBUG_OBD
	#define debug_obd(x, args...)  prompt(x, ##args);
#else
	#define debug_obd(x, args...)  ;
#endif

#define	prompt(x, args...)	printf("[%d,%02d%%]> ",OSTime/100,OSCPUUsage);printf(x,	##args);

#define STD_RCV_CAN_ID			0x07E8 		//0x07E8
#define EXT_RCV_CAN_ID			0x18DAF110	//0x18DAF111 ?

#define OBD_MIN_PID 			1
#define OBD_MAX_PID		 		112
#define	OBD_SUPPORT_PID_CNT		16
#define	OBD_BUF_SIZE			128

//popular PID:
#define	OBD_PID_ENGINE_RPM		0x0C		//0 ~ 16,383.75,rpm,((A*256)+B)/4

//OBD error code define
#define OBD_ERR_NONE 			0	//OK, no err
#define OBD_ERR_UNSUPPORT_PID 	1	//unsupport PID
#define OBD_ERR_REC_DAT_TIMEOUT	2	//Receive data timeout
#define OBD_ERR_REC_UNKNOW_DAT	3	//Receive unknow data

//BKP_DR2, OBD Flag:	15~12:KWP_TYPEDEF
//						11~8:CAN2_TYPEDEF
//						7~4: CAN1_TYPEDEF
//						3~0: OBD_TYPEDEF 
//BKP_DR3, can_snd_id index, check app_obd.c

#define obd_read_type						BKP_ReadBackupRegister(BKP_DR2)&0x0F
#define obd_can1_type						(BKP_ReadBackupRegister(BKP_DR2)&0xF0)>>4
#define obd_read_canid_idx					BKP_ReadBackupRegister(BKP_DR3)

/* Exported types ------------------------------------------------------------*/
//						3~0: OBD_TYPEDEF
#define OBD_TYPE_NO_DFN						0	//OBD type no define
#define OBD_TYPE_CAN1						1	//OBD type Only CAN1, Pin 6&14
#define OBD_TYPE_CAN2						2	//OBD type Only CAN2, Pin 3&11
#define OBD_TYPE_CAN1_2						3	//OBD type CAN1 + CAN2
#define OBD_TYPE_KWP						4	//OBD type KWP

//						7~4: CAN1_TYPEDEF
//第1路CAN, CAN1: OBD-II, Pins 6&14
#define CAN1_TYPE_NO_DEFINE					0	//
#define CAN1_TYPE_STD_250					1	//CAN bus 250 Kbps, standard, ID:11 bits
#define CAN1_TYPE_EXT_250					2	//CAN bus 250 Kbps, extend, ID: 29 bits
#define CAN1_TYPE_STD_500					3	//CAN bus 500 Kbps, standard, ID:11 bits
#define CAN1_TYPE_EXT_500					4	//CAN bus 500 Kbps, extend, ID: 29 bits

//						11~8:CAN2_TYPEDEF
//第2路CAN, CAN2: OBD-II, Pins 3&11
#define CAN2_TYPE_NO_DFN					0	//
#define CAN2_TYPE_STD_250					1	//CAN bus 250 Kbps, standard, ID:11 bits
#define CAN2_TYPE_EXT_250					2	//CAN bus 250 Kbps, extend, ID: 29 bits
#define CAN2_TYPE_STD_500					3	//CAN bus 500 Kbps, standard, ID:11 bits
#define CAN2_TYPE_EXT_500					4	//CAN bus 500 Kbps, extend, ID: 29 bits

//BKP_DR2, OBD Flag:	15~12:KWP_TYPEDEF
//多路KWP: OBD-II, Pin7, 8, 9, 12, 13
#define KWP_TYPE_NO_DFN						0	//
#define KWP_TYPE_KWP_7						1	//
#define KWP_TYPE_KWP_8						2	//
#define KWP_TYPE_KWP_9						3	//
#define KWP_TYPE_KWP_12						4	//
#define KWP_TYPE_KWP_13						5	//

typedef enum 
{
	CAN_1 = 0, //CAN1: OBD-II, Pins 6&14
	CAN_2 = 1, //CAN2, Pin 3&11
	CAN_1_2 = 3 //CAN1&2
} can_pin_typedef;

typedef enum 
{
	CAN_250K = 0, //250 Kbps
	CAN_500K = 1  //500 Kbps
} can_speed_typedef;

typedef enum 
{
	CAN_STD = 0, //standard, ID:11 bits
	CAN_EXT = 1  //extend, ID: 29 bits
} can_std_typedef;

typedef enum 
{
	DAT_FRAME = 0, //Data frame
	RMO_FRAME = 1  //Remote frame
} frame_typedef;

typedef enum 
{
	NO_CMD		= 0 , //no command
	READ_PID	= 1 , //read Parameter ID
	SPEED		= 2   //engine speed
} obd_cmd_typedef;

struct OBD_DAT {
	u8 can_tx_cnt;//can tx count
	obd_cmd_typedef cmd;
	u8 rx_buf[OBD_BUF_SIZE];
	u8 support_pid[OBD_SUPPORT_PID_CNT];
	u8 pid;
	bool update_support_table;
};


/* Exported constants --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

void  app_task_obd (void *p_arg);
bool obd_check_support_pid( u16 );
#endif /* __APP_OBD_H */
