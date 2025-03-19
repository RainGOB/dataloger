#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include "main.h"
#include "fatfs.h"

#define RXBUFFERSIZE  100    //最大接收字节数
#define RESPONSEWAITING 500

struct RacingCarData{
	//CAN2
	//ID:0X211
	uint8_t FrontSpeed;          //前轮车速 在这里作为参考车速 1Byte
	uint8_t PedalTravel;         //油门踏板开度    1Byte
	uint8_t brakeTravel;         //刹车踏板开度    1Byte
	uint8_t carTravel;           //车辆跑动距离    1Byte
	
	//ID:0X213
	uint8_t gearMode;            //挡位信息  1Bit
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
	uint16_t l_motor_target_torque;      //左电机目标转矩  2Byte
	uint16_t l_motor_target_rpm;		 //左电机目标转速 2Byte
	uint8_t  l_target_controlmodeorder;  //左电机目标控制模式指令
	uint8_t  l_gearstage;         		 //左电机扭挡位状态+主正接触器
	float dccur;          		     //直流母线电压

    //0x08B1EF21:  //VCUtoMCU2
	uint16_t r_motor_target_torque;      //右电机目标转矩  2Byte
	uint16_t r_motor_target_rpm;		 //右电机目标转速 2Byte
	uint8_t  r_target_controlmodeorder;  //右电机目标控制模式指令
	uint8_t  r_gearstage;         	  	 //右电机扭挡位状态+主正接触器
    //uint16_t dccur;     	  		 //右电机直流母线电压
		
    //0x0CFFC6EF:  //MCU1toVCU1
	uint16_t l_motor_torque;        	 //左转矩  2Byte
	uint16_t l_motor_rpm;		    	 //左转速 2Byte
	uint8_t l_controlmodeorder;			 //左电机控制模式指令
	uint8_t lmcuinfo1;					 //左电机控制器状态1
	uint8_t lmcuinfo2;					 //左电机控制器状态2 为节省资源，此消息包含了两帧报文的内容
										 
    //0x0CB221EF:  //MCU2toVCU1     	 
	uint16_t r_motor_torque;        	 //右转矩  2Byte
	uint16_t r_motor_rpm;		    	 //右转速 2Byte
	uint8_t r_controlmodeorder; 		 //右电机控制模式指令
	uint8_t rmcuinfo1;					 //右电机控制器状态1
	uint8_t rmcuinfo2;					 //右电机控制器状态2 为节省资源，此消息包含了两帧报文的内容
	
    //0x0CFFC7EF:  //MCU1toVCU2
	int8_t l_mcu_temp;				     //左控制器温度 
	int8_t l_motor_temp;				 //左电机温度
	float lmcu_dcvol;          		     //左电机直流母线电压
	float lmcu_dccur;          		     //左电机直流母线电流
	float lmcu_accur;  	     		     //左电机交流电流有效值
 
    //0x0CB321EF:  //MCU2toVCU2
	int8_t r_mcu_temp;			    	 //右控制器温度 
	int8_t r_motor_temp;				 //右电机温度
	float rmcu_dcvol;          		     //右电机直流母线电压
	float rmcu_dccur;          		     //右电机直流母线电流
	float rmcu_accur;          		     //右电机交流电流有效值

	//0x186040F3  //电池箱
	float BatVoltage; 					 //动力电池总电压
	float BatCurrent;		             //动力电池总电流
	uint8_t BatSoc;                      //动力电池Soc
	uint8_t BatSoh;                      //动力电池Soh
	uint8_t BatState;                    //动力电池状态
	uint8_t BatAlmLv;					 //动力警告级别
	uint8_t Batlife;                     //通信生命信息
	

};
extern uint8_t sd_data_send_mes;
extern uint16_t MessageCount;

extern struct RacingCarData racingCarData;

extern uint16_t *lcd_fb;

extern FATFS fs;                       /* FatFs 文件系统对象 */
extern FIL file;                       /* 文件对象 */
extern FRESULT f_res;                  /* 文件操作结果 */
extern UINT fnum;                      /* 文件成功读写数量 */
extern char FileName[4];
extern char ReadBuffer[100];    /* 读缓冲区 */
extern char CarDataBuffer[1024];            /* 写缓冲区 */
extern char buffer[10];
extern _Bool SDWrongFlag;
extern _Bool SDSendStateflg;

#endif
