/*
 Name:		Car.ino
 Created:	2019/4/30 上午 02:24:01
 Author:	s2862
*/

#include "L298N.h"
#include "SR04.h"
#include <servo.h>
#include <SoftwareSerial.h>

const int trig = 2;
const int echo = 3;
const int inter_time = 1000;
int time = 0;

L298N act(8, 9, 10, 11, 6, 5);
SR04 sr04(A0, A1);
Servo servo;
SoftwareSerial BT(2, 3);

void Run_dodge();
void Run_BT();
void setup()
{
	BT.begin(115200);
	Serial.begin(9600);
	servo.attach(12);
	servo.write(90);
	delay(2000);
	act.set_speed(130);
}

void loop()
{
	bool L, M, R;
	L = digitalRead(A4);
	M = digitalRead(A3);
	R = digitalRead(A2);
	Serial.print(L);
	Serial.print(" , ");
	Serial.print(M);
	Serial.print(" , ");
	Serial.println(R);

	if (L & M & R)
	{
		bool i = false;
		while ((L & M & R))
		{
			if (!i)
			{
				act.stop();
				i = true;
			}
			L = digitalRead(A4);
			M = digitalRead(A3);
			R = digitalRead(A2);
			Serial.println("stop");
			Run_BT();
		}
	}
	if (M)
	{
		(!L) ? act.L_stop() : act.R_stop();
		delay(30);
		act.Forward();
	}
	else
		act.Forward();
}
void Run_dodge()
{
	float F = sr04.get_distance();
	if (F < 35)
	{
		act.stop();
		servo.write(40);
		delay(500);
		float R = sr04.get_distance();
		Serial.println(R);
		servo.write(140);
		delay(500);
		float L = sr04.get_distance();
		Serial.println(L);
		servo.write(90);
		delay(500);

		L > R ? act.T_left() : act.T_right();
		delay(200);
		act.stop();
	}
	else
		act.Forward();
}
void Run_BT()
{
	if (BT.available())
	{
		char val = BT.read();
		Serial.println(val);
		switch (val)
		{
		case 'w':
			act.Forward();
			break;
		case 'a':
			act.T_left();
			break;
		case 'd':
			act.T_right();
			break;
		case 'x':
			act.Backward();
			break;
		default:
			act.stop();
			break;
		}
	}
}