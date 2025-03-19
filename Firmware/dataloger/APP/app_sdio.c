#include "bsp_sdio.h"
#include "fatfs.h"
#include "Variable.h"
#include "app_fatdata.h"
#include "bsp_WS2812B.h"
#include "bsp_lcd.h"

#include "stdio.h"

BYTE CarDataHead1[] =            /* 写缓冲区 */
	"0:Speed Throttle Brake Mileage RotAngle Acc_x Acc_y Acc_z Roll Pitch Yaw DcCur \
L TaTorq TaRPM TaCon TaGear Torq RPM CON inf1,2 UTemp MTemp dcvol dccur accur\r\n";
BYTE CarDataHead2[] =            /* 写缓冲区 */
	"1:R TaTorq TaRPM TaCon TaGear Torq RPM CON inf1,2 UTemp MTemp dcvol dccur accur \
Bat Vol Cur Soc Soh State AlmLv life\r\n";

TCHAR TitleHead[20] = {"0:LYdata"};


/*********************** 文件处理 ***********************/

void title_strcat(char * dest , const char * src){
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
	
	*dest = '.';dest++;
	*dest = 't';dest++;
	*dest = 'x';dest++;
	*dest = 't';dest++;

    // 添加字符串结束符
    *dest = '\0';
}

//没有关闭文件，记得关闭否则数据全部丢失
int FATFS_CarOpen(){
	printf("\r\n*****Write from text file*****\r\n");
	title_strcat(TitleHead,FileName);
	f_res = f_open(&file, TitleHead , FA_CREATE_ALWAYS | FA_WRITE);
	if(f_res == FR_OK){
		printf("open file sucess!!\r\n");
		f_res = f_write(&file,CarDataHead1,sizeof(CarDataHead1),&fnum);
		f_res = f_write(&file,CarDataHead2,sizeof(CarDataHead2),&fnum);
		if(f_res == FR_OK){
			printf("write FileName success!!(%d)\r\n",fnum);
			SDSendStateflg = 1;
			//printf("write FileName: %s\r\n",CarDataBuffer);
		}			
		else{
			printf("write FileName error: %d\r\n",f_res);
		}
	}
	else{
		printf("open FileName error!!! %d\r\n",f_res);
	}
	
	return f_res;
}

//每次使用完成FATFS_Write或FATFS_Read后都要用这个函数
void FATFS_Carclosefile(){
	f_close(&file);
	f_mount(NULL, "0:", 1);
}

int FATFS_CarWrite(){
	if(SDWrongFlag != 1){
	  if((sd_data_send_mes & 0xF) == 0xF){
		DecodeSdData();
		LCD_ShowString(48,80,(unsigned char *)"send data to sd card",0xFFFF,0x0000,16,0);
		//MessageCount++;
		if(SDWrongFlag == 0 & SDSendStateflg == 1){
		printf("write data\r\n");
		f_res = f_write(&file,CarDataBuffer,sizeof(CarDataBuffer),&fnum);
		if(f_res == FR_OK){
			printf("cardata write file success:%d",fnum);
			sd_data_send_mes &= 0X3F0;
		}
		else{
		    printf("cardata write file fail");
			ws2812_red(1);
			SDWrongFlag = 1;
		}
		}
		else{
			printf("there is somthing wrong with FAT");
		}
	  }
	  if((sd_data_send_mes & 0x7F0) == 0x3F0 ){
		DecodeSdData();
		LCD_ShowString(48,80,(unsigned char *)"send data to sd card",0xFFFF,0x0000,16,0);
		//MessageCount++;
		if(SDWrongFlag == 0 & SDSendStateflg == 1){
		printf("write data\r\n");
		f_res = f_write(&file,CarDataBuffer,sizeof(CarDataBuffer),&fnum);
		if(f_res == FR_OK){
			printf("cardata write file success:%d",fnum);
			sd_data_send_mes &= 0XF;
		}
		else{
		    printf("cardata write file fail");
			ws2812_red(1);
			SDWrongFlag = 1;
		}
		}
		else{
			printf("there is somthing wrong with FAT");
		}
	  }
}
}

int FATFS_Load(){
	//在外部SD卡挂载文件系统，文件系统挂载时会对SD卡初始化
	f_res = f_mount(&fs,"0:",1);
	
	printf("\r\n***** Register the gile system object to the FatFS module *****\r\n");
	//如果没有创建文件系统就格式化创建文件系统
	if(f_res == FR_NO_FILESYSTEM){
		printf("The SD Card does not yet have a file system and is about to be formatted...\r\n");
		
		//格式化
		f_res = f_mkfs("0:",0,4096,0,_MAX_SS);
		if(f_res == FR_OK){
			printf("The SD card successfully formatted the file system\r\n");
			//格式化后，先取消挂载
			f_res = f_mount (NULL,"0:",1);
			f_res = f_mount(&fs,"0:",1);
		}
		else{
			printf("mount error");		
		}
	}
	else if(f_res != FR_OK){
		printf("mount error: %d \r\n",f_res);
	}
	else	printf("file system has already been formatted");
	
	return f_res;
}

//读取文件技术文件，并用此是计数为车载数据文件命名
//使用前确保卡里里面有此文件
int FATFS_ReadPara(){
	printf("\r\n***** Read data from text files *****\r\n");
	f_res = f_open(&file, "0:FileParameter.txt",FA_OPEN_EXISTING | FA_READ);
	if(f_res == FR_OK){
		printf("open file sucess!!!\r\n");
		f_res = f_read(&file,&ReadBuffer,4,&fnum);
		if(f_res == FR_OK){
			printf("read FileName sucess!!(%d)\r\n",fnum);
			printf("read FileName Data : %s\r\n",ReadBuffer);
		}
		else{
			printf("read FileName error!!! %d\r\n",f_res);
		}
	f_close(&file);
	}
	else{
		printf("open file error: %d\r\n",f_res);
	}
	
	//为了防止溢出，只能存储0~999个文件名
    FileName[0] = ReadBuffer[0];
    FileName[1] = ReadBuffer[1];
    FileName[2] = ReadBuffer[2];
    if (FileName[2] < '9') {
        FileName[2] += 1; }
    else {
        FileName[2] = '0';
        FileName[1] += 1;
    }
    if (FileName[1] > '9') {
        FileName[1] = '0';
        FileName[0] += 1;
    }
	FileName[3] = '\0';
	
	printf("\r\n*****Write from text file*****\r\n");
	f_res = f_open(&file, "0:FileParameter.txt", FA_CREATE_ALWAYS | FA_WRITE);
	if(f_res == FR_OK){
		printf("open file sucess!!\r\n");
		f_res = f_write(&file,&FileName,sizeof(FileName),&fnum);
		if(f_res == FR_OK){
			printf("write FileName success!!(%d)\r\n",fnum);
			//printf("write FileName: %s\r\n",CarDataBuffer);
		}			
		else{
			printf("write FileName error: %d\r\n",f_res);
		}
		f_close(&file);
	}
	else{
		printf("write FileName error!!! %d\r\n",f_res);
	}
	
	//取消挂载
	//f_mount(NULL, "0:", 1);
	
	return f_res;
}


