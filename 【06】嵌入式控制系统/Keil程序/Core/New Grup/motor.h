#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "main.h"

//电机运动函数
void LEFTTURN(int C_COUNTER_L,int C_COUNTER_R,int TIME_L);    /* 左转函数-变量为占空比数值，占空比= C_COUNTER/1000, TIME_L为左转需要的时间*/
void RIGHTTURN(int C_COUNTER,int C_COUNTER_R,int TIME_R);     /* 右转函数-变量为占空比数值，占空比= C_COUNTER/1000, TIME_R为右转需要的时间*/
void FORWARD(int C_COUNTE , int TIME);      /* 前进函数-变量为占空比数值，占空比= C_COUNTER/1000, TIME_F为函数运行的时间*/
void BACK(int C_COUNTE , int TIME);           /* 后退函数-变量为占空比数值，占空比= C_COUNTER/1000, TIME_B为函数运行的时间*/
void STOP(int C_COUNTER,int TIME);           /* 制动函数-变量为占空比数值，占空比= C_COUNTER/1000, TIME_S为函数运行的时间*/
void left_90(int C_COUNTER_L,int C_COUNTER_R,int TIME);
void right_90(int C_COUNTER_L,int C_COUNTER_R,int TIME);
void rotate_180(int C_COUNTER_L,int C_COUNTER_R,int TIME);
	//  电机接口IO口分配
//左电机的两个IO分配
//左电机1号IO
#define LEFT_MOTOR_PIN             GPIO_PIN_4      
#define LEFT_MOTOR_GPIO            GPIOA

//右电机的两个IO分配
//右电机1号IO
#define RIGHT_MOTOR_PIN             GPIO_PIN_10
#define RIGHT_MOTOR_GPIO            GPIOB





















#endif

