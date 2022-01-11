#ifndef __LINETRACKING_H
#define __LINETRACKING_H
#include "stm32f1xx_hal.h"

#define INF_port    GPIOB
#define INF_PIN_1 GPIO_PIN_12
#define INF_PIN_2 GPIO_PIN_13
#define INF_PIN_3 GPIO_PIN_14
#define INF_PIN_4 GPIO_PIN_15


#define INF1 HAL_GPIO_ReadPin(INF_port,INF_PIN_1)//ÓÒ1
#define INF2 HAL_GPIO_ReadPin(INF_port,INF_PIN_2)//ÓÒ2
#define INF3 HAL_GPIO_ReadPin(INF_port,INF_PIN_3)//×ó2
#define INF4 HAL_GPIO_ReadPin(INF_port,INF_PIN_4)//×ó1

void linetrack(void);
void line_follow(void);
void right_90turn(void);
void left_90turn(void);
void circle_turn(void);

uint8_t T_check(void);
uint8_t left90_check(void);
uint8_t right90_check(void);
uint8_t right_180turn(void);
void line_follow_slowdown(void);

uint8_t middle_check(void);

void dongyidong(void);
#endif
