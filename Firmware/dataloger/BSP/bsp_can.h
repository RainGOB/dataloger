#ifndef _BSP_CAN_H_
#define _BSP_CAN_H_

#include "main.h"
#include "can.h"
#include "app_can.h"

//#define CAN_SendEnabel 
#define CAN_ReceiveEnable 
//#define CAN_SendEnable

static CAN_TxHeaderTypeDef TxBuff;    //can发送消息的消息头
static CAN_RxHeaderTypeDef RxBuff1;    //can接收消息的消息头
static CAN_RxHeaderTypeDef RxBuff2;


void Can2Filter_Config(void);
void Can1Filter_Config(void);
void canfilter_init(void);

	#ifdef CAN_SendEnable
		void CAN2_Send(uint32_t CAN_ID,uint8_t *CAN_Data);
	#endif
	#ifdef CAN_ReceiveEnable
		void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
	#endif

#endif
