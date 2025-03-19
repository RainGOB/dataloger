#include "bsp_sdio.h"
#include "main.h"
#include "sdio.h"
#include "bsp_WS2812B.h"
#include "fatfs.h"
#include "stdio.h"

HAL_SD_CardInfoTypeDef g_sd_card_info_handle; /* SD����Ϣ�ṹ�� */

/*********************** �жϴ��� ***********************/
/**
 * @brief       �ر������ж�(���ǲ�����fault��NMI�ж�)
 * @param       ��
 * @retval      ��
 */
void sys_intx_disable(void)
{
    __ASM volatile("cpsid i");
}

/**
 * @brief       ���������ж�
 * @param       ��
 * @retval      ��
 */
void sys_intx_enable(void)
{
    __ASM volatile("cpsie i");
}


uint8_t sd_init(void)
{
    uint8_t SD_Error;

    SD_Error = HAL_SD_Init(&hsd);
    if (SD_Error != HAL_OK)
    {
        return 1;
    }
 
    HAL_SD_GetCardInfo(&hsd, &g_sd_card_info_handle);                  /* ��ȡSD����Ϣ */
/*
    SD_Error = HAL_SD_ConfigWideBusOperation(&hsd, SDIO_BUS_WIDE_4B);  * ʹ�ܿ�����ģʽ 
    if (SD_Error != HAL_OK)
    {
        return 2;
    }
*/
    return 0;
}

/**
 * @brief       ��ȡ����Ϣ����
 * @param       cardinfo   : SD����Ϣ���
 * @retval      ����ֵ:��ȡ����Ϣ״ֵ̬
 */
uint8_t get_sd_card_info(HAL_SD_CardInfoTypeDef *cardinfo)
{
    uint8_t sta;
    sta = HAL_SD_GetCardInfo(&hsd, cardinfo);
    return sta;
}

/**
 * @brief       �ж�SD���Ƿ���Դ���(��д)����
 * @param       ��
 * @retval      ����ֵ:SD_TRANSFER_OK      ������ɣ����Լ�����һ�δ���
                       SD_TRANSFER_BUSY SD ����æ�������Խ�����һ�δ���
 */
uint8_t get_sd_card_state(void)
{
    return ((HAL_SD_GetCardState(&hsd) == HAL_SD_CARD_TRANSFER) ? SD_TRANSFER_OK : SD_TRANSFER_BUSY);
}

/**
 * @brief       ��SD��(fatfs/usb����)
 * @param       pbuf  : ���ݻ�����
 * @param       saddr : ������ַ
 * @param       cnt   : ��������
 * @retval      0, ����;  ����, �������(���SD_Error����);
 */
uint8_t sd_read_disk(uint8_t *pbuf, uint32_t saddr, uint32_t cnt)
{
    uint8_t sta = HAL_OK;
    uint32_t timeout = SD_TIMEOUT;
    long long lsector = saddr;
   // sys_intx_disable();                                                                    /* �ر����ж�(POLLINGģʽ,�Ͻ��жϴ��SDIO��д����!!!) */
    sta = HAL_SD_ReadBlocks(&hsd, (uint8_t *)pbuf, lsector, cnt, SD_TIMEOUT);  /* ���sector�Ķ����� */

    /* �ȴ�SD������ */
    while (get_sd_card_state() != SD_TRANSFER_OK)
    {
        if (timeout-- == 0)
        {
            sta = SD_TRANSFER_BUSY;
        }
    }

    //sys_intx_enable();      /* �������ж� */
    return sta;
}

/**
 * @brief       дSD��(fatfs/usb����)
 * @param       pbuf  : ���ݻ�����
 * @param       saddr : ������ַ
 * @param       cnt   : ��������
 * @retval      0, ����;  ����, �������(���SD_Error����);
 */
uint8_t sd_write_disk(uint8_t *pbuf, uint32_t saddr, uint32_t cnt)
{
    uint8_t sta = HAL_OK;
    uint32_t timeout = SD_TIMEOUT;
    long long lsector = saddr;
    sys_intx_disable();                                                                     /* �ر����ж�(POLLINGģʽ,�Ͻ��жϴ��SDIO��д����!!!) */
    sta = HAL_SD_WriteBlocks(&hsd, (uint8_t *)pbuf, lsector, cnt, SD_TIMEOUT);  /* ���sector��д���� */

    /* �ȴ�SD��д�� */
    while (get_sd_card_state() != SD_TRANSFER_OK)
    {
        if (timeout-- == 0)
        {
            sta = SD_TRANSFER_BUSY;
        }
    }

    sys_intx_enable();     /* �������ж� */
    
    return sta;
}

