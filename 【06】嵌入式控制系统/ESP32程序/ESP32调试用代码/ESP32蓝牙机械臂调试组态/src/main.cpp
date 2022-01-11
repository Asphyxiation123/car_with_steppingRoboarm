#include <Arduino.h>

/* *****************************************************************

   Download latest Blinker library here:
   https://github.com/blinker-iot/blinker-library/archive/master.zip


   Blinker is a cross-hardware, cross-platform solution for the IoT.
   It provides APP, device and server support,
   and uses public cloud services for data transmission and storage.
   It can be used in smart home, data monitoring and other fields
   to help users build Internet of Things projects better and faster.

   Make sure installed 2.7.4 or later ESP8266/Arduino package,
   if use ESP8266 with Blinker.
   https://github.com/esp8266/Arduino/releases

   Make sure installed 1.0.5 or later ESP32/Arduino package,
   if use ESP32 with Blinker.
   https://github.com/espressif/arduino-esp32/releases

   Docs: https://diandeng.tech/doc


 * *****************************************************************

   Blinker 库下载地址:
   https://github.com/blinker-iot/blinker-library/archive/master.zip

   Blinker 是一套跨硬件、跨平台的物联网解决方案，提供APP端、设备端、
   服务器端支持，使用公有云服务进行数据传输存储。可用于智能家居、
   数据监测等领域，可以帮助用户更好更快地搭建物联网项目。

   如果使用 ESP8266 接入 Blinker,
   请确保安装了 2.7.4 或更新的 ESP8266/Arduino 支持包。
   https://github.com/esp8266/Arduino/releases

   如果使用 ESP32 接入 Blinker,
   请确保安装了 1.0.5 或更新的 ESP32/Arduino 支持包。
   https://github.com/espressif/arduino-esp32/releases

   文档: https://diandeng.tech/doc


 * *****************************************************************/



#define BLINKER_BLE  
// #define BLINKER_WIFI
#define LED_BUILTIN 2

#include <../lib/Blinker/src/Blinker.h>
#include <../lib/stepset.h>
#include <../lib/AccelStepper/src/AccelStepper.h>
#include <Servo.h>

// char auth[] = "bb6d24dd3582";
// char ssid[] = "konodioda";
// char pswd[] = "23333333";

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 



// 新建组件对象
BlinkerButton Button1( (char*)"key1" );
BlinkerButton Buttonre0( (char*)"btn-0" );
BlinkerButton Bjiada( (char*)"jiada" );
BlinkerButton Bjiaxiao( (char*)"jiaxiao" );

//BlinkerNumber Num1( (char*)"num-1" );
BlinkerNumber Num_D1( (char*)"num-D1" );
BlinkerNumber Num_D2( (char*)"num-D2" );
BlinkerNumber Num_D3( (char*)"num-D3" );

BlinkerSlider bar1( (char*)"bar1" );
BlinkerSlider bar2( (char*)"bar2" );
BlinkerSlider bar3( (char*)"bar3" );

int16_t D1=0;int16_t D2=0;int16_t D3=0;
int16_t record_D1;int16_t record_D2;int16_t record_D3;
bool button_on_flag = 0;
bool button_re0_flag = 0;
bool close_flag = 0;
//char state_axis[]="";




void bar1_callback(int32_t value)
{
  D1=value;
    //Num_D1.print(D1);
}
void bar2_callback(int32_t value)
{
  D2=value;
  //Num_D2.print(D2);
}
void bar3_callback(int32_t value)
{
  D3=value;
  //Num_D3.print(D3);
}



// 按下按键即会执行该函数
void button1_callback(const String & state)
{
    if (state=="on") {
        //digitalWrite(LED_BUILTIN, HIGH);
        // 反馈开关状态
        record_D1=D1;
        record_D2=D2;
        record_D3=D3;
        button_on_flag=1;
        Button1.print("on");
        
    } else if(state=="off"){
        //digitalWrite(LED_BUILTIN, LOW);
        // 反馈开关状态
        //Blinker.vibrate();
        button_on_flag=0;
        Button1.print("off");
    }
    
}
///*
void bjiaxiao_callback(const String & state)
{
    if (state=="on") {
        //digitalWrite(LED_BUILTIN, HIGH);
        // 反馈开关状态
        myservo.write(0);
        Bjiaxiao.print("on");
        
    } else if(state=="off"){
        //digitalWrite(LED_BUILTIN, LOW);
        // 反馈开关状态
        
        //myservo.write(75);
        close_flag=1;
        Bjiaxiao.print("off");
    }
    
}

void bjiada_callback(const String & state)
{
    if (state=="on") {
        //digitalWrite(LED_BUILTIN, HIGH);
        // 反馈开关状态
        myservo.write(37);
        Bjiada.print("on");
        
    } else if(state=="off"){
        close_flag=1;
        //myservo.write(75);
        Bjiada.print("off");
    }
    
}
//*/

void buttonre0_callback(const String & state)
{
  button_re0_flag=1;
}


void setup()
{
  BLINKER_DEBUG.stream(Serial);
  BLINKER_DEBUG.debugAll();


  // 初始化串口
  Blinker.begin();
  Serial.begin(115200);
  // Blinker.begin(auth, ssid, pswd);
  // Blinker.connect();
  // delay(1000);

  // 初始化有LED的IO
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // 初始化blinker
  Motor_Setup();
  
  myservo.attach(18);  // attaches the servo on pin 4 to the servo object 


  Button1.attach(button1_callback);
  Buttonre0.attach(buttonre0_callback);
  // Bjiada.attach(bjiada_callback);
  // Bjiaxiao.attach(bjiaxiao_callback);

  bar1.attach(bar1_callback);
  bar2.attach(bar2_callback);
  bar3.attach(bar3_callback);
  
}

void loop() {
  Blinker.run();
  motor_run(D1,D2,D3);
  if(button_re0_flag==1)
  {
    motor_return_to_zero();
    button_re0_flag=0;
  }

  else
    {
      if(button_on_flag==0)
      {
        motor_run(D1,D2,D3);
        if(close_flag==1){
       //   myservo.write(75);
          close_flag=0;
        }
      }
      else 
      {
       motor_autorun(record_D1,record_D2,record_D3);
      }
    }
    Num_D1.print( D1 );
    Num_D2.print( D2 );
    Num_D3.print( D3 );
  
}