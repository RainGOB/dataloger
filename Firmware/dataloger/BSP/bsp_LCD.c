#include "bsp_LCD.h" 
#include "bsp_LCDfont.h"



 void LCD_WR_REG(uint8_t data){
	 LCD_DC_Clr();
	 HAL_SPI_Transmit_DMA(&hspi1,&data,1);
	 LCD_DC_Set();
 }
 
 void LCD_WR_DATA8(uint8_t data){
	 HAL_SPI_Transmit_DMA(&hspi1,&data,1);
	 HAL_Delay(1);
 }
 
 void LCD_WR_DATA(uint16_t data){
	 uint8_t high_byte = (data >> 8) & 0xFF;
	 uint8_t low_byte = data & 0xFF;
	 
	 HAL_SPI_Transmit_DMA(&hspi1,&high_byte,1);
	 HAL_SPI_Transmit_DMA(&hspi1,&low_byte,1);
 }
 
 void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1+20);
		LCD_WR_DATA(y2+20);
		LCD_WR_REG(0x2c);//储存器写
	}
	else
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1+20);
		LCD_WR_DATA(x2+20);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
}

 
 void LCD_init(void){
	 
	 //LCD_BLK_Set();
	 
	 LCD_RES_Set();
	 HAL_Delay(10);
	 LCD_RES_Clr(); //屏幕复位
	 HAL_Delay(10);
	 LCD_RES_Set();
	 HAL_Delay(120);
	 
	 LCD_BLK_Clr();
	 
	 LCD_WR_REG(0xfd);
	 LCD_WR_DATA8(0x06);
	 LCD_WR_DATA8(0x08);
	 
	 LCD_WR_REG(0x61);//add
	 LCD_WR_DATA8(0x07);//
	 LCD_WR_DATA8(0x04);//
	 
	 LCD_WR_REG(0x62);//bias setting
	 LCD_WR_DATA8(0x00);//00
	 LCD_WR_DATA8(0x44);//44
	 LCD_WR_DATA8(0x45);//40  47
	 
	 LCD_WR_REG(0x63);//
	 LCD_WR_DATA8(0x41);//
	 LCD_WR_DATA8(0x07);//
	 LCD_WR_DATA8(0x12);//
	 LCD_WR_DATA8(0x12);//
	 
	 LCD_WR_REG(0x64);//
	 LCD_WR_DATA8(0x37);//
	 //VSP
	 LCD_WR_REG(0x65);//Pump1=4.7MHz //PUMP1 VSP
	 LCD_WR_DATA8(0x09);//D6-5:pump1_clk[1:0] clamp 28 2b
	 LCD_WR_DATA8(0x10);//6.26
	 LCD_WR_DATA8(0x21);
	 //VSN
	 LCD_WR_REG(0x66); //pump=2 AVCL
	 LCD_WR_DATA8(0x09); //clamp 08 0b 09
	 LCD_WR_DATA8(0x10); //10
	 LCD_WR_DATA8(0x21);
	 //add source_neg_time
	 LCD_WR_REG(0x67);//pump_sel
	 LCD_WR_DATA8(0x20);//21 20
	 LCD_WR_DATA8(0x40);
	 
	 //gamma vap/van
	 LCD_WR_REG(0x68);//gamma vap/van
	 LCD_WR_DATA8(0x90);//
	 LCD_WR_DATA8(0x4c);//
	 LCD_WR_DATA8(0x7C);//VCOM  
	 LCD_WR_DATA8(0x66);//
	 
	 LCD_WR_REG(0xb1);//frame rate
	 LCD_WR_DATA8(0x0F);//0x0f fr_h[5:0] 0F
	 LCD_WR_DATA8(0x02);//0x02 fr_v[4:0] 02
	 LCD_WR_DATA8(0x01);//0x04 fr_div[2:0] 04
	 
	 LCD_WR_REG(0xB4);
	 LCD_WR_DATA8(0x01); //01:1dot 00:column
	 ////porch
	 LCD_WR_REG(0xB5);
	 LCD_WR_DATA8(0x02);//0x02 vfp[6:0]
	 LCD_WR_DATA8(0x02);//0x02 vbp[6:0]
	 LCD_WR_DATA8(0x0a);//0x0A hfp[6:0]
	 LCD_WR_DATA8(0x14);//0x14 hbp[6:0]
	 
	 LCD_WR_REG(0xB6);
	 LCD_WR_DATA8(0x04);//
	 LCD_WR_DATA8(0x01);//
	 LCD_WR_DATA8(0x9f);//
	 LCD_WR_DATA8(0x00);//
	 LCD_WR_DATA8(0x02);//
	 ////gamme sel
	 LCD_WR_REG(0xdf);//
	 LCD_WR_DATA8(0x11);//gofc_gamma_en_sel=1
	 ////gamma_test1 A1#_wangly
	 //3030b_gamma_new_
	 //GAMMA---------------------------------/////////////
	 
	 //GAMMA---------------------------------/////////////
	 LCD_WR_REG(0xE2);	
	 LCD_WR_DATA8(0x13);//vrp0[5:0]	V0 13
	 LCD_WR_DATA8(0x00);//vrp1[5:0]	V1 
	 LCD_WR_DATA8(0x00);//vrp2[5:0]	V2 
	 LCD_WR_DATA8(0x30);//vrp3[5:0]	V61 
	 LCD_WR_DATA8(0x33);//vrp4[5:0]	V62 
	 LCD_WR_DATA8(0x3f);//vrp5[5:0]	V63
	 
	 LCD_WR_REG(0xE5);	
	 LCD_WR_DATA8(0x3f);//vrn0[5:0]	V63
	 LCD_WR_DATA8(0x33);//vrn1[5:0]	V62	
	 LCD_WR_DATA8(0x30);//vrn2[5:0]	V61 
	 LCD_WR_DATA8(0x00);//vrn3[5:0]	V2 
	 LCD_WR_DATA8(0x00);//vrn4[5:0]	V1 
	 LCD_WR_DATA8(0x13);//vrn5[5:0]  V0 13
	 
	 LCD_WR_REG(0xE1);	
	 LCD_WR_DATA8(0x00);//prp0[6:0]	V15
	 LCD_WR_DATA8(0x57);//prp1[6:0]	V51 
	 
	 LCD_WR_REG(0xE4);	
	 LCD_WR_DATA8(0x58);//prn0[6:0]	V51 
	 LCD_WR_DATA8(0x00);//prn1[6:0]  V15
	 
	 LCD_WR_REG(0xE0);
	 LCD_WR_DATA8(0x01);//pkp0[4:0]	V3 
	 LCD_WR_DATA8(0x03);//pkp1[4:0]	V7  
	 LCD_WR_DATA8(0x0d);//pkp2[4:0]	V21
	 LCD_WR_DATA8(0x0e);//pkp3[4:0]	V29 
	 LCD_WR_DATA8(0x0e);//pkp4[4:0]	V37 
	 LCD_WR_DATA8(0x0c);//pkp5[4:0]	V45 
	 LCD_WR_DATA8(0x15);//pkp6[4:0]	V56 
	 LCD_WR_DATA8(0x19);//pkp7[4:0]	V60 
	 
	 LCD_WR_REG(0xE3);	
	 LCD_WR_DATA8(0x1a);//pkn0[4:0]	V60 
	 LCD_WR_DATA8(0x16);//pkn1[4:0]	V56 
	 LCD_WR_DATA8(0x0C);//pkn2[4:0]	V45 
	 LCD_WR_DATA8(0x0f);//pkn3[4:0]	V37 
	 LCD_WR_DATA8(0x0e);//pkn4[4:0]	V29 
	 LCD_WR_DATA8(0x0d);//pkn5[4:0]	V21 
	 LCD_WR_DATA8(0x02);//pkn6[4:0]	V7  
	 LCD_WR_DATA8(0x01);//pkn7[4:0]	V3 
	 //GAMMA---------------------------------/////////////
	 
	 //source
	 LCD_WR_REG(0xE6);
	 LCD_WR_DATA8(0x00);
	 LCD_WR_DATA8(0xff);//SC_EN_START[7:0] f0
	 
	 LCD_WR_REG(0xE7);
	 LCD_WR_DATA8(0x01);//CS_START[3:0] 01
	 LCD_WR_DATA8(0x04);//scdt_inv_sel cs_vp_en
	 LCD_WR_DATA8(0x03);//CS1_WIDTH[7:0] 12
	 LCD_WR_DATA8(0x03);//CS2_WIDTH[7:0] 12
	 LCD_WR_DATA8(0x00);//PREC_START[7:0] 06
	 LCD_WR_DATA8(0x12);//PREC_WIDTH[7:0] 12
	 
	 LCD_WR_REG(0xE8); //source
	 LCD_WR_DATA8(0x00); //VCMP_OUT_EN 81-
	 LCD_WR_DATA8(0x70); //chopper_sel[6:4]
	 LCD_WR_DATA8(0x00); //gchopper_sel[6:4] 60
	 ////gate
	 LCD_WR_REG(0xEc);
	 LCD_WR_DATA8(0x52);//52
	 
	 LCD_WR_REG(0xF1);
	 LCD_WR_DATA8(0x01);//te_pol tem_extend 00 01 03
	 LCD_WR_DATA8(0x01);
	 LCD_WR_DATA8(0x02);
	 
	 
	 LCD_WR_REG(0xF6);
	 LCD_WR_DATA8(0x09);
	 LCD_WR_DATA8(0x10);
	 LCD_WR_DATA8(0x00);//
	 LCD_WR_DATA8(0x00);//40 3线2通道
	 
	 LCD_WR_REG(0xfd);
	 LCD_WR_DATA8(0xfa);
	 LCD_WR_DATA8(0xfc);
	 
	 LCD_WR_REG(0x3a);
	 LCD_WR_DATA8(0x05);//
	 
	 LCD_WR_REG(0x35);
	 LCD_WR_DATA8(0x00);
	 
	 LCD_WR_REG(0x36);
	 if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x08);
	 //LCD_WR_DATA8(0xC8);
	 else LCD_WR_DATA8(0x78);
	 //LCD_WR_DATA8(0xA8);
	 
	 LCD_WR_REG(0x21); 
	 
	 LCD_WR_REG(0x11); // exit sleep
	 HAL_Delay(200);
	 LCD_WR_REG(0x29); // display on
	 HAL_Delay(10); 
 }
 
 
 //画点
 void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
	/*
    if (x > LCD_WIDTH || y > LCD_HEIGHT) {
        return;
    }
	*/
    LCD_Address_Set(x,y,x,y);
	LCD_WR_DATA(color);

