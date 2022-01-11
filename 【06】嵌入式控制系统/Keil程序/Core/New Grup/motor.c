#include "motor.h"
#include "tim.h"
//左转函数
/*  注：电机输入IO口1表示正转，0表示反转
				PWM口输入0--1000值进行速度调节
*/

void LEFTTURN(int C_COUNTER_L,int C_COUNTER_R,int TIME_L)
{     //左电机
	 //HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);                                    //开启左电机的pwm调压
	 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, C_COUNTER_L);                    //设定左电机的占空比=C_COUNTER/1000
	 HAL_GPIO_WritePin(LEFT_MOTOR_GPIO , LEFT_MOTOR_PIN, GPIO_PIN_RESET); //左轮正转      /* 设定IO的值使左转电机正转或反转  */  

		//右电机
	//	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);                                   //开启右电机的pwm调压 
	 __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, C_COUNTER_R*1.2);                     //设定右电机的占空比=C_COUNTER/1000
	 HAL_GPIO_WritePin(RIGHT_MOTOR_GPIO, RIGHT_MOTOR_PIN, GPIO_PIN_RESET);        /* 设定IO的值使右转电机正转或反转  */ 
	//设定运行时间
	   HAL_Delay(TIME_L);
	
//	   HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_2);    //关闭左电机的pwm输出，防止怠速运行
//	   HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);    //关闭右电机的pwm输出，防止怠速运行
}



//右转函数

void RIGHTTURN(int C_COUNTER_L,int C_COUNTER_R,int TIME_R)
{     //左电机
    // HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);                                    //开启左电机的pwm调压
		 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, C_COUNTER_L);                    //设定左电机的占空比=C_COUNTER/1000
     HAL_GPIO_WritePin(LEFT_MOTOR_GPIO , LEFT_MOTOR_PIN, GPIO_PIN_RESET);       /* 设定IO的值使左转电机正转或反转  */  
	
	    //右电机
	  //  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);                                   //开启右电机的pwm调压 
		 __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, C_COUNTER_R*1.12);                     //设定右电机的占空比=C_COUNTER/1000
     HAL_GPIO_WritePin(RIGHT_MOTOR_GPIO, RIGHT_MOTOR_PIN, GPIO_PIN_RESET);        /* 设定IO的值使右转电机正转或反转  */ 
	//设定运行时间
	   HAL_Delay(TIME_R);
	
//	   HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_2);    //关闭左电机的pwm输出，防止怠速运行
//	   HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);    //关闭右电机的pwm输出，防止怠速运行

}



//前进函数

void FORWARD(int C_COUNTER,int TIME)
{     //左电机
     //HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);                                    //开启左电机的pwm调压
		 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, C_COUNTER);                    //设定左电机的占空比=C_COUNTER/1000
     HAL_GPIO_WritePin(LEFT_MOTOR_GPIO , LEFT_MOTOR_PIN, GPIO_PIN_RESET);       /* 设定IO的值使左转电机正转或反转  */  
	
	    //右电机
	 //  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);                                   //开启右电机的pwm调压 
		 __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, C_COUNTER*1.12);                     //设定右电机的占空比=C_COUNTER/1000
     HAL_GPIO_WritePin(RIGHT_MOTOR_GPIO, RIGHT_MOTOR_PIN, GPIO_PIN_RESET);        /* 设定IO的值使右转电机正转或反转  */ 
	//设定运行时间
	   HAL_Delay(TIME);
	
	  // HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_2);    
	  // HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);    //关闭左右电机的pwm输出，防止怠速运行
}


//后退函数


void BACK(int C_COUNTER,int TIME)
{     //左电机
     //HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);                                    //开启左电机的pwm调压
		 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, C_COUNTER);                    //设定左电机的占空比=C_COUNTER/1000
     HAL_GPIO_WritePin(LEFT_MOTOR_GPIO , LEFT_MOTOR_PIN, GPIO_PIN_SET);       /* 设定IO的值使左转电机正转或反转  */  
	
	    //右电机
	 //  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);                                   //开启右电机的pwm调压 
		 __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, C_COUNTER*1.12);                     //设定右电机的占空比=C_COUNTER/1000
     HAL_GPIO_WritePin(RIGHT_MOTOR_GPIO, RIGHT_MOTOR_PIN, GPIO_PIN_SET);        /* 设定IO的值使右转电机正转或反转  */ 
	//设定运行时间
	   HAL_Delay(TIME);
	
	  // HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_2);    
	  // HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);    //关闭左右电机的pwm输出，防止怠速运行
}



