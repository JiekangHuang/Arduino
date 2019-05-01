#include "SR04.h"

SR04::SR04(byte trig, byte echo)
{
	this->trig = trig;
	this->echo = echo;

	pinMode(this->trig, OUTPUT);
	pinMode(this->echo, INPUT);
}

SR04::~SR04()
{
	Serial.println("SR04::~SR04();");
}

float SR04::get_distance()
{
	digitalWrite(trig, LOW);
	delayMicroseconds(3);
	digitalWrite(trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(trig, LOW);

	float duration = pulseIn(echo, HIGH);
	float distance = (duration / 2) / 29.1;
	return distance;
}