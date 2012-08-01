/**
  ******************************************************************************
  * SVN revision information:
  * @file    $URL$ 
  * @version $Rev$
  * @author  $Author$
  * @date    $Date$
  * @brief   This file contains all necessary *.h and global define.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <os_cfg.h>
#include <ucos_ii.h>
#include <cpu.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f10x.h"
#include "app_cfg.h"
#include "app_taskmanager.h"
#include "app_gsm.h"
#include "app_obd.h"
#include "drv_uart.h"
#include "drv_gpio.h"
#include "drv_adc.h"
#include "drv_rtc.h"
#include "drv_can.h"
#include "drv_iwdg.h"
#include "drv_mg323.h"
#include "drv_flash.h"

/* Exported types ------------------------------------------------------------*/
//For taskmanger

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define DEBUG_GSM

#define AT_CMD_LENGTH			64 //for GSM command, must < RX_BUF_SIZE in drv_uart.h
#define MAX_ONLINE_TRY			25 //if ( my_icar.mg323.try_online_cnt_cnt > MAX_ONLINE_TRY )
#define MAX_WARN_MSG			3  //Warn message, uint32
#define MIN_GSM_SIGNAL			8  //Min. GSM Signal require

#define MAX_PROG_TRY			16 //Max. program flash retry

#define AT_TIMEOUT				1*OS_TICKS_PER_SEC // 1 sec

#define VOICE_RESPOND_TIMEOUT	1*1*60*OS_TICKS_PER_SEC //60 secs
#define TCP_RESPOND_TIMEOUT		1*1*30*OS_TICKS_PER_SEC //30 secs
#define TCP_SEND_PERIOD			1*1*30*OS_TICKS_PER_SEC //30 secs
#define TCP_CHECK_PERIOD		1*1*30*OS_TICKS_PER_SEC //30 secs
#define CLEAN_QUEUE_PERIOD		1*2*60*OS_TICKS_PER_SEC //2  mins

#define RE_DIAL_PERIOD			1*2*60*OS_TICKS_PER_SEC //2  mins

//#define RTC_UPDATE_PERIOD		1*60*60 //1 Hour
#define RTC_UPDATE_PERIOD		1*2*60 //2 mins, use RTC time, +1 per second in RTC

//For GSM <==> Server protocol
#define GSM_HEAD				0xC9
#define GSM_ASK_IST				0x3F //'?', Ask instruction from server
#define GSM_CMD_ERROR			0x45 //'E', upload error log to server
#define GSM_CMD_RECORD			0x52 //'R', record gsm/adc data
#define GSM_CMD_SN				0x53 //'S', upload SN
#define GSM_CMD_TIME			0x54 //'T', time
#define GSM_CMD_UPGRADE			0x55 //'U', Upgrade firmware
#define GSM_CMD_UPDATE			0x75 //'u', Update parameter
#define GSM_CMD_WARN			0x57 //'W', warn msg, report to server

#define	prompt(x, args...)	printf("[%d,%02d%%]> ",OSTime/100,OSCPUUsage);printf(x,	##args);

/* Exported functions ------------------------------------------------------- */

/* Exported types ------------------------------------------------------------*/
struct ICAR_DEVICE {
	unsigned char hw_rev ;//iCar hardware revision, up to 255
	u16 fw_rev ;//iCar firmware revision, up to 9999
	unsigned char debug ;//debug flag
	unsigned int login_timer;
	unsigned int err_log_send_timer;
	unsigned char *sn ;//serial number
	unsigned char need_sn;//server need SN

	unsigned int warn_msg[MAX_WARN_MSG];//file name(1 Byte), msg(1 Byte), line(2 B)
	
	struct RTC_STATUS stm32_rtc;
	struct ADC_STATUS stm32_adc;

	struct UART_TX stm32_u1_tx;
	struct UART_RX stm32_u1_rx;

	struct UART_TX stm32_u2_tx;
	struct UART_RX stm32_u2_rx;

	struct UART_TX stm32_u3_tx;
	struct UART_RX stm32_u3_rx;

	struct GSM_STATUS mg323;

	struct FIRMWARE_UPGRADE upgrade;
	struct PARA_UPDATE update;
	struct PARA_METERS para;
};

//File name define, for warn msg report
#define F_MAIN				01	//main.c
#define F_APP_TASKMANAGER	02	//app_taskmanager.c
#define F_APP_GSM			03	//app_gsm.c


#endif /* __MAIN_H */
