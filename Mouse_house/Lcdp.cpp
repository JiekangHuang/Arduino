#include "Lcdp.h"

Lcdp::Lcdp(LiquidCrystal_I2C* lcd)
{
	this->_lcd = lcd;
}

Lcdp::~Lcdp()
{
}

void Lcdp::lcd_begin()
{
	this->_lcd->begin(16, 2);
	this->_lcd->clear();
	this->_lcd->setCursor(0, 0);
	this->_lcd->print("Boot");
	for (int i = 0; i < 8; i++)
	{
		delay(500);
		this->_lcd->setCursor(i + 4, 0);
		this->_lcd->print(".");
	}
	this->_lcd->clear();
	this->_lcd->setCursor(0, 0);
	this->_lcd->print("Boot completed!!");
	delay(2000);
	this->_lcd->clear();
	this->_lcd->print("Quantity >0    R");
}