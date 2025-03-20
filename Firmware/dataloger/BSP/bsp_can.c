#include "BSP_CAN.h"
#include "bsp_lcd.h"



void Can2Filter_Config()
{
	CAN_FilterTypeDef Can_FilterStructure;
	
	Can_FilterStructure.FilterBank = 10;
	Can_FilterStructure.FilterMode = CAN_FILTERMODE_IDMASK;
	Can_FilterStructure.FilterScale = CAN_FILTERSCALE_32BIT;
	
	Can_FilterStructure.FilterIdHigh = 0x000 << 5;			//32λ�£��洢Ҫ����ID�ĸ�16λ
    Can_FilterStructure.FilterIdLow = 0x0000;					//32λ�£��洢Ҫ����ID�ĵ�16λ
    Can_FilterStructure.FilterMaskIdHigh = 0x0000;			//����ģʽ�£��洢��������
    Can_FilterStructure.FilterMaskIdLow = 0x0000;
	
	//Can_FilterStructure.FilterIdHigh = ((0x210 | 0x55)<< 5);			//32λ�£��洢Ҫ����ID�ĸ�16λ
    //Can_FilterStructure.FilterIdLow = 0x0000;					//32λ�£��洢Ҫ����ID�ĵ�16λ
    //Can_FilterStructure.FilterMaskIdHigh = (0xFFC << 5);			//����ģʽ�£��洢��������
    //Can_FilterStructure.FilterMaskIdLow = 0 | 0x02;
	
    //Can_FilterStructure.FilterIdHigh = ((0x210 | 0x50 << 3)>>16;			//32λ�£��洢Ҫ����ID�ĸ�16λ
    //Can_FilterStructure.FilterIdLow = ((0x210 | 0x50)<<3)|(0x01<<2)|(0x00<<1);					//32λ�£��洢Ҫ����ID�ĵ�16λ
    //Can_FilterStructure.FilterMaskIdHigh = (0xFFC<<3)>>16;			//����ģʽ�£��洢��������
    //Can_FilterStructure.FilterMaskIdLow = (0xFFC<<3)|(0x01<<2)|(0x01<<1);
	
	Can_FilterStructure.FilterFIFOAssignment = 0;       //��������һ��fifo
	Can_FilterStructure.FilterActivation = ENABLE; //����can
	Can_FilterStructure.SlaveStartFilterBank = 0;
	
	if(HAL_CAN_ConfigFilter(&hcan2,&Can_FilterStructure) != HAL_OK){
		//�����״̬
		//printf("CAN2 Filter Config Fail!\r\n");
		Error_Handler();
	}
	//printf("CAN2 Filter Config Success!\r\n");
	LCD_ShowString(10,40,(unsigned char *)"can1 OK",0xFFFF,0x0000,16,0);
	//�����״̬
}

void Can1Filter_Config()
{
	CAN_FilterTypeDef Can_FilterStructure;
	
	Can_FilterStructure.FilterBank = 10;
	Can_FilterStructure.FilterMode = CAN_FILTERMODE_IDMASK;
	Can_FilterStructure.FilterScale = CAN_FILTERSCALE_32BIT;
	
	Can_FilterStructure.FilterIdHigh = 0x000 << 5;			//32λ�£��洢Ҫ����ID�ĸ�16λ
    Can_FilterStructure.FilterIdLow = 0x0000;					//32λ�£��洢Ҫ����ID�ĵ�16λ
    Can_FilterStructure.FilterMaskIdHigh = 0x0000;			//����ģʽ�£��洢��������
    Can_FilterStructure.FilterMaskIdLow = 0x0000;
	
	//Can_FilterStructure.FilterIdHigh = ((0x210 | 0x55)<< 5);			//32λ�£��洢Ҫ����ID�ĸ�16λ
    //Can_FilterStructure.FilterIdLow = 0x0000;					//32λ�£��洢Ҫ����ID�ĵ�16λ
    //Can_FilterStructure.FilterMaskIdHigh = (0xFFC << 5);			//����ģʽ�£��洢��������
    //Can_FilterStructure.FilterMaskIdLow = 0 | 0x02;
	
    //Can_FilterStructure.FilterIdHigh = ((0x210 | 0x50 << 3)>>16;			//32λ�£��洢Ҫ����ID�ĸ�16λ
    //Can_FilterStructure.FilterIdLow = ((0x210 | 0x50)<<3)|(0x01<<2)|(0x00<<1);					//32λ�£��洢Ҫ����ID�ĵ�16λ
    //Can_FilterStructure.FilterMaskIdHigh = (0xFFC<<3)>>16;			//����ģʽ�£��洢��������
    //Can_FilterStructure.FilterMaskIdLow = (0xFFC<<3)|(0x01<<2)|(0x01<<1);
	
	Can_FilterStructure.FilterFIFOAssignment = 0;       //��������һ��fifo
	Can_FilterStructure.FilterActivation = ENABLE; //����can
	Can_FilterStructure.SlaveStartFilterBank = 0;
	
	if(HAL_CAN_ConfigFilter(&hcan1,&Can_FilterStructure) != HAL_OK){
		//printf("CAN1 Filter Config Fail!\r\n");
		Error_Handler();
	}
	//�����״̬
	//printf("CAN1 Filter Config Success!\r\n");
	LCD_ShowString(10,60,(unsigned char *)"can2 OK",0xFFFF,0x0000,16,0);
}

//can��ʼ��
void canfilter_init(){
	
	Can1Filter_Config();
	Can2Filter_Config();
	
	if(HAL_CAN_Start(&hcan1) != HAL_OK){
		//
		Error_Handler();
	}
	if(HAL_CAN_Start(&hcan2) != HAL_OK){
		//
		Error_Handler();
	}
	//
	
	if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK){
		//
		Error_Handler();
	}
	if(HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK){
		//
		Error_Handler();
	}
}

#ifdef CAN_SendEnable
uint32_t CAN_MailBox0;

//���ͺ���
void CAN2_Send(uint32_t CAN_ID,uint8_t *CAN_Data){
	TxBuff.IDE = CAN_ID_STD;
	TxBuff.StdId = CAN_ID;
	TxBuff.RTR = CAN_RTR_DATA;  //���ô��͵�����֡
	TxBuff.DLC = 8;            //���ݳ���
	
	if(HAL_CAN_AddTxMessage(&hcan2,&TxBuff,CAN_Data,&CAN_MailBox0) != HAL_OK){
		//
		Error_Handler();
	}

	//
}
#endif

#ifdef CAN_ReceiveEnable
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	uint8_t  mdata[8];
	HAL_StatusTypeDef	status;
	
	
	if (hcan == &hcan2) {	
		
		status = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxBuff2, mdata);
		
		if(HAL_OK == status){
			decode(RxBuff2.StdId,mdata);
		}
	}
	
	if (hcan == &hcan1){
				
		status = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxBuff1, mdata);
		
		if(HAL_OK == status){
			decode_power(RxBuff1.ExtId,mdata);
		}
	}
}
	

#endif
