#ifndef __SCHEME_H
#define __SCHEME_H

#include "linetracking.h"
#include "motor.h"
#include "stm32f1xx_hal.h"
typedef	struct	//车辆状态Situation
{
	uint8_t Trend;     	/*当前命令：	
															送料未开始 =0
															前往右转路口1 = 1
															前往T形路口1 	= 2
															大转轮 =        3
															待停车取料	= 4
															已取料返回	=5
															进入大圆盘  =6
															大圆盘    =7
															初始通道	=8
															到达卸料口卸料	=9
															返回	=10
	
															到达T路口T1.2，准备再走一圈  =11
															前往T路口T1.2，准备回家 =12
															到达起点T路口，准备回家	=13
															到家，转弯回到原点，准备接受下
															
	
	
	
	*/

//  uint8_t speed;       /*告知总台速度*/
//  uint16_t distance;        /*总路程*/ 

  uint8_t turn_situ;  /*	在T路口周边的位置Flag	
											下个路口不转=0
											下个路口转  =1
	*/
	uint8_t round_count;/*	用于计数所走圈数	
											
	*/
	
	
} Situ_InitTypeDef; 

void initilize_suit(void);
#endif
