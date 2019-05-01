/*
 Name:		Car.ino
 Created:	2019/4/30 上午 02:24:01
 Author:	s2862
*/

#include "L298N.h"
#include "SR04.h"

const int trig = 2;
const int echo = 3;
const int inter_time = 1000;
int time = 0;

L298N act(8, 9, 10, 11, 6, 5);
SR04 sr04(A0, A1);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	act.Forward();
	//bool value1 = analogRead(A2);
	//bool value2 = analogRead(A3);
	//bool value3 = analogRead(A4);
	//Serial.print(value1);
	//Serial.print(" , ");
	//Serial.print(value2);
	//Serial.print(" , ");
	//Serial.println(value3);
	//Serial.println(sr04.get_distance());
}