/**
 * @brief       ͨ�����ڴ�ӡSD�������Ϣ
 * @param       ��
 * @retval      ��
 */
void show_sdcard_info(void)
{
    HAL_SD_CardCIDTypeDef sd_card_cid;

    HAL_SD_GetCardCID(&hsd, &sd_card_cid);        /* ��ȡCID */
    get_sd_card_info(&g_sd_card_info_handle);    /* ��ȡSD����Ϣ */

    switch (g_sd_card_info_handle.CardType)
    {
        case CARD_SDSC:
        {
            if (g_sd_card_info_handle.CardVersion == CARD_V1_X)
            {
                printf("Card Type:SDSC V1\r\n");
            }
            else if (g_sd_card_info_handle.CardVersion == CARD_V2_X)
            {
                printf("Card Type:SDSC V2\r\n");
            }
        }
        break;

        case CARD_SDHC_SDXC:
            printf("Card Type:SDHC\r\n");
            break;
        default: break;
    }

    printf("Card ManufacturerID:%d\r\n", sd_card_cid.ManufacturerID);                   /* ������ID */
    printf("Card RCA:%d\r\n", g_sd_card_info_handle.RelCardAdd);                        /* ����Ե�ַ */
    printf("Card Capacity:%d MB\r\n", (uint32_t)SD_TOTAL_SIZE_MB(&hsd));    /* ��ʾ���� */
    printf("Card BlockSize:%d\r\n\r\n", g_sd_card_info_handle.BlockSize);               /* ��ʾ���С */
}

/**
 * @brief       ����SD���Ķ�ȡ
 * @note        ��secaddr��ַ��ʼ,��ȡseccnt������������
 * @param       secaddr : ������ַ
 * @param       seccnt  : ������
 * @retval      ��
 */
/*
void sd_test_read(uint32_t secaddr, uint32_t seccnt)
{
    uint32_t i;
    uint8_t *buf;
    uint8_t sta = 0;
    buf = mymalloc(SRAMIN, seccnt * 512);       * �����ڴ�,��SDRAM�����ڴ� *
    sta = sd_read_disk(buf, secaddr, seccnt);   * ��ȡsecaddr������ʼ������ *

    if (sta == 0)
    {
        lcd_show_string(30, 170, 200, 16, 16, "USART1 Sending Data...", BLUE);
        printf("SECTOR %d DATA:\r\n", secaddr);

        for (i = 0; i < seccnt * 512; i++)
        {
            printf("%x ", buf[i]);              * ��ӡsecaddr��ʼ���������� *
        }

        printf("\r\nDATA ENDED\r\n");
        lcd_show_string(30, 170, 200, 16, 16, "USART1 Send Data Over!", BLUE);
    }
    else
    {
        printf("err:%d\r\n", sta);
        lcd_show_string(30, 170, 200, 16, 16, "SD read Failure!      ", BLUE);
    }

    myfree(SRAMIN, buf);                       * �ͷ��ڴ� 
}
*/
/**
 * @brief       ����SD����д��
 * @note        ��secaddr��ַ��ʼ,д��seccnt������������
 *              ����!! ���дȫ��0XFF������,���������SD��.
 *
 * @param       secaddr : ������ַ
 * @param       seccnt  : ������
 * @retval      ��
 */
/*
void sd_test_write(uint32_t secaddr, uint32_t seccnt)
{
    uint32_t i;
    uint8_t *buf;
    uint8_t sta = 0;
    buf = mymalloc(SRAMIN, seccnt * 512);       * ��SRAM�����ڴ� *

    for (i = 0; i < seccnt * 512; i++)          * ��ʼ��д�������,��3�ı���. *
    {
        buf[i] = i * 3;
    }

    sta = sd_write_disk(buf, secaddr, seccnt);  * ��secaddr������ʼд��seccnt���������� *

    if (sta == 0)
    {
        printf("Write over!\r\n");
    }
    else
    {
        printf("err:%d\r\n", sta);
    }

    myfree(SRAMIN, buf);                        * �ͷ��ڴ� *
}
*/
