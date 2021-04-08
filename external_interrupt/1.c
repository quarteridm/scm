#include <reg52.h>
#include <intrins.h>

typedef unsigned int u16; //对数据类型进行声明定义
typedef unsigned char u8;
#define led P2

//sbit LED=P2^0;

sbit k3=P3^2;
sbit k4=P3^3;
	u8 scan=1;
void inter1()
{
	EA=1;
	EX1=1;
	IT1=1;
}
void delay(u16 i)
{
	while(i--);
}

void main()
{
	u8 i;

	inter1();
	
	led=~0x01;
	delay(50000);
	while(1)
	{
//		if(scan==1)
//		{
			for(i=0;i<7;i++)
			{
				if(scan==1)
				{
				led=_crol_(led,1);
				delay(50000);
				}
				else
				{
					delay(50000);
				}
			}
		}
		
//	}
}

void		Int1()  interrupt 2
{
	delay(1000);
	if(k4==0)
	{	
			scan=~scan;
	}
}