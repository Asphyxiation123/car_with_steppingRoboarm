/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "motor.h"
#include "linetracking.h"
#include "HC_SR04.h"
#include "delay.h"
#include "stdio.h"
#include "scheme.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern HCSR04 hcsr04;
extern Situ_InitTypeDef vechile1;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define INF1 HAL_GPIO_ReadPin(INF_port,INF_PIN_1)//右1
//#define INF2 HAL_GPIO_ReadPin(INF_port,INF_PIN_2)//右2
//#define INF3 HAL_GPIO_ReadPin(INF_port,INF_PIN_3)//左2
//#define INF4 HAL_GPIO_ReadPin(INF_port,INF_PIN_4)//左1
#define send_singal HAL_GPIO_WritePin(GoGo_GPIO_Port,GoGo_Pin,GPIO_PIN_SET)
#define close_singal HAL_GPIO_WritePin(GoGo_GPIO_Port,GoGo_Pin,GPIO_PIN_RESET)
#define START HAL_GPIO_ReadPin(Start_GPIO_Port,Start_Pin)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t flag_reach=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void getdistance(){
			if(hcsr04.STATE == TRIG_WAIT)
		{
			//给HCSR04一个50us触发电平
			HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_SET);
			Delay_us(20);			
			HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_RESET);
			
			//启动上升沿捕获
			__HAL_TIM_SET_CAPTUREPOLARITY(&HCSR04_TIM_HAL, HCSR04_TIM_CHANNEL, TIM_INPUTCHANNELPOLARITY_RISING);
			//启动输入捕获
			HAL_TIM_IC_Start_IT(&HCSR04_TIM_HAL, HCSR04_TIM_CHANNEL);	
			//设置上升沿捕获
			hcsr04.STATE = RISING;
		}
		
		if(hcsr04.STATE == OVER)//判断电平捕获结束
		{
			//计算高电平时间差值代表时间维持的长度，因为定时器设置1us自加一次，所以时长单位为us
			//乘以0.017的是因为声波速度为340m/s，而1s=1000000us，且记录一次距离是一个来回
			//要除以2，此处单位为cm
			hcsr04.len = (float)(hcsr04.buf[1]- hcsr04.buf[0])*0.017; 
			//刷新状态，使可以进行下一次触发电平
			hcsr04.STATE = TRIG_WAIT;
			//发送数据到上位机
			HAL_Delay(60);
	

		}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//char ch;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);  
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	
	OLED_Init();
	OLED_CLS();
	//STOP(0,100);
	uint8_t str1[10]="";
//	uint8_t str2[10]="";
//	uint8_t str3[10]="";
//	uint8_t str4[10]="";
//	uint8_t strdis[10]="";
	initilize_suit();
	//while(!START)

//	uint8_t a=0;
	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		sprintf ((char *)str1 ,"point:%d",vechile1.Trend);
//		sprintf ((char *)str2 ,"IO2:%d",INF2);
//		sprintf ((char *)str3 ,"IO3:%d",INF3);
//		sprintf ((char *)str4 ,"IO4:%d",INF4);
		OLED_ShowStr(0, 0, str1, 2);//显示字符串
//		OLED_ShowStr(0, 2, str2, 2);//显示字符串
//		OLED_ShowStr(0, 4, str3, 2);//显示字符串
//		OLED_ShowStr(0, 6, str4, 2);//显示字符串

		//getdistance();
		
