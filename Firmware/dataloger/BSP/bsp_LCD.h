#ifndef _BSP_LCD_H
#define _BSP_LCD_H

#include "main.h"
#include "spi.h"

#define USE_HORIZONTAL 1  //…Ë÷√∫·∆¡ªÚ’ﬂ ˙∆¡£¨0Œ™ ˙∆¡£¨1Œ™∫·∆¡

#if USE_HORIZONTAL==0
#define LCD_WIDTH 240
#define LCD_HEIGHT 280

#else
#define LCD_WIDTH 280
#define LCD_HEIGHT 240
#endif



#define LCD_RES_Clr()  HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin,(LCD_BL_GPIO_Port,LCD_BL_Pin,GPIO_PIN_RESET)//BLK
#define LCD_BLK_Set()  HAL_GPIO_WritePin(LCD_BL_GPIO_Port,LCD_BL_Pin,GPIO_PIN_SET)


 void LCD_WR_REG(uint8_t data);
 void LCD_WR_DATA(uint16_t data);
 void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
 void LCD_init(void);
 
 void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
 void lcd_draw_line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
 void lcd_draw_rectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
 void lcd_draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
 void lcd_fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color);
 void lcd_clear(uint16_t color);
 
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[]);
#endif

