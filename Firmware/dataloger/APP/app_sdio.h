#ifndef _APP_SDIO_H_
#define _APP_SDIO_H_

#include "main.h"

void Fatfs_init(void);
int FATFS_Load(void);
int FATFS_ReadPara(void);

int FATFS_CarOpen(void);
int FATFS_CarWrite(void);
void FATFS_Carclosefile(void);

#endif
