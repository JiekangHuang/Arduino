#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Lcdp
{
protected:
	LiquidCrystal_I2C* _lcd;
public:
	Lcdp(LiquidCrystal_I2C*);
	~Lcdp();
	void lcd_begin();
};
