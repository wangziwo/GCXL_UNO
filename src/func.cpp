//
// Created by wang on 2021/3/13.
//

#include "header.h"


char val,buffer[5];
char info;
String buffer1,buffer2,buffer3;
//S23分别接43
//0ut接2
//8控制是否进行颜色识别
//led默认常量，加低电平熄灭
//红绿蓝分别在789输出高电平，反应速度在0.5秒左右
int   R=50; //颜色补偿，基准值为50，可上下波动约20
int   G=50;
int   B=50;

char temp;
int i;
int z=3;
int r=2;
int l=1;

int a=1,b=1;
#define OUT    2
#define S2     4
#define S3     7
float g_SF[4];
int   g_count = 0;
int   g_array[4];
int   m;
int   g_flag = 0;


void TSC_Init()
{
    Serial.begin(9600,SERIAL_8N1);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(OUT, INPUT);

}
//选择滤波器模式，决定让红、绿、蓝，哪种光线通过滤波器
void TSC_FilterColor(int Level01, int Level02)
{
    if(Level01 != 0)
        Level01 = HIGH;
    if(Level02 != 0)
        Level02 = HIGH;
    digitalWrite(S2, Level01);
    digitalWrite(S3, Level02);
}
void TSC_Count()
{
    g_count ++ ;
}
void TSC_WB(int Level0, int Level1)
{
    g_count = 0;   //计数值清零
    g_flag ++;     //输出信号计数标志
    TSC_FilterColor(Level0, Level1); //滤波器模式
    Timer1.setPeriod(100000);     //设置输出信号脉冲计数时长1s
}
//定时器中断函数，每1s中断后，把该时间内的红、绿、蓝三种光线通过滤波器时，
//TCS3200输出信号脉冲个数分别存储到数组g_array[3]的相应元素变量中
void TSC_Callback()
{
    switch(g_flag)
    {
        case 0:
            TSC_WB(LOW, LOW);   //选择让红色光线通过滤波器的模式
            break;
        case 1:
            g_array[1] = ((g_count+R)*0.9);    //存储1s内的红光通过滤波器时，TCS3200输出的脉冲个数
            Serial.print("R=");
            Serial.print((g_count+R)*0.9);
            TSC_WB(HIGH, HIGH);  //选择让绿色光线通过滤波器的模式
            break;
        case 2:
            g_array[2] = ((g_count+G)*1.3);    //存储1s内的绿光通过滤波器时，TCS3200输出的脉冲个数
            Serial.print("  G=");
            Serial.print((g_count+G)*1.3);
            TSC_WB(LOW, HIGH);  //选择让蓝色光线通过滤波器的模式
            break;
        case 3:
            g_array[3] = ((g_count+B)*1.2);     //存储1s内的蓝光通过滤波器时，TCS3200输出的脉冲个数
            Serial.print("B=");
            Serial.print((g_count+B)*1.2);
            TSC_WB(HIGH, LOW);   //选择无滤波器的模式
            break;
        default:
            g_count = 0;     //计数值清零
            break;
    }
}
void read_rgb(){
    TSC_Init();
    Serial.begin(9600,SERIAL_8N1);  //启动串行通信
    Timer1.initialize();
    Timer1.attachInterrupt(TSC_Callback); //设置定时器1的中断，中断调用函数为TSC_Callback()
    //设置TCS3200输出信号的上跳沿触发中断，中断调用函数为TSC_Count()
    attachInterrupt(0, TSC_Count, RISING);
    delay(400); //延时0.1s，以等待被测物体红、绿、蓝三色在1s内的TCS3200输出信号脉冲计数
    for(b=0;b<=2;b++)
    {g_flag = 0;
        delay(400);
        if(g_array[1]>g_array[2]&&g_array[1]>g_array[3]){m=1;digitalWrite(5,HIGH);digitalWrite(6,LOW);digitalWrite(7,LOW);delay(100);}
        if(g_array[2]>g_array[3]&&g_array[2]>g_array[1]){m=2;digitalWrite(6,HIGH);digitalWrite(5,LOW);digitalWrite(7,LOW);delay(100);}
        if(g_array[3]>g_array[1]&&g_array[3]>g_array[2]){m=3;digitalWrite(7,HIGH);digitalWrite(5,LOW);digitalWrite(6,LOW);delay(100);}
        Serial.print("   color is");
        Serial.println(m);}
    Timer1.stop();

}