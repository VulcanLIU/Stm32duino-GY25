/* 
* ComwithGY25.cpp
*
* Created: 2018/10/8 19:30:32
* Author: Vulcan
*/


#include "ComwithGY25.h"

#include <HardwareSerial.h>

HardwareSerial Serial1(PA10, PA9);
// default constructor
ComwithGY25::ComwithGY25()
{
} //ComwithGY25

void ComwithGY25::begin()
{
	Serial1.begin(115200);
	delay(3000);
	correctYaw();
	Serial1.write(0XA5);
	Serial1.write(0X52);    //��ʼ��GY25,�������ģʽ
}

void ComwithGY25::autoMode()
{
	Serial1.write(0XA5);
	Serial1.write(0X52);    //��ʼ��GY25,�������ģʽ
}

void ComwithGY25::autoModeASCII()
{
	Serial1.write(0XA5);
	Serial1.write(0X53);    //��ʼ��GY25,�������ģʽ
}

void ComwithGY25::singleMode()
{
	Serial1.write(0XA5);
	Serial1.write(0X51);    //У��ģʽ��У����������� 0 �ȣ���Ҫ����ˮƽʱ����
}

void ComwithGY25::correctPitchRow()
{
	Serial1.write(0XA5);
	Serial1.write(0X54);    //У��ģʽ��У����������� 0 �ȣ���Ҫ����ˮƽʱ����
}

void ComwithGY25::correctYaw()
{
	Serial1.write(0XA5);
	Serial1.write(0X55);    //У��ģʽ��У������ 0 �ȣ���������Ƕ�����
}

void ComwithGY25::refresh() {
	while (Serial1.available()) {
		Re_buf[counter]=(unsigned char)Serial1.read();
		if(counter==0&&Re_buf[0]!=0xAA) return;      // ���֡ͷ
		counter++;
		if(counter==8)                //���յ�����
		{
			counter=0;                 //���¸�ֵ��׼����һ֡���ݵĽ���
			sign=1;
		}
	}
	if(sign == 1)
	{
		if(Re_buf[0]==0xAA && Re_buf[7]==0x55)        //���֡ͷ��֡β
		{
			YPR[0]=(Re_buf[1]<<8|Re_buf[2])/-100.00;   //�ϳ����ݣ�ȥ��С�����2λ
			YPR[1]=(Re_buf[3]<<8|Re_buf[4])/100.00;
			YPR[2]=(Re_buf[5]<<8|Re_buf[6])/100.00;
		}
		sign = 0;
	}
}

ComwithGY25 GY25 = ComwithGY25();