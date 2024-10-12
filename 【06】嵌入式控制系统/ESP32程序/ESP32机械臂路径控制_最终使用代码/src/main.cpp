/*
 * @Author: ChenJiaChen
 * @Date: 2023-12-05 15:07:51
 * @LastEditors: ChenJiaChen
 * @LastEditTime: 2024-02-21 20:42:57
 * @FilePath: \esp32_I2C2udp\src\main.cpp
 * @Description: 用于将串口数据发送至UDP客户端
 */

#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <stdio.h>

#define BufReceiveSize 40
#define BUFFER_SIZE 4 * sizeof(uint32_t) + 10

#define I2C_DEV_ADDR  0x01


static const uint8_t sda_pin = 4;
static const uint8_t scl_pin = 5;

const char *ssid = "CJC141";
const char *password = "12345678";
int i = 0;
uint32_t orderIndex; // UDP接收到的指令

WiFiUDP Udp;
IPAddress remote_IP(192, 168, 137, 1); // 远程监 IP 地址
unsigned int remoteUdpPort = 8080;     // 远程监听端口pc端口

uint32_t ReceiveBuf[BufReceiveSize];
char Sendbuffer[BUFFER_SIZE];
char incomingPacket[8];
char SendtoPCbuffer[8];
// uint32_t I2CSendbuf[2] = {365,24};//测试I2C发送指令
uint8_t I2CReceiveBuf[8];
/*I2C指令表

*/

uint8_t singalframe;
uint8_t Numframe = 40;
// uint16_t endframe;
uint32_t TmpCount = 0;

// void onRequest(){
//   Serial.println("onRequest");
// }

// void OnReceive(int count){
//   Serial.println("onReceive");
//   for(int i = 0; i < count; i++)
//   {
//     I2CReceiveBuf[i] = Wire.read();
//   }
// }



void setup()
{

  /*串口0为调试串口，串口1为数据转换串口*/
  Serial.begin(230400);
  // Serial1.begin(115200);
  Serial.setDebugOutput(true);

  
  Serial1.begin(230400, SERIAL_8N1, /*rx =*/1, /*Tx =*/0);
  
  // /*I2C从机初始化*/
  // Wire.onReceive(OnReceive);
  // Wire.onRequest(onRequest);//当被需要接收数据时接收中断回调函数，slaveread

  /*I2C主机初始化*/


  
  Serial.println("Init_I2c");
  
  while (!Wire.begin(sda_pin, scl_pin, 100000)){
    delay(100);
    Serial.println("I2C device loading...");
  }
  //                                sda,scl
  delay(100);
  // Wire.setClock(100000); // 设置I2C时钟频率
  // Wire.begin(I2C_DEV_ADDR);
  
  

  /*WIFI初始化*/
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false); // 关闭STA模式下wifi休眠，提高响应速度
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.print("Connected, IP Address: ");
  Serial.println(WiFi.localIP());
  // 打印WiFiUDP本地端口与IP

  Udp.beginPacket(remote_IP, remoteUdpPort); // 配置远端ip地址和端口
  Udp.print("nihao\n");
  Udp.endPacket(); // 发送数据

}

