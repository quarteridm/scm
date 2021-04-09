/**************************************************************************************
ʵ�������
����˵���� ��Ƭ��-->LED&��ͨ��ģ��(�������ͼ�ɼ��������Զ�Ӧʵ��ġ�ʵ�������½�)
		   P00-->D1	
ע�����																				  
***************************************************************************************/

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;
int a;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit k3=P3^2;
sbit k4=P3^3;

u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ

void time0unit()  //��ʱ��0�жϿ���
{
	TMOD|=0X01;
	TH0=0xFC;
	TL0=0X18;
	ET0=1;
	EA=1;
	TR0=1;
	
}
void inter1()//�ⲿ�ж�1����
{
	EA=1;
	EX1=1;
	IT1=1;
}
void delay(u16 i)//ʱ�Ӻ�������Լ��ʱ1us
{
	while(i--);
}
void Time0() interrupt 1//��ʱ��1�жϺ�����ʵ��1s�ļ�ʱ��
{												//ͬʱʵ�������ʾ���ֵļ���
	static u16 i;

	TH0=0xFC;//����ʱ��1��ֵ
	TL0=0x18;
	i++;
		if(i==1000)
			{
				i=0;
				a--;
			}	
}

void		Int1()  interrupt 2//�������㺯����ʹ��K4���ⲿ�ж�1
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
			delay(1100);//��ʱ����LED���͵�Ӱ��
			LSA=0;LSB=0;LSC=1;
			P0=smgduan[a/10];
			delay(1100);
		}
		else
		{
			a=59;//�Զ���λ
		}
	}
}

