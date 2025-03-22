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
FATFS fs;                       /* FatFs 文件系统对象 */
FIL file;                       /* 文件对象 */
FRESULT f_res;                  /* 文件操作结果 */
UINT fnum;                      /* 文件成功读写数量 */
char FileName[4] = {0};
char ReadBuffer[100] = {0};    /* 读缓冲区 */
char CarDataBuffer[1024] = {'\0'};    /* 读缓冲区 */
char buffer[10] = {0};
_Bool SDWrongFlag = 0;
_Bool SDSendStateflg = 0;



