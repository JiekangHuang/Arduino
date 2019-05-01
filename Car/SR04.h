#pragma once
#include <Arduino.h>
class SR04
{
private:
	byte trig, echo;
public:
	SR04(byte, byte);
	~SR04();
	float get_distance();
};