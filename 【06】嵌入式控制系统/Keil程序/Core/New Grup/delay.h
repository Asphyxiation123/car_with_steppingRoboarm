#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f1xx.h"

/**************************** 获取内核时钟频率 ***********************************/
/*函数HAL_RCC_GetSysClockFreq()的作用是获取当前的SYSCLK时钟频率,在cubemx里时钟
树的配置里，你完全可以看到SYSCLK这一项，在这里，其值就是72MHz，数值就是72000000，
但若本延时函数不是在HAL库下使用的，则是没有HAL_RCC_GetSysClockFreq()这个函数的，
所以你要自己手敲SYSCLK时钟频率是多少。
*/
#define HAL_delay 1 //若是HAL库，则宏定义为1，否则为0
#if HAL_delay

#define GET_CPU_ClkFreq()       HAL_RCC_GetSysClockFreq()

#else

#define GET_CPU_ClkFreq()       (72000000)//若不是HAL库，这里要写对SYSCLK的时钟频率

#endif

/***********************************************************************************/


/* 为方便使用，在延时函数内部调用Delay_Init函数初始化时间戳寄存器，但这样每次
调用延时函数都会初始化寄存器一遍。但若只想初始化一遍，节省点时间，则把本宏值设
置为0，但需要在main函数刚运行时调用Delay_Init函数初始化一下时间戳寄存器。*/  
#define CPU_TS_INIT_IN_DELAY_FUNCTION   1  


/*******************************************************************************
 * 函数声明
 ******************************************************************************/
uint32_t CPU_TS_TmrRd(void);//读取当前时间戳
void Delay_Init(void);//初始化时间戳寄存器

//使用以下函数前必须先调用Delay_Init函数使能计数器，或使能宏CPU_TS_INIT_IN_DELAY_FUNCTION
//最大延时值为2^32/(SYSCLK的值)秒，在这里是2^32/72000000=59.6523(s)
void Delay_us(uint32_t us);

#define HAL_Delay(ms)     Delay_us(ms*1000)

#endif /* __DELAY_H */