#if USE_DMA2D_EN
#else
#endif /* USE_DMA2D_EN */
}
 

//画直线
void lcd_draw_line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
    uint16_t x_delta;
    uint16_t y_delta;
    int16_t x_sign;
    int16_t y_sign;
    int16_t error;
    int16_t error2;
    
    x_delta = (x1 < x2) ? (x2 - x1) : (x1 - x2);
    y_delta = (y1 < y2) ? (y2 - y1) : (y1 - y2);
    x_sign = (x1 < x2) ? 1 : -1;
    y_sign = (y1 < y2) ? 1 : -1;
    error = x_delta - y_delta;
    
    lcd_draw_point(x2, y2, color);
    
    while ((x1 != x2) || (y1 != y2))
    {
        lcd_draw_point(x1, y1, color);
        
        error2 = error << 1;   			//将error乘以2,这样会更快
        if (error2 > -y_delta) 
        { 
            error -= y_delta;
            x1 += x_sign;
        }
        
        if (error2 < x_delta)
        {
            error += x_delta;
            y1 += y_sign;
        }
    }
}
 
//画矩形
void lcd_draw_rectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	lcd_draw_line(x1,y1,x1,y2,color);
	lcd_draw_line(x1,y2,x2,y2,color);
	lcd_draw_line(x1,y2,x2,y2,color);
	lcd_draw_line(x1,y1,x2,y1,color);
}