void loop()
{
  // Serial.println(Serial1.available());
  /*每次串口接收40个整数，接收完了再一并向外转发*/
  if (Serial1.available() >= 0)
  {

    Serial1.readBytes((uint8_t *)&singalframe, sizeof(singalframe));
    Serial.print("frameis:");
    Serial.println(singalframe);
    // 解析singalframe的前16位是否为帧头和后16位代表的帧类型
    if (singalframe == 222) // 发送原生数据
    {
      // Serial1.readBytes((uint8_t *)&Numframe, sizeof(Numframe));
      Serial.println("发送数据");
      // Serial.println(Numframe);

      // Serial1.readBytesUntil(0xBBBB, (uint8_t *)ReceiveBuf, sizeof(ReceiveBuf));
      while (Serial1.available() >= sizeof(uint32_t) && TmpCount < Numframe )
      {
        Serial1.readBytes((uint8_t *)&ReceiveBuf[TmpCount], sizeof(uint32_t));
        TmpCount++;
      }
      
      Serial.println("发送数据2");
      
      // Wire.slaveWrite((uint8_t*)I2CSendbuf, sizeof(I2CSendbuf));
      
      TmpCount = 0;
      // Serial1.flush();

      // 打印接收到的数据
      Udp.beginPacket(remote_IP, remoteUdpPort); // 配置远端ip地址和端口
      for (i = 0; i < Numframe/4; i++)
      {
        sprintf(Sendbuffer, "%d\n%d\n%d\n%d\n", (uint16_t)ReceiveBuf[i * 4], (uint16_t)ReceiveBuf[i * 4 + 1],
                (uint16_t)ReceiveBuf[i * 4 + 2], (uint16_t)ReceiveBuf[i * 4 + 3]);
        // Serial.print(Sendbuffer);
        Udp.print(Sendbuffer); // 把数据写入发送缓冲区
        if(i == 4){
          Udp.endPacket(); // 发送数据
          Udp.beginPacket(remote_IP, remoteUdpPort); // 配置远端ip地址和端口
        }
        // 清空SendBuffer数组里的内容
      }
      Udp.endPacket(); // 发送数据
      
    }

    else if(singalframe == 208){
      Serial.println("发送数据33333");
      sprintf(SendtoPCbuffer, "%d\n", 0x43);
      Udp.beginPacket(remote_IP, remoteUdpPort); // 配置远端ip地址和端口
      Udp.print(SendtoPCbuffer);
      Udp.endPacket(); // 发送数据
    }
  }


  // if (Wire.available())
  // {
  //   //读取8byte数据
  //   for (int i = 0; i < 8; i++)
  //   {
  //     I2CReceiveBuf[i] = Wire.read();
  //   }
  //   Serial.println("收到i2c总线数据");
  // }

  

  //UDP数据检测
   Udp.beginPacket(remote_IP, remoteUdpPort); // 配置远端ip地址和端口
  // UDP接收主机数据并使用UDP发送回主机
  if ( Udp.parsePacket() )                      //如果有数据那么Data_length不为0，无数据Data_length为0
  {
    int len = Udp.read(incomingPacket, sizeof(incomingPacket));  //读取数据，将数据保存在数组incomingPacket中
    Serial.println("UDP数据接收成功");

    Wire.beginTransmission(12);  // 向从机发送数据
    Wire.write((uint8_t*)incomingPacket, sizeof(incomingPacket));
    Wire.endTransmission();  // 结束IIC通讯


    Serial1.print(incomingPacket);
    uint32_t data1,data2;
    // Serial.println(incomingPacket);
    //UDP发送接收字符
 
    /*UDP接收调试*/
    //data1为incomingPacket前4位组合而成的数
    data1 = ((uint32_t)incomingPacket[0] << 24) | ((uint32_t)incomingPacket[1] << 16) | ((uint32_t)incomingPacket[2] << 8) | (uint32_t)incomingPacket[3];
    //data2为incomingPacket后4位组合而成的数
    data2 = ((uint32_t)incomingPacket[4] << 24) | ((uint32_t)incomingPacket[5] << 16) | ((uint32_t)incomingPacket[6] << 8) | (uint32_t)incomingPacket[7];
    
    char UDPsendOutbuffer[20];
    sprintf(UDPsendOutbuffer,"data1:%d,data2:%d",data1,data2);
    Serial.println(UDPsendOutbuffer);
    
    



    Udp.print("receive:");

    // Udp.print(incomingPacket);                    // 把数据写入发送缓冲区
    
    Udp.print(UDPsendOutbuffer);                    // 把数据写入发送缓冲区
    // Udp.print("data1:");Udp.println(data1);
    
    
    // Udp.print("data2:");Udp.println(data2);

    Udp.endPacket(); // 发送数据
  }
  Udp.endPacket(); 
  // delay(500);
}