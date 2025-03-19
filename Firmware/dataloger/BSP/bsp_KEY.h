#ifndef  _BSP_KEY_H
#define _BSP_KEY_H
#include "main.h"

enum {
	KeyLeft = 1,
	KeyPush,
	KeyRight
};

#define KEY_LEFT  HAL_GPIO_ReadPin(KEY_LEFT_GPIO_Port,KEY_LEFT_Pin)
#define KEY_PUSH	HAL_GPIO_ReadPin(KEY_PUSH_GPIO_Port,KEY_PUSH_Pin)
#define KEY_RIGHT	HAL_GPIO_ReadPin(KEY_RIGHT_GPIO_Port,KEY_RIGHT_Pin)

uint8_t key_scan(uint8_t mode);

#endif

