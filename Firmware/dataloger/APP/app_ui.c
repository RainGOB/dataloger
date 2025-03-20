#include "app_ui.h"

_Bool loop_flag = 0;  //重新刷新主菜单
_Bool start_up_flag = 0;  //防止重复刷新
_Bool recode_mode_flag = 0;

void start_up(){
	if(start_up_flag){
	if(Display_mode == 1){
	LCD_ShowString(10,10,"recorde mode",0x0000,0xFFFF,32,0);
	LCD_ShowString(10,40,"master mode",0xFFFF,0x0000,32,0);
	LCD_ShowString(10,70,"diagnose mode",0xFFFF,0x0000,32,0);
	}
	else if(Display_mode == 2){
	LCD_ShowString(10,10,"recorde mode",0xFFFF,0x0000,32,0);
	LCD_ShowString(10,40,"master mode",0x0000,0xFFFF,32,0);
	LCD_ShowString(10,70,"diagnose mode",0xFFFF,0x0000,32,0);	
	}
	else{
	LCD_ShowString(10,10,"recorde mode",0xFFFF,0x0000,32,0);
	LCD_ShowString(10,40,"master mode",0xFFFF,0x0000,32,0);
	LCD_ShowString(10,70,"diagnose mode",0x0000,0xFFFF,32,0);
	}
	}
	start_up_flag = 0;
}

void recorde_mode(){
	if(recode_mode_flag){
	lcd_clear(0x0000);
	LCD_ShowString(10,10,"recorde mode",0xFFFF,0x0000,16,0);
	}
}

