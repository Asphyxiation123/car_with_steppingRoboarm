#include "linetracking.h"
#include "motor.h"
#include "stm32f1xx_hal.h"


extern uint8_t flag_reach;
void linetrack(void)
{
	
 if(INF1==0 && INF2==1 && INF3==1 && INF4==0)
	       {
            FORWARD(450,10);//直行

         }

else if ( (INF1==0 && INF2==0 && INF3==1 && INF4==0)
         	)

         {
					 RIGHTTURN(500,350,10);//右小转
					 
				 }
else if ( (INF1==0 && INF2==0 && INF3==0 && INF4==1)
					||(INF1==0 && INF2==0 && INF3==1 && INF4==1))

         {
					 RIGHTTURN(650,370,10);//右da转
					 
				 } 				 
else if( (INF1==0 && INF2==1 && INF3==0 && INF4==0) )
   {
					 LEFTTURN(350,500,10);//左小转
					 
				 }

else if( (INF1==1 && INF2==0 && INF3==0 && INF4==0)
				||(INF1==1 && INF2==1 && INF3==0 && INF4==0) )
   {
					 LEFTTURN(350,680,10);//左da转
					 
				 }
else if(INF1==0 && INF2==0 && INF3==0 && INF4==0)
   {		
			STOP(0,100);
			BACK(350,400);
	 }
else if(INF1==1 && INF2==1 && INF3==1 && INF4==1)
   {	
		 STOP(0,50);//停转
		 
			if(INF1==1 && INF2==1 && INF3==1 && INF4==1){
					 STOP(0,50);//停转
					 flag_reach=1;
					HAL_GPIO_WritePin(led_GPIO_Port,led_Pin,GPIO_PIN_SET);
					rotate_180(420,420,3000);
				while( (INF1==0 && INF2==1 && INF3==1 && INF4==0) ==0 )
					rotate_180(420,420,10);
				}
		}
 	 
else if(INF1==1 && INF2==1 && INF3==1 && INF4==0)
   {
		 
		 STOP(0,50);//停转
		 if(INF1==1 && INF2==1 && INF3==1 && INF4==0)
   {
		 
		 while( (INF1==0 && INF2==1 && INF3==1 && INF4==0) ==0 )
					 left_90(330,580,10);
					 
		}
					 
		}
	 
//else if(INF1==0 && INF2==1 && INF3==1 && INF4==1)
//   {
//		 STOP(0,50);//停转
//		 if(INF1==0 && INF2==1 && INF3==1 && INF4==1)
//   {
//		 while( (INF1==0 && INF2==1 && INF3==1 && INF4==0) ==0 )
//					 right_90(550,400,10);
//					 
//		}
//	}

}


void line_follow(void)
{
if(INF1==0 && INF2==1 && INF3==1 && INF4==0)
		 {
				FORWARD(450,10);//直行
		 }

else if ( (INF1==0 && INF2==0 && INF3==1 && INF4==0) )
		 {
			 RIGHTTURN(590,350,10);//右小转			 
		 }
else if( (INF1==0 && INF2==0 && INF3==1 && INF4==1) )
		 {
			 FORWARD(500,300);
			 while( (INF1==0 && INF2==1 && INF3==1 && INF4==0) ==0 )
					 right_90(460,460,5);				
		 }
else if( (INF1==0 && INF2==1 && INF3==0 && INF4==0)  )
   {
			LEFTTURN(350,590,10);//左小转	 
		}
else if( (INF1==1 && INF2==1 && INF3==0 && INF4==0) )
	{
	//LEFTTURN(350,670,10);
		//FORWARD(500,300);
		while( (INF1==0 && INF2==1 && INF3==1 && INF4==0) ==0 ){			
			left_90(455,455,5);	
		}
	}
else if( INF1==0 && INF2==0 && INF3==0 && INF4==0 ){
			BACK(320,250);
	 }
//	else
//	{
//		HAL_Delay(2);
//	}
}




void left_90turn(void)
{

		// while( (INF1==0 && INF2==1 && INF3==1 && INF4==0) ==0 )
	 while( (INF1==0 && INF2==1 && INF3==1 && INF4==0) ==0 )	 
	{
				left_90(450,450,2);	 
					 
		}
}

