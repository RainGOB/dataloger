#ifndef _APP_FATDATA_H_
#define _APP_FATDATA_H_

#include "main.h"


void uint8_t2string(uint8_t num,char * str);
void int8_t2string(int8_t num , char* str);
void uint16_t2srting(uint16_t num , char* str);
void float2string(float num,char* str);
void Car_strcat(char * dest , const char * src);

void DecodeSdData();
void DecodeSdData_Power();
#endif