//		if(hcsr04.len < 20.0)
//			STOP(0,20);	
//	else	
//	{
	//	 /*
		switch (vechile1.Trend)
		{
			case 0:
				while(!START)
				{
					STOP(0,500);
				}
				vechile1.Trend=1;
				break;
					
					
			case 1:
				line_follow();
				if(right90_check())
					{
						//STOP(0,2000);
						FORWARD(500,550);
						right_90(450,450,500);
						right_90turn();
						vechile1.Trend=2;
						//close_singal;
					}						
					break;
			case 2:
				line_follow();
				if( T_check() )
				{
					FORWARD(500,500);
					right_90(450,450,500);
					right_90turn();
					vechile1.Trend=3;		
				}
				break;
			case 3:
//				if( vechile1.turn_situ == 0  )
					circle_turn();
//				else if( vechile1.turn_situ ==1  )
//					line_follow();
				if( (right90_check() || T_check() ) && (vechile1.turn_situ==0) )
				{
					LEFTTURN(350,675,200);//左小转	 
					vechile1.turn_situ = 1;
				}
				
				else if( (right90_check() || T_check() ) && (vechile1.turn_situ==1) )
				{
					RIGHTTURN(520,450,650);
					right_90(450,450,650);
					right_90turn();	 
					vechile1.turn_situ = 0;
					vechile1.Trend=4;		
					//line_follow();
				}
				break;
				
			case 4:   //进到第一个路口抓物块
				line_follow();
				if( left90_check() )
					{
					FORWARD(500,530);
					left_90(450,450,300);
					left_90turn();
					vechile1.Trend=16;
					}
					break;
					
			case 16:
				line_follow_slowdown();
				if( T_check() )
				{
					FORWARD(300,250);
					STOP(0,500);
					send_singal;
					STOP(0,1000);
					close_singal;
					STOP(0,34000);
					vechile1.Trend=5;
				}
				break;
//			case 4:
//				line_follow();
//				if( T_check() )
//				{
//					STOP(0,2000);
//					vechile1.Trend=5;
//									
//				}
//				break;	
			case 5:
				BACK(350,2700);
				left_90(450,450,650);
				left_90turn();
				vechile1.Trend=7;	
				break;
				
//			case 6:
//				line_follow();
//				if( T_check() )
//				{
//					right_90turn();
//					vechile1.Trend=7;		
//				}
//				break;
//			case 6:
//				line_follow();
//			if( left90_check() )
//			{
//				FORWARD(500,480);
//				left_90(450,450,300);
//				left_90turn();
//			}
//			if( T_check() ){
//				STOP(0,3000);
//				
//				vechile1.Trend=7;
//			}
//			break;
			
			
			case 7:
//			BACK(350,1000);
//			left_90(450,450,300);
//			left_90turn();
				line_follow();
				if( T_check() )
				{
					FORWARD(500,540);
					right_90(450,450,2);
					right_90turn();
					vechile1.Trend=8;		
				}
				break;
			case 8:
					circle_turn();
				if( (right90_check() || T_check() ) && (vechile1.turn_situ==0) )
				{
					LEFTTURN(350,670,150);//左小转	 
					vechile1.turn_situ = 1;
				}
				if( (right90_check() || T_check() ) && (vechile1.turn_situ==1) )
				{
					RIGHTTURN(520,450,650);
					right_90(450,450,650);
					right_90turn();	 
					vechile1.turn_situ = 0;
					vechile1.Trend=9;	
				}
				break;
				
			case 9:
				line_follow();
			if( left90_check() )
			{
				FORWARD(500,520);
				left_90(450,450,500);
				left_90turn();
				vechile1.Trend=10;
			}
				break;
			case 10:
				line_follow();
			if( T_check() )//放物块
				{
					STOP(0,500);
					send_singal;
					STOP(0,1000);
					close_singal;
					STOP(0,26000);
					
					vechile1.Trend=11;					
				}
				break;
			case 11:
				BACK(350,500);
				if( right_180turn() )
				{
//					if(vechile1.round_count==1){
//						vechile1.Trend=11;
//						vechile1.round_count++;
//					}
//					else if(vechile1.round_count==2)
//					{
						vechile1.Trend=13;
//					}
				}
				break;
//			case 12:
//				
//				line_follow();
//				if(T_check())
//				{
//					FORWARD(500,530);
//					left_90(450,450,500);
//					left_90turn();
//					vechile1.Trend=2;
//				}	
//				break;
			
			case 13:
				line_follow();
				if( T_check() )
				{
					FORWARD(500,500);
					left_90(450,450,500);
					left_90turn();
					vechile1.Trend=14;
				}
			break;
			case 14:
				line_follow();
				if(left90_check())
					{
						FORWARD(500,530);
						left_90(450,450,500);
						left_90turn();
						vechile1.Trend=15;
					}
				
			case 15:
				line_follow();
			if( T_check() )
				{
					STOP(0,500);
					
				}
				break;
				
			}
	//		*/
				
////		sprintf ((char *)strdis ,"dis:%.3f",hcsr04.len);
////		OLED_ShowStr(0, 3, strdis, 2);//显示字符串
//		
////		while(hcsr04.len<30){
////			
////			STOP(0,100);
////			sprintf ((char *)str4 ,"dis:%.3f",hcsr04.len);
////			getdistance();
////			
////		}
//	
				
				//dongyidong();
//		}
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
