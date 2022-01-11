/***************************************************************************************************
*			代码来源：https://blog.csdn.net/qq_45396672/article/details/119619269?spm=1001.2014.3001.5501
*	辅助参考资料：https://blog.csdn.net/as480133937/article/details/99407485（HAL库下的定时器输入捕获设置）
* 				日期：2021年11月22日
****************************************************************************************************/

#include "HC_SR04.h"

//声明一个模块的数据结构体
HCSR04 hcsr04;
//重新编写输入捕获回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	
	if(htim->Instance == HCSR04_TIM)
	{
		//如果上升沿检测
		if(hcsr04.STATE == RISING)
		{
			//设置定时器CNT为0
			__HAL_TIM_SET_COUNTER(&HCSR04_TIM_HAL,0);
		  //读取上升沿时的CNT值到buf
			hcsr04.buf[0] = __HAL_TIM_GetCounter(&HCSR04_TIM_HAL);
			//设置下一个捕获为下降沿
			__HAL_TIM_SET_CAPTUREPOLARITY(&HCSR04_TIM_HAL,HCSR04_TIM_CHANNEL,TIM_ICPOLARITY_FALLING); 
			//改变运行模式
			hcsr04.STATE=FALLING;
		}else if(hcsr04.STATE == FALLING)//如果下降沿检测
		{
			//获取当前的CNT到buf2，这样高电平维持的时间长度就记录了
			hcsr04.buf[1] = __HAL_TIM_GetCounter(&HCSR04_TIM_HAL);
			//将运行标志设置为完成
			hcsr04.STATE=OVER; 
			
		}
	}
	
}
