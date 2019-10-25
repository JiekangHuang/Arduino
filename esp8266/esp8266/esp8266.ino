/*
 Name:		esp8266.ino
 Created:	2019/8/4 下午 06:39:03
 Author:	s2862
*/
#include "OTA.h"
#include "esp8266_key.h"

long int pre_time = 0;
long int cur_time = 0;
bool val = false;

boolean success = false;

void setup()
{
	Serial.begin(9600);
	OTA();
	pinMode(D4, OUTPUT);
}

void loop()
{
}