//画圆
void lcd_draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color)
{
    int32_t x_t;
    int32_t y_t;
    int32_t error;
    int32_t error2;
    
    x_t = -r;
    y_t = 0;
    error = 2 - 2 * r;
    
    do {
        lcd_draw_point(x - x_t, y + y_t, color);
        lcd_draw_point(x + x_t, y + y_t, color);
        lcd_draw_point(x + x_t, y - y_t, color);
        lcd_draw_point(x - x_t, y - y_t, color);
        
        error2 = error;
        if (error2 <= y_t)
        {
            y_t++;
            error = error + (y_t * 2 + 1);
            if ((-x_t == y_t) && (error2 <= x_t))
            {
                error2 = 0;
            }
        }
        
        if (error2 > x_t)
        {
            x_t++;
            error = error + (x_t * 2 + 1);
        }
    } while (x_t <= 0);
}


//填充颜色
void lcd_fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{	
	uint16_t i,j; 
	
	LCD_Address_Set(xs,ys,xe-1,ye-1);//设置显示范围
	//LCD_WR_DATA(color);

	for(i=ys;i<ye;i++){													   	 	
	for(j=xs;j<xe;j++){
		LCD_WR_DATA(color);
	}} 	

	
 /*
    LCD_WR_DATA(color);
  */
}

