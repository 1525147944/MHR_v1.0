#ifndef _LED_H
#define _LED_H
#include "sys.h"

//LED�˿ڶ���
#define LED1(isOnLED)		(isOnLED?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET))
#define LED1_Toggle (HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0)) //LED0�����ƽ��ת
#define LED2(isOnLED)		(isOnLED?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_RESET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_SET))
#define LED2_Toggle (HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_3)) //LED1�����ƽ��ת

#endif
