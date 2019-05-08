#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#include "Lcdp.h"
#include "Time.h"

#define pin A0

Lcdp _lcd(&lcd);
Time _time(&lcd);

void setup()
{
	Serial.begin(9600);
	_lcd.lcd_begin();
	_time.time_begin();
}

void loop()
{
	_time.show_time();
	static int num = 0, sum = 0;
	bool val;
	int rd = analogRead(pin);
	rd < 200 ? val = true : val = false;
	if (val)
	{
		num++;
		do
		{
			_time.show_time();
			rd = analogRead(pin);
			rd < 200 ? val = true : val = false;
		} while (val);
		if (num % 9 == 0)
		{
			lcd.setCursor(10, 0);
			sum++;
			Serial.println(sum);
			lcd.print(sum);
		}
	}
}