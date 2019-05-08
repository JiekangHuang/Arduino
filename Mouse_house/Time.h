#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Time
{
protected:
	int boot_time;
	LiquidCrystal_I2C* _lcd;
public:
	Time(LiquidCrystal_I2C*);
	~Time();
	void time_begin();
	void show_time();
};
