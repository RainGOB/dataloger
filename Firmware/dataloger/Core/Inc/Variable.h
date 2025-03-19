#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include "main.h"
#include "fatfs.h"

#define RXBUFFERSIZE  100    //�������ֽ���
#define RESPONSEWAITING 500

struct RacingCarData{
	//CAN2
	//ID:0X211
	uint8_t FrontSpeed;          //ǰ�ֳ��� ��������Ϊ�ο����� 1Byte
	uint8_t PedalTravel;         //����̤�忪��    1Byte
	uint8_t brakeTravel;         //ɲ��̤�忪��    1Byte
	uint8_t carTravel;           //�����ܶ�����    1Byte
	
	//ID:0X213
	uint8_t gearMode;            //��λ��Ϣ  1Bit
	float angle;
	
	//ID:0x50
	uint8_t sensor_diff;
	float acc_x;
	float acc_y;
	float acc_z;
	float yaw;
	float pitch;
	float roll;
	
	//CAN1
    //0x08C1EF21:  //VCUtoMCU1
	uint16_t l_motor_target_torque;      //����Ŀ��ת��  2Byte
	uint16_t l_motor_target_rpm;		 //����Ŀ��ת�� 2Byte
	uint8_t  l_target_controlmodeorder;  //����Ŀ�����ģʽָ��
	uint8_t  l_gearstage;         		 //����Ť��λ״̬+�����Ӵ���
	float dccur;          		     //ֱ��ĸ�ߵ�ѹ

    //0x08B1EF21:  //VCUtoMCU2
	uint16_t r_motor_target_torque;      //�ҵ��Ŀ��ת��  2Byte
	uint16_t r_motor_target_rpm;		 //�ҵ��Ŀ��ת�� 2Byte
	uint8_t  r_target_controlmodeorder;  //�ҵ��Ŀ�����ģʽָ��
	uint8_t  r_gearstage;         	  	 //�ҵ��Ť��λ״̬+�����Ӵ���
    //uint16_t dccur;     	  		 //�ҵ��ֱ��ĸ�ߵ�ѹ
		
    //0x0CFFC6EF:  //MCU1toVCU1
	uint16_t l_motor_torque;        	 //��ת��  2Byte
	uint16_t l_motor_rpm;		    	 //��ת�� 2Byte
	uint8_t l_controlmodeorder;			 //��������ģʽָ��
	uint8_t lmcuinfo1;					 //����������״̬1
	uint8_t lmcuinfo2;					 //����������״̬2 Ϊ��ʡ��Դ������Ϣ��������֡���ĵ�����
										 
    //0x0CB221EF:  //MCU2toVCU1     	 
	uint16_t r_motor_torque;        	 //��ת��  2Byte
	uint16_t r_motor_rpm;		    	 //��ת�� 2Byte
	uint8_t r_controlmodeorder; 		 //�ҵ������ģʽָ��
	uint8_t rmcuinfo1;					 //�ҵ��������״̬1
	uint8_t rmcuinfo2;					 //�ҵ��������״̬2 Ϊ��ʡ��Դ������Ϣ��������֡���ĵ�����
	
    //0x0CFFC7EF:  //MCU1toVCU2
	int8_t l_mcu_temp;				     //��������¶� 
	int8_t l_motor_temp;				 //�����¶�
	float lmcu_dcvol;          		     //����ֱ��ĸ�ߵ�ѹ
	float lmcu_dccur;          		     //����ֱ��ĸ�ߵ���
	float lmcu_accur;  	     		     //��������������Чֵ
 
    //0x0CB321EF:  //MCU2toVCU2
	int8_t r_mcu_temp;			    	 //�ҿ������¶� 
	int8_t r_motor_temp;				 //�ҵ���¶�
	float rmcu_dcvol;          		     //�ҵ��ֱ��ĸ�ߵ�ѹ
	float rmcu_dccur;          		     //�ҵ��ֱ��ĸ�ߵ���
	float rmcu_accur;          		     //�ҵ������������Чֵ

	//0x186040F3  //�����
	float BatVoltage; 					 //��������ܵ�ѹ
	float BatCurrent;		             //��������ܵ���
	uint8_t BatSoc;                      //�������Soc
	uint8_t BatSoh;                      //�������Soh
	uint8_t BatState;                    //�������״̬
	uint8_t BatAlmLv;					 //�������漶��
	uint8_t Batlife;                     //ͨ��������Ϣ
	

};
extern uint8_t sd_data_send_mes;
extern uint16_t MessageCount;

extern struct RacingCarData racingCarData;

extern uint16_t *lcd_fb;

extern FATFS fs;                       /* FatFs �ļ�ϵͳ���� */
extern FIL file;                       /* �ļ����� */
extern FRESULT f_res;                  /* �ļ�������� */
extern UINT fnum;                      /* �ļ��ɹ���д���� */
extern char FileName[4];
extern char ReadBuffer[100];    /* �������� */
extern char CarDataBuffer[1024];            /* д������ */
extern char buffer[10];
extern _Bool SDWrongFlag;
extern _Bool SDSendStateflg;

#endif
