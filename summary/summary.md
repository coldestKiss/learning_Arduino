# <center>开源硬件实战总结</center>
>李煜楠  
>2019/07/02 - 2019/07/05  
___
## <center>第一天
* 认识开源硬件
* 常用软件及学习网站  
### 开源硬件  
* 开源硬件是指与自由及开放原始码软件相同方式设计的计算机和电子硬件。
### 常用软件及学习网站
1. Arduino —— [https://www.arduino.cc](https://www.arduino.cc)
2. Fritzing —— [http://fritzing.org/home/](http://fritzing.org/home/)
3. Processing —— [https://processing.org/](https://processing.org/)
4. Github —— [https://github.com/](https://github.com/)
___
## <center>第二天
* 开源硬件入门
* 用Arduino实现莫尔斯电码
### 开源硬件入门  
* 了解了Arduino UNO的结构  
![](/Markdown/summary/UNO结构图.jpg)
#### Serial  
0（RX）、1（TX）引脚，被用于接收和发送串口数据。这两个引脚通过连接到ATmega16u2来与计算机进行串口通信。  
#### 外部中断  
2、3引脚，可以输入外部中断信号。中断有四种触发模式：低电平触发、电平改变触发、上升沿触发、下降沿触发。  
#### PWM输出：  
3、5、6、9、10、11号引脚，可用于输出8-bit PWM波。对应函数 analogWrite().  
#### SPI：  
10（SS）、11（MOSI）、12（MISO）、13（SCK）引脚，可用于SPI通信。可以使用官方提供的SPI库操纵。  
#### L-LED：  
13号引脚连接了一个LED，当引脚输出高电平时打开LED，当引脚输出低电平时关闭LED。  
* Arduino编程语言  
掌握了`<Serial()>`, `<digtalWrite()>`,`<pinMode()>`等常用Arduino函数  
### Arduino实现莫尔斯电码
```C
/*
.ino文件
*/
#include <Morse.h>
 
Morse morse(13);
int incomingByte = 0;
 
void setup()
{
  Serial.begin(9600);
}

void loop(){
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    switch(incomingByte){
      case 97:morse.dot();morse.dash();morse.c_space();break;
      case 98:morse.dash();morse.dot();morse.dot();morse.dot();morse.c_space();break;
      case 99:morse.dash();morse.dot();morse.dash();morse.dot();morse.c_space();break;
      case 100:morse.dash();morse.dot();morse.dot();morse.c_space();break;
      case 101:morse.dot();morse.c_space();break;
      case 102:morse.dot();morse.dot();morse.dash();morse.dot();morse.c_space();break;
      case 103:morse.dash();morse.dash();morse.dot();morse.c_space();break;
      case 104:morse.dot();morse.dot();morse.dot();morse.dot();morse.c_space();break;
      case 105:morse.dot();morse.dot();morse.c_space();break;
      case 106:morse.dot();morse.dash();morse.dash();morse.dash();morse.c_space();break;
      case 107:morse.dash();morse.dot();morse.dash();morse.c_space();break;
      case 108:morse.dot();morse.dash();morse.dot();morse.dot();morse.c_space();break;
      case 109:morse.dash();morse.dash();morse.c_space();break;
      case 110:morse.dash();morse.dot();morse.c_space();break;
      case 111:morse.dash();morse.dash();morse.dash();morse.c_space();break;
      case 112:morse.dot();morse.dash();morse.dash();morse.dot();morse.c_space();break;
      case 113:morse.dash();morse.dash();morse.dot();morse.dash();morse.c_space();break;
      case 114:morse.dot();morse.dash();morse.dot();morse.c_space();break;
      case 115:morse.dot();morse.dot();morse.dot();morse.c_space();break;
      case 116:morse.dash();morse.c_space();break;
      case 117:morse.dot();morse.dot();morse.dash();morse.c_space();break;
      case 118:morse.dot();morse.dot();morse.dot();morse.dash();morse.c_space();break;
      case 119:morse.dot();morse.dash();morse.dash();morse.c_space();break;
      case 120:morse.dash();morse.dot();morse.dot();morse.dash();morse.c_space();break;
      case 121:morse.dash();morse.dot();morse.dash();morse.dash();morse.c_space();break;
      case 122:morse.dash();morse.dash();morse.dot();morse.dot();morse.c_space();break;
      case 32:morse.w_space();
    }
  }
}  
```
```C
/*
.cpp文件
*/
#include "Arduino.h"
#include "Morse.h"

Morse::Morse(int pin)
{
	pinMode(pin,OUTPUT);
	_pin=pin;
	_dottime=250;
}

void Morse::dot()
{
	digitalWrite(_pin,HIGH);
	delay(_dottime);
	digitalWrite(_pin,LOW);
	delay(_dottime);
}

void Morse::dash()
{
	digitalWrite(_pin,HIGH);
	delay(_dottime*4);
	digitalWrite(_pin,LOW);
	delay(_dottime);
}

void Morse::c_space()
{
	digitalWrite(_pin,LOW);
	delay(_dottime*3);
}

void Morse::w_space()
{
	digitalWrite(_pin,LOW);
	delay(_dottime*7);
}
```
```C
/*
.h文件
*/
#ifndef _MORSE_H
#define _MORSE_H
class Morse
{
  public:
    Morse(int pin);
    void dot();
    void dash();
    void c_space();
    void w_space();
  private:
    int _pin;
    int _dottime;
};
#endif /*_MORSE_H*/
```
___
## <center>第三天
* 汽车马达及车灯模拟
* 七段数码管数字显示模拟
### 汽车马达及车灯模拟
* 实现内容: 在串口监控窗  
输入w: 马达正向转动  
输入a: 马达一正一反转动, 亮左车灯  
输入d: 马达一反一正转动, 亮右车灯  
输入s: 马达反向转动, 车灯全亮
* 模拟图
![](/Markdown/summary/汽车马达及车灯模拟.png)
* 模拟程序
```C
int income = 0;

void setup()
{
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available() > 0)
  {
    income = Serial.read();
    switch(income)
    {
      case 'w':forward();break;
      case 'a':left();break;
      case 'd':right();break;
      case 's':backward();break;
    }
  }
}

void forward()
{
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}

void left()
{
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
}

void right()
{
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}

void backward()
{
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}
```
### 七段数码管数字显示模拟
* 实现内容: 将在串口监控窗输入的0~9显示在数码管上
* 难点: 学习七段数码管和CD4511的使用
* 模拟图
![](/Markdown/summary/七段数码管数字显示_模拟图.png)
* 模拟程序
```C
int income;

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(6, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  if(Serial.available() > 0)
  {
    income = Serial.read() - '0';
    if((income&1)==1)
      digitalWrite(2, HIGH);
    if((income>>1)&1==1)
      digitalWrite(3, HIGH);
    if((income>>2)&1==1)
      digitalWrite(4, HIGH);
    if((income>>3)&1==1)
      digitalWrite(5, HIGH);
    
    digitalWrite(6, HIGH);
    delay(1000);
  }  
}
```
___
## <center>第四天
* 将第二天的莫尔斯电码在tinkCAD上实现
### 莫尔斯电码的tinkCAD实现
* 实现内容: 在串口监控窗输入英文字母或空格,在13号接口上的LED灯输出对应的莫尔斯电码
* 难点: 将头文件中的变量定义和类提取转化为主文件中的变量和函数
* 模拟程序:
```C
int _pin = 13;
int _dottime = 250;


void dot()
{
	digitalWrite(_pin,HIGH);
	delay(_dottime);
	digitalWrite(_pin,LOW);
	delay(_dottime);
}

void dash()
{
	digitalWrite(_pin,HIGH);
	delay(_dottime*4);
	digitalWrite(_pin,LOW);
	delay(_dottime);
}

void c_space()
{
	digitalWrite(_pin,LOW);
	delay(_dottime*3);
}

void w_space()
{
	digitalWrite(_pin,LOW);
	delay(_dottime*7);
}

int incomingByte = 0;
 
void setup()
{
  pinMode(_pin, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    switch(incomingByte){
      case 97:dot();dash();c_space();break;
      case 98:dash();dot();dot();dot();c_space();break;
      case 99:dash();dot();dash();dot();c_space();break;
      case 100:dash();dot();dot();c_space();break;
      case 101:dot();c_space();break;
      case 102:dot();dot();dash();dot();c_space();break;
      case 103:dash();dash();dot();c_space();break;
      case 104:dot();dot();dot();dot();c_space();break;
      case 105:dot();dot();c_space();break;
      case 106:dot();dash();dash();dash();c_space();break;
      case 107:dash();dot();dash();c_space();break;
      case 108:dot();dash();dot();dot();c_space();break;
      case 109:dash();dash();c_space();break;
      case 110:dash();dot();c_space();break;
      case 111:dash();dash();dash();c_space();break;
      case 112:dot();dash();dash();dot();c_space();break;
      case 113:dash();dash();dot();dash();c_space();break;
      case 114:dot();dash();dot();c_space();break;
      case 115:dot();dot();dot();c_space();break;
      case 116:dash();c_space();break;
      case 117:dot();dot();dash();c_space();break;
      case 118:dot();dot();dot();dash();c_space();break;
      case 119:dot();dash();dash();c_space();break;
      case 120:dash();dot();dot();dash();c_space();break;
      case 121:dash();dot();dash();dash();c_space();break;
      case 122:dash();dash();dot();dot();c_space();break;
      case 32:w_space();
    }
  }
}
```
___
## <center>小结
我自身对开源硬件有很大的兴趣, 通过开源硬件实战这门课程, 我学会了如何学习开源硬件, 学会了如何通过学习一步步完成想要实现的目标, 虽然只有短短的四天,但我真的收获很大, 感谢老师和一起讨论问题的同学.