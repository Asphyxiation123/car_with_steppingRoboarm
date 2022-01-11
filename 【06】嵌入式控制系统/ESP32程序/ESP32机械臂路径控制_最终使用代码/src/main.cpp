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



//#define BLINKER_BLE  
#define BLINKER_WIFI
#define LED_BUILTIN 2

#define outpin 4
#define getinpin1 23


#include <../lib/stepset.h>
#include <AccelStepper.h>
#include <Servo.h>

// char auth[] = "2fa0d2a306bf";
// char ssid[] = "konodioda";
// char pswd[] = "23333333";


Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 



//int16_t D1=0;int16_t D2=0;int16_t D3=0;
int16_t getbig_deg1[2] = {22,22};
int16_t getbig_deg2[2] = {47,75};
int16_t getbig_deg3[2] = {27,27};

int16_t savebig1_deg1[2] = {22,189};
int16_t savebig1_deg2[2] = {30,36};
int16_t savebig1_deg3[2] = {32,27};


int16_t getsmall_deg1[2] = {189,-23};
int16_t getsmall_deg2[2] = {8,107};
int16_t getsmall_deg3[2] = {16,11};


//int16_t savebig2_deg1;int16_t savebig2_deg2;int16_t savebig2_deg3;
int16_t savesmall1_deg1[2] = {-23,208};
int16_t savesmall1_deg2[2] = {0,22};
int16_t savesmall1_deg3[2] = {40,19};
//int16_t savesmall2_deg1;int16_t  savesmall2_deg2;int16_t  savesmall2_deg3;
int16_t put_deg1[3] = {208,-4,-4};
int16_t put_deg2[3] = {10,41,25};
int16_t put_deg3[3] = {45,11,35};

bool  button_on_flag=0;
bool  button_re0_flag=0;
uint8_t roboflag=2;
//char state_axis[]="";


// 按下按键即会执行该函数



void setup()
{

  Serial.begin(115200);
  //Blinker.begin(auth, ssid, pswd);
  
  // Blinker.connect();
  // delay(1000);

  // 初始化有LED的IO
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(outpin, OUTPUT);
  pinMode(getinpin1, INPUT);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(outpin, LOW);
  // 初始化blinker
  Motor_Setup();

  myservo.attach(18);  // attaches the servo on pin 9 to the servo object 
  myservo.write(78);
}

void loop() {

  if(digitalRead(getinpin1)==1){
    switch (roboflag)
    {
    case 1:
      while(digitalRead(getinpin1)==1)
      {
        digitalWrite(LED_BUILTIN,HIGH);
        delay(1000);
      }

      roboflag++;
      digitalWrite(LED_BUILTIN,LOW);
      break;

    case 2://取用物块

      while(digitalRead(getinpin1)==1)
      {
        digitalWrite(LED_BUILTIN,HIGH);
        //抓放大底盘
        motor_run(getbig_deg1[0],getbig_deg2[0],getbig_deg3[0]);//抓大底盘
        //delay(500);
        motor_run(getbig_deg1[1],getbig_deg2[1],getbig_deg3[1]);//抓大底盘
        //delay(500);
        myservo.write(37);
        delay(500);
        motor_run(savebig1_deg1[0],savebig1_deg2[0],savebig1_deg3[0]);//放大底盘
        //delay(500);
        motor_run(savebig1_deg1[1],savebig1_deg2[1],savebig1_deg3[1]);//放大底盘
        //delay(500);
        myservo.write(78);
        delay(500);

        //抓放小物块
        motor_run(getsmall_deg1[0],getsmall_deg2[0],getsmall_deg3[0]);//抓小物块
        //delay(500);
        motor_run(getsmall_deg1[1],getsmall_deg2[1],getsmall_deg3[1]);//抓小物块
        //delay(500);
        myservo.write(0);
        delay(500);
        motor_run(savesmall1_deg1[0],savesmall1_deg2[0],savesmall1_deg3[0]);//放小物块
        //delay(500);
        motor_run(savesmall1_deg1[1],savesmall1_deg2[1],savesmall1_deg3[1]);//放小物块
        //delay(500);
        myservo.write(78);
        delay(500);
        //motor_run(savesmall1_deg1[1],savesmall1_deg2[1]-4,savesmall1_deg3[1]);//收回一点






      }
      roboflag++;
      digitalWrite(LED_BUILTIN,LOW);
      break;

      case 3://放回物块

      while(digitalRead(getinpin1)==1)
      {

        //抓放小物块
        myservo.write(0);
        delay(500);
        motor_run(put_deg1[0],put_deg2[0],put_deg3[0]);//放小物块
      
        motor_run(put_deg1[1],put_deg2[1],put_deg3[1]);//放小物块
       
        myservo.write(77);
        delay(500);

     // motor_run(put_deg1[3],put_deg2[3],put_deg3[3]);//放大底盘
        //抓放大底盘
        motor_run(put_deg1[2],put_deg2[2],put_deg3[2]);//抓大底盘

        motor_run(savebig1_deg1[1],savebig1_deg2[1],savebig1_deg3[1]);//抓大底盘

        myservo.write(37);
        delay(500);
        motor_run(189,put_deg2[0],put_deg3[0]);//放大底盘
        motor_run(put_deg1[1],put_deg2[1],put_deg3[1]);//放大底盘
        myservo.write(77);
        delay(500);

        motor_return_to_zero();

        
      }
      digitalWrite(LED_BUILTIN,LOW);
        roboflag=4;
        break;

    default:
      break;
    }

    

  }
}