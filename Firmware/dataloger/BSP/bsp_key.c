#include "bsp_key.h"

uint8_t key_scan(uint8_t mode){
	static uint8_t key_up = 1;
	uint8_t keyval = 0;
	if(mode) key_up=1;

	if(key_up &&  (KEY_PUSH == 0 || KEY_LEFT == 0 || KEY_RIGHT == 0 )){
		HAL_Delay(10);
		key_up = 0;
		
		if(KEY_LEFT == 0) keyval = KeyLeft;
		if(KEY_PUSH == 0) keyval = KeyPush;
		if(KEY_RIGHT == 0) keyval = KeyRight;
	}
	else if(KEY_LEFT == 1 && KEY_PUSH == 1 && KEY_RIGHT == 1 && key_up == 0){
		key_up = 1;
	}
	
	return keyval;
}
