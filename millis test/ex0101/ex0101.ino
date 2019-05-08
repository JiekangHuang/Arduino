/*
 Name:		ex0101.ino
 Created:	2019/5/9 上午 02:47:32
 Author:	s2862
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

unsigned long boot_time = 0;
unsigned long previous_time = 0;
#define sw_pin 2
bool SW(int);
void setup()
{
	Serial.begin(9600);
	lcd.begin(16, 2);
	lcd.clear();
	pinMode(sw_pin, INPUT_PULLUP);
}

void loop()
{
	static int num = 0, i = 0, val = 1;
	boot_time = millis();

	if (boot_time - previous_time >= 1000)
	{
		previous_time = boot_time;
		lcd.setCursor(0, 0);
		lcd.print(i);
		i += val;
	}
	if (SW(sw_pin))
		val = -val;

	i > 9 ? i = 0 : NULL;
	i < 0 ? i = 9 : NULL;
}
bool SW(int pin)
{
	bool sw = digitalRead(pin);
	delay(20);
	if (!sw)
	{
		unsigned long now_time = millis();
		do
		{
			if (millis() - now_time >= 50)
				return false;
			delay(20);
			sw = digitalRead(pin);
			delay(20);
		} while (!sw);
		return true;
	}
	return false;
}