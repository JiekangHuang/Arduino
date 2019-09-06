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

void setup()
{
	Serial.begin(9600);
	OTA();
	pinMode(D4, OUTPUT);
	Serial.begin(9600);
	pre_time = millis();
}

void loop()
{
	ArduinoOTA.handle();
	cur_time = millis();
	if (cur_time - pre_time >= 1000)
	{
		Serial.println("Holle !");
		pre_time = cur_time;
		digitalWrite(D4, val);
		val = !val;
	}
}