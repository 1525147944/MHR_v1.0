#ifndef _KEY_H
#define _KEY_H
#include "sys.h"

#define KEY1        HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)
#define KEY2        HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_11)

#define KEY1_PRES 1  //KEY0���º󷵻�ֵ
#define KEY2_PRES	2	//KEY1���º󷵻�ֵ


u8 KEY_Scan(u8 mode); //����ɨ�躯��

#endif
