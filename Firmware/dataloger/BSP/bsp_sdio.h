#ifndef _BSP_SDIO_
#define _BSP_SDIO_
#include "main.h"

extern HAL_SD_CardInfoTypeDef g_sd_card_info_handle; /* SD卡信息结构体 */

#define SD_TIMEOUT             ((uint32_t)100000000)                                  /* 超时时间 */

#define SD_TOTAL_SIZE_MB(__Handle__)    (((uint64_t)((__Handle__)->SdCard.LogBlockNbr)*((__Handle__)->SdCard.LogBlockSize))>>20)

void sys_intx_disable(void);
void sys_intx_enable(void);

uint8_t sd_init(void);
uint8_t get_sd_card_state(void);
uint8_t get_sd_card_info(HAL_SD_CardInfoTypeDef *cardinfo);
uint8_t sd_read_disk(uint8_t *pbuf, uint32_t saddr, uint32_t cnt);
uint8_t sd_write_disk(uint8_t *pbuf, uint32_t saddr, uint32_t cnt);
void show_sdcard_info(void);
//void sd_test_read(uint32_t secaddr, uint32_t seccnt);
//void sd_test_write(uint32_t secaddr, uint32_t seccnt);
#endif