void right_90turn(void)
{
	
		 
		 while( (INF1==0 && INF2==1 && INF3==1 && INF4==0) ==0 )
		 {
					 right_90(450,450,2);	 				 
		 }
}


void circle_turn(void)
{
	if(INF1==0 && INF2==1 && INF3==1 && INF4==0)
		 {
				FORWARD(420,2);//直行
		 }

else if ( (INF1==0 && INF2==0 && INF3==1 && INF4==0)
        ||(INF1==0 && INF2==0 && INF3==1 && INF4==1) )
		 {
			 RIGHTTURN(675,350,5);//右小转
			 
		 }
 else if( (INF1==0 && INF2==1 && INF3==0 && INF4==0) 
					||(INF1==1 && INF2==1 && INF3==0 && INF4==0) )
   {
			LEFTTURN(350,670,5);//左小转	 
		}
	 else if( INF1==0 && INF2==0 && INF3==0 && INF4==0 ){
			BACK(330,40);
	 }
}

uint8_t T_check(void)
{
	if(INF1==1 && INF2==1 && INF3==1 && INF4==1)
   {
		 
		 STOP(0,50);//停转
		 if(INF1==1 && INF2==1 && INF3==1 && INF4==1)
   {
		 
		return 1;
		}
	 else 
		 return 0;
	}
	 else 
		 return 0;
}

uint8_t left90_check(void)
{
	if(INF1==1 && INF2==1 && INF3==1 && INF4==0)
   {
		 
		 STOP(0,50);//停转
		 if(INF1==1 && INF2==1 && INF3==1 && INF4==0)
			{
			return 1;
			}
		else 
		 return 0;
	}
	 else 
		 return 0;
}


uint8_t right90_check(void)
{
	if(INF1==0 && INF2==1 && INF3==1 && INF4==1)
   {
		 
		 STOP(0,50);//停转
		 if(INF1==0 && INF2==1 && INF3==1 && INF4==1)
			{
			return 1;
			}
		else 
		 return 0;
	}
	 else 
		 return 0;
}

uint8_t right_180turn(void)
{
	right_90(440,440,800);
	while( (INF1==0 && INF2==1 && INF3==1 && INF4==0)==0 )
	{
		right_90(440,440,2);
	}
	return 1;
}

void line_follow_slowdown(void)
{
	if(INF1==0 && INF2==1 && INF3==1 && INF4==0)
		 {
				FORWARD(380,5);//直行
		 }

else if ( (INF1==0 && INF2==0 && INF3==1 && INF4==0) )
		 {
			 RIGHTTURN(490,340,10);//右小转			 
		 }
else if( (INF1==0 && INF2==0 && INF3==1 && INF4==1) )
		 {
			 FORWARD(500,300);
			 while( (INF1==0 && INF2==1 && INF3==1 && INF4==0) ==0 )
					 right_90(460,460,5);				
		 }
else if( (INF1==0 && INF2==1 && INF3==0 && INF4==0)  )
   {
			LEFTTURN(340,490,10);//左小转	 
		}
else if( (INF1==1 && INF2==1 && INF3==0 && INF4==0) )
	{
	//LEFTTURN(350,670,10);
		//FORWARD(500,300);
		while( (INF1==0 && INF2==1 && INF3==1 && INF4==0) ==0 ){			
			left_90(455,455,5);	
		}
	}
else if( INF1==0 && INF2==0 && INF3==0 && INF4==0 ){
			BACK(320,250);
	 }

}


uint8_t middle_check(void)
{
	if(INF1==0 && INF2==1 && INF3==1 && INF4==0)
   {
		 
		 HAL_Delay(20);//
		 if(INF1==0 && INF2==1 && INF3==1 && INF4==0)
			{
			return 1;
			}
		else 
		 return 0;
	}
	 else 
		 return 0;
}

void dongyidong(void)
{
		FORWARD(400,2000);
		BACK(400,2000);
		left_90(450,450,1000);
		right_90(450,450,1000);
}