//清屏
void lcd_clear(uint16_t color)
{
#if USE_DMA2D
    dma2d_transfer_data_r2m((uint32_t *)LAYER_FB_ADDR, LCD_WIDTH, LCD_HEIGHT, 0, color);
#else
	LCD_Address_Set(0,0,LCD_WIDTH-1,LCD_HEIGHT-1);
    LCD_WR_DATA(color);
#endif /* USE_DMA2D_EN */
}

/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t temp,sizex,t,m=0;
	uint16_t i,TypefaceNum;//一个字符所占字节大小
	uint16_t x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //得到偏移后的值
	LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //设置光标位置 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==12)temp=ascii_1206[num][i];		       //调用6x12字体
		else if(sizey==16)temp=ascii_1608[num][i];		 //调用8x16字体
		else if(sizey==24)temp=ascii_2412[num][i];		 //调用12x24字体
		else if(sizey==32)temp=ascii_3216[num][i];		 //调用16x32字体
		else return;
		for(t=0;t<8;t++)
		{
			if(!mode)//非叠加模式
			{
				if(temp&(0x01<<t))LCD_WR_DATA(fc);
				else LCD_WR_DATA(bc);
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//叠加模式
			{
				if(temp&(0x01<<t))lcd_draw_point(x,y,fc);//画一个点
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}


/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y显示坐标
                *p 要显示的字符串
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}

/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
      函数说明：显示整数变量
      入口数据：x,y显示坐标
                num 要显示整数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	uint8_t sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 


/******************************************************************************
      函数说明：显示两位小数变量
      入口数据：x,y显示坐标
                num 要显示小数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp,sizex;
	uint16_t num1;
	sizex=sizey/2;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
			t++;
			len+=1;
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
}

/******************************************************************************
      函数说明：显示图片
      入口数据：x,y起点坐标
                length 图片长度
                width  图片宽度
                pic[]  图片数组    
      返回值：  无
******************************************************************************/
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[])
{
	uint16_t i,j;
	uint32_t k=0;
	LCD_Address_Set(x,y,x+length-1,y+width-1);
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_WR_DATA8(pic[k*2]);
			LCD_WR_DATA8(pic[k*2+1]);
			k++;
		}
	}			
}

