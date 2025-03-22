#include "Variable.h"
#include "string.h"
#include "app_fatdata.h"

/*  **********************    数据转换    ***********************/
//uint8_t2string
void uint8_t2string(uint8_t num,char * str){
	uint8_t i = 0; //指示填充str
	if(num >= 100)
		str[i++] = num/100 + 48;
	if(num >= 10)
		str[i++] = num/10%10 + 48;
	str[i++] = num%10 + 48;\
	str[i++] = ' ';
	str[i] = '\0';

}

//int8_tg2string
void int8_t2string(int8_t num , char* str){
	uint8_t i = 0;
	
	if(num < 0){
		num = -num;
		str[i++] = '-';
	}
	
	if(num>=100)
	str[i++] = num/100%10 + 48;
	if(num>=10)
	str[i++] = num/10%10 + 48;
	str[i++] = num%10 + 48;
	str[i++] = ' ';
	str[i] = '\0';
	
}

//uint16_tg2string
void uint16_t2string(uint16_t num , char* str){
	uint8_t i = 0;
	
	if(num>=10000)
	str[i++] = num/10000 + 48;
	if(num>=1000)
	str[i++] = num/1000%10 + 48;
	if(num>=100)
	str[i++] = num/100%10 + 48;
	if(num>=10)
	str[i++] = num/10%10 + 48;
	str[i++] = num%10 + 48;
	str[i++] = ' ';
	str[i] = '\0';

}

//float2string  本函数取值目标为保留正负10000以内，以及小数点后两位
void float2string(float num,char* str){
	uint8_t i = 0;
	if(num < 0){
		num = -num;
		str[i++] = '-';
	}
	
	if(num>=10000)
	str[i++] = num/10000 + 48;
	if(num>=1000)
	str[i++] = (int)(num/1000)%10 + 48;
	if(num>=100)
	str[i++] = (int)(num/100)%10 + 48;
	if(num>=10)
	str[i++] = (int)(num/10)%10 + 48;
	str[i++] = (int)(num)%10 + 48;
	str[i++] = '.';
	str[i++] = (int)(num * 10) %10 +48;
	str[i++] = (int)(num * 100) %10 +48;
	
	str[i++] = ' ';
	str[i] = '\0';
	
}

void Car_strcat(char * dest , const char * src){
	// 找到目标字符串的末尾
    while (*dest != '\0') {
        dest++;
    }

    // 将源字符串拼接到目标字符串的末尾
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    // 添加字符串结束符
    *dest = '\0';
}

/******************* 数据处理 ********************/
//data upload
//float类型只保留小数点后两位，方便用两个unsigned int 赋值,单位数据不能超过255
void DecodeSdData(){
	memset(CarDataBuffer,0x00,sizeof(CarDataBuffer)); 
	
	Car_strcat(CarDataBuffer,"0:");
	uint8_t2string(racingCarData.FrontSpeed,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.PedalTravel,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.brakeTravel,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.carTravel,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.gearMode,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.angle,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.acc_x,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.acc_y,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.acc_z,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.yaw,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.pitch,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.roll,buffer);
	Car_strcat(CarDataBuffer,buffer);
	Car_strcat(CarDataBuffer,"\r\n");
}

void DecodeSdData1_Power(){
	memset(CarDataBuffer,0x00,sizeof(CarDataBuffer)); 
	
	Car_strcat(CarDataBuffer,"1.1:");
	uint16_t2string(racingCarData.l_motor_target_torque,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.l_motor_target_rpm,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.l_target_controlmodeorder,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.l_gearstage,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.dccur,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.r_motor_target_torque,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.r_motor_target_rpm,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.r_target_controlmodeorder,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.r_gearstage,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.l_motor_torque,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.l_motor_rpm,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.l_controlmodeorder,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.lmcuinfo1,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.lmcuinfo2,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.r_motor_torque,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.r_motor_rpm,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.r_controlmodeorder,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.rmcuinfo1,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.rmcuinfo2,buffer);
	Car_strcat(CarDataBuffer,buffer);
	int8_t2string(racingCarData.l_mcu_temp,buffer);
	Car_strcat(CarDataBuffer,buffer);
	int8_t2string(racingCarData.l_motor_temp,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.lmcu_dcvol,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.lmcu_dccur,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.lmcu_accur,buffer);
	Car_strcat(CarDataBuffer,buffer);
	Car_strcat(CarDataBuffer,"\r\n");
}

void DecodeSdData2_Power(){
	memset(CarDataBuffer,0x00,sizeof(CarDataBuffer)); 
	
	Car_strcat(CarDataBuffer,"1.2:");
	int8_t2string(racingCarData.r_mcu_temp,buffer);
	Car_strcat(CarDataBuffer,buffer);
	int8_t2string(racingCarData.r_motor_temp,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.rmcu_dcvol,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.rmcu_dccur,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.rmcu_accur,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.BatVoltage,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.BatCurrent,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.BatSoc,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.BatSoh,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.BatState,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.BatAlmLv,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.Batlife,buffer);
	Car_strcat(CarDataBuffer,buffer);
	Car_strcat(CarDataBuffer,"\r\n");
}


void DecodeSdData_Power(){
	memset(CarDataBuffer,0x00,sizeof(CarDataBuffer)); 
	
	Car_strcat(CarDataBuffer,"1:");
	uint16_t2string(racingCarData.l_motor_target_torque,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.l_motor_target_rpm,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.l_target_controlmodeorder,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.l_gearstage,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.dccur,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.r_motor_target_torque,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.r_motor_target_rpm,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.r_target_controlmodeorder,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.r_gearstage,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.l_motor_torque,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.l_motor_rpm,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.l_controlmodeorder,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.lmcuinfo1,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.lmcuinfo2,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.r_motor_torque,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint16_t2string(racingCarData.r_motor_rpm,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.r_controlmodeorder,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.rmcuinfo1,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.rmcuinfo2,buffer);
	Car_strcat(CarDataBuffer,buffer);
	int8_t2string(racingCarData.l_mcu_temp,buffer);
	Car_strcat(CarDataBuffer,buffer);
	int8_t2string(racingCarData.l_motor_temp,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.lmcu_dcvol,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.lmcu_dccur,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.lmcu_accur,buffer);
	Car_strcat(CarDataBuffer,buffer);
	
	//分隔开
	int8_t2string(racingCarData.r_mcu_temp,buffer);
	Car_strcat(CarDataBuffer,buffer);
	int8_t2string(racingCarData.r_motor_temp,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.rmcu_dcvol,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.rmcu_dccur,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.rmcu_accur,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.BatVoltage,buffer);
	Car_strcat(CarDataBuffer,buffer);
	float2string(racingCarData.BatCurrent,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.BatSoc,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.BatSoh,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.BatState,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.BatAlmLv,buffer);
	Car_strcat(CarDataBuffer,buffer);
	uint8_t2string(racingCarData.Batlife,buffer);
	Car_strcat(CarDataBuffer,buffer);
	Car_strcat(CarDataBuffer,"\r\n");
}

