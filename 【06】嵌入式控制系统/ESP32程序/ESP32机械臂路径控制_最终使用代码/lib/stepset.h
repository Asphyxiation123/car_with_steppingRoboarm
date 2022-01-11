#ifndef STEPSET_H
#define STEPSET_H
#include"Arduino.h"
#include <AccelStepper.h>
const int enablePin = 12; //8;  // 使能控制引脚
 
const int xdirPin  = 15;  //5;     // x方向控制引脚
const int xstepPin = 26;  //2;     // x步进控制引脚
const int ydirPin  = 27;  //6;     // y方向控制引脚
const int ystepPin =25;   //3  // y步进控制引脚

const int zdirPin  = 33;  //7   // z方向控制引脚
const int zstepPin = 5;  //4  // z步进控制引脚

// const int zdirPin  = 18;  //13   // z方向控制引脚
// const int zstepPin = 19;  //12  // z步进控制引脚

void Motor_Setup();

void motor_run(int16_t deg1 , int16_t deg2 , int16_t deg3);
void motor_autorun(float deg1 , float deg2 , float deg3);
void motor_return_to_zero();
int16_t deg2steps(int16_t deg);
int16_t deg2stepsf(float deg);

float position_count(int32_t steps);
int32_t get_postion1();
int32_t get_postion2();
int32_t get_postion3();

#endif