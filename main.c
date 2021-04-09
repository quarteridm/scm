/**************************************************************************************
实验现象：�
接线说明： 单片机-->LED&交通灯模块(具体接线图可见开发攻略对应实验的“实验现象”章节)
		   P00-->D1	
注意事项：																				  
***************************************************************************************/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;
int a;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit k3=P3^2;
sbit k4=P3^3;

u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值

void time0unit()  //定时器0中断开启
{
	TMOD|=0X01;
	TH0=0xFC;
	TL0=0X18;
	ET0=1;
	EA=1;
	TR0=1;
	
}
void inter1()//外部中断1开启
{
	EA=1;
	EX1=1;
	IT1=1;
}
void delay(u16 i)//时延函数，大约延时1us
{
	while(i--);
}
void Time0() interrupt 1//定时器1中断函数，实现1s的计时，
{			//同时实现秒表显示数字的减少
	static u16 i;

	TH0=0xFC;//给定时器1赋值
	TL0=0x18;
	i++;
		if(i==1000)
			{
				i=0;
				a--;
			}	
}

void		Int1()  interrupt 2//按键置零函数，使用K4→外部中断1
{
	delay(500);
	if(k4==0)
	{	
			a=59;
	}
}

void main()
{
	inter1();
	time0unit();
	a=59;
	while(1)
	{
		
		if(a>=0)
		{
			LSA=0;LSB=0;LSC=0;
			P0=smgduan[a%10];
			delay(1100);//延时减少LED余晖的影响
			LSA=0;LSB=0;LSC=1;
			P0=smgduan[a/10];
			delay(1100);
		}
		else
		{
			a=59;//自动复位
		}
	}
}

