#include <../lib/stepset.h>
#include <Arduino.h>
AccelStepper stepper1(1,xstepPin,xdirPin);//建立步进电机对象1
AccelStepper stepper2(1,ystepPin,ydirPin);//建立步进电机对象2
AccelStepper stepper3(1,zstepPin,zdirPin);//建立步进电机对象3

void Motor_Setup() {
  
  pinMode(xstepPin,OUTPUT);     // Arduino控制A4988x步进引脚为输出模式
  pinMode(xdirPin,OUTPUT);      // Arduino控制A4988x方向引脚为输出模式
  pinMode(ystepPin,OUTPUT);     // Arduino控制A4988y步进引脚为输出模式
  pinMode(ydirPin,OUTPUT);      // Arduino控制A4988y方向引脚为输出模式
  pinMode(zstepPin,OUTPUT);     // Arduino控制A4988z步进引脚为输出模式
  pinMode(zdirPin,OUTPUT);      // Arduino控制A4988z方向引脚为输出模式
  //pinMode(outPin,INPUT);
  
  pinMode(enablePin,OUTPUT);   // Arduino控制A4988使能引脚为输出模式
  digitalWrite(enablePin,LOW); // 将使能控制引脚设置为低电平从而让
                               // 电机驱动板进入工作状态
                                
  stepper1.setMaxSpeed(5500.0);     // 设置电机最大速度300 
  stepper1.setAcceleration(1200.0);  // 设置电机加速度20.0  
  stepper2.setMaxSpeed(4500.0);     // 设置电机最大速度300 
  stepper2.setAcceleration(1000.0);  // 设置电机加速度20.0 
  stepper3.setMaxSpeed(4000.0);     // 设置电机最大速度300 
  stepper3.setAcceleration(800.0);  // 设置电机加速度20.0 
}

void motor_autorun(float deg1 ,float deg2,float deg3){
  int16_t moveSteps1 = deg2stepsf(deg1);
  int16_t moveSteps2 = -deg2stepsf(deg2);
  int16_t moveSteps3 = -deg2stepsf(deg3);

  if ( stepper1.currentPosition() != moveSteps1 ){ 
    stepper1.moveTo(moveSteps1);              
  } 
  else if ( stepper1.currentPosition() == moveSteps1  ){
    stepper3.moveTo(0);            
  } 
  
  // 控制步进电机2往复运动
  if ( stepper2.currentPosition() != moveSteps2 ){ 
    stepper2.moveTo(moveSteps2);              
  }   
  else if ( stepper1.currentPosition() == moveSteps2  ){
    stepper2.moveTo(0);            
  } 
          
  // 控制步进电机3往复运动
  if ( stepper3.currentPosition() != moveSteps3 ){ 
    stepper3.moveTo(moveSteps3);              
  } 
  else if ( stepper3.currentPosition() == moveSteps3  ){
    stepper3.moveTo(0);            
  }    
  
  stepper1.run();   // 1号电机运行
  stepper2.run();   // 2号电机运行
  stepper3.run();   // 3号电机运行


}
void motor_run(int16_t deg1,int16_t deg2,int16_t deg3)
{
    int16_t steps1 =  deg2steps(deg1);
    int16_t steps2 = -deg2steps(deg2);
    int16_t steps3 = -deg2steps(deg3);
    
                
  if ( stepper1.currentPosition() !=steps1 ){ 
    stepper1.runToNewPosition(steps1);               
  }   
  
  // 控制步进电机2运动
 
    if ( stepper2.currentPosition() !=steps2 ){ 
    stepper2.runToNewPosition(steps2);               
  }                
  
          
  // 控制步进电机3运动
    if ( stepper3.currentPosition() !=steps3 ){ 
    stepper3.runToNewPosition(steps3);               
  }             
    
  
  stepper1.run();   // 1号电机运行
  stepper2.run();   // 2号电机运行
  stepper3.run();   // 3号电机运行
}

void motor_return_to_zero()
{
  if ( stepper1.currentPosition() != 0 )
  { 
    stepper1.runToNewPosition(0);              
  }
  // 控制步进电机2归零
  if ( stepper2.currentPosition() != 0 )
  { 
    stepper2.runToNewPosition(0);              
  }      
  // 控制步进电机3归零
  if ( stepper3.currentPosition() != 0 )
  { 
    stepper3.runToNewPosition(0);              
  }  
}

int16_t deg2steps(int16_t deg)
{
  int16_t steps;
  steps = int16_t( deg*16.9+0.5 );
  return steps; 
}

int16_t deg2stepsf(float deg)
{
  int16_t steps;
  steps = int16_t( deg*16.9+0.5 );
  return steps; 
}




float position_count(int32_t steps)
{
  float out_degree;
  out_degree = steps*0.225*3.69;
  out_degree = ( ( int )( out_degree * 100 + 0.5 ) ) / 100.0;
  return out_degree;
}
// int32_t get_postion1()
// {
//   return stepper1.currentPosition();
// }

// int32_t get_postion2()
// {
//   return stepper2.currentPosition();
// }

// int32_t get_postion3()
// {
//   return stepper3.currentPosition();
// }

