#include "Time.h"

Time::Time(LiquidCrystal_I2C* lcd)
{
	this->_lcd = lcd;
}

Time::~Time()
{
}
void Time::time_begin()
{
	this->_lcd->setCursor(0, 1);
	this->_lcd->print("boot time>");
	this->_lcd->setCursor(15, 1);
	this->_lcd->print("m");
}
void Time::show_time()
{
	boot_time = millis() / 1000 / 60;
	this->_lcd->setCursor(10, 1);
	this->_lcd->print(boot_time);
}