//制动函数

void STOP(int C_COUNTER,int TIME)
{     //左电机
	//HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);     //开启左电机的pwm调压	  
	//HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);     //开启右电机的pwm调压     
                          
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, C_COUNTER);   //设定左电机的占空比=C_COUNTER/1000	
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, C_COUNTER);   //设定右电机的占空比=C_COUNTER/1000
	 HAL_Delay(TIME);
	// HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_2);    //关闭左电机的pwm输出，防止怠速运行
	 //HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);    //关闭右电机的pwm输出，防止怠速运行
}
void left_90(int C_COUNTER_L,int C_COUNTER_R,int TIME)
{     //左电机
	//HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);     //开启左电机的pwm调压	  
	//HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);     //开启右电机的pwm调压     
  HAL_GPIO_WritePin(LEFT_MOTOR_GPIO , LEFT_MOTOR_PIN, GPIO_PIN_SET); //左轮反转      /* 设定IO的值使左转电机正转  */  
	HAL_GPIO_WritePin(RIGHT_MOTOR_GPIO, RIGHT_MOTOR_PIN, GPIO_PIN_RESET);        /* 设定IO的值使右转电机正转  */ 
	
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, C_COUNTER_L);   //设定左电机的占空比=C_COUNTER/1000	
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, C_COUNTER_R*1.12);   //设定右电机的占空比=C_COUNTER/1000

	HAL_Delay(TIME);
	// HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_2);    //关闭左电机的pwm输出，防止怠速运行
	 //HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);    //关闭右电机的pwm输出，防止怠速运行
}
void right_90(int C_COUNTER_L,int C_COUNTER_R,int TIME)
{     //左电机
	//HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);     //开启左电机的pwm调压	  
	//HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);     //开启右电机的pwm调压     
  HAL_GPIO_WritePin(LEFT_MOTOR_GPIO , LEFT_MOTOR_PIN, GPIO_PIN_RESET); //左轮反转      /* 设定IO的值使左转电机正转  */  
	HAL_GPIO_WritePin(RIGHT_MOTOR_GPIO, RIGHT_MOTOR_PIN, GPIO_PIN_SET);        /* 设定IO的值使右转电机正转  */ 
                        
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, C_COUNTER_L);   //设定左电机的占空比=C_COUNTER/1000	
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, C_COUNTER_R);   //设定右电机的占空比=C_COUNTER/1000

	HAL_Delay(TIME);
	// HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_2);    //关闭左电机的pwm输出，防止怠速运行
	 //HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);    //关闭右电机的pwm输出，防止怠速运行
}

void rotate_180(int C_COUNTER_L,int C_COUNTER_R,int TIME)
{     //左电机
	//HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);     //开启左电机的pwm调压	  
	//HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);     //开启右电机的pwm调压     
  HAL_GPIO_WritePin(LEFT_MOTOR_GPIO , LEFT_MOTOR_PIN, GPIO_PIN_RESET); //左轮反转      /* 设定IO的值使左转电机正转  */  
	HAL_GPIO_WritePin(RIGHT_MOTOR_GPIO, RIGHT_MOTOR_PIN, GPIO_PIN_SET);        /* 设定IO的值使右转电机正转  */                         
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, C_COUNTER_L);   //设定左电机的占空比=C_COUNTER/1000	
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, C_COUNTER_R);   //设定右电机的占空比=C_COUNTER/1000

	HAL_Delay(TIME);
	// HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_2);    //关闭左电机的pwm输出，防止怠速运行
	 //HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);    //关闭右电机的pwm输出，防止怠速运行
}



