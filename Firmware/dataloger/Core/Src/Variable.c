#include "Variable.h"

//can
struct RacingCarData racingCarData;
uint16_t sd_data_send_mes = 0;
uint16_t MessageCount = 0;

//display
uint16_t *lcd_fb;

//key
uint8_t Display_mode = 0;

//file system
FATFS fs;                       /* FatFs �ļ�ϵͳ���� */
FIL file;                       /* �ļ����� */
FRESULT f_res;                  /* �ļ�������� */
UINT fnum;                      /* �ļ��ɹ���д���� */
char FileName[4] = {0};
char ReadBuffer[100] = {0};    /* �������� */
char CarDataBuffer[1024] = {'\0'};    /* �������� */
char buffer[10] = {0};
_Bool SDWrongFlag = 0;
_Bool SDSendStateflg = 0;



