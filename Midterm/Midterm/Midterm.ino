/*
 Name:		Midterm.ino
 Created:	2019/11/3 上午 01:20:22
 Author:	s2862
*/
#define CA1 30
#define CA2 31
#define CA3 32

int BUT_PIN[] = { 33,34 };
byte segs[] = { 2, 3, 4, 5, 6, 7, 8 };

byte seven_seg_digits[10][7] =
{
	{ 0,0,0,0,0,0,1 },
	{ 1,0,0,1,1,1,1 },
	{ 0,0,1,0,0,1,0 },
	{ 0,0,0,0,1,1,0 },
	{ 1,0,0,1,1,0,0 },
	{ 0,1,0,0,1,0,0 },
	{ 0,1,0,0,0,0,0 },
	{ 0,0,0,1,1,1,1 },
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,1,1,0,0 }
};

bool SW(int);
void action(int);
void show(int);

int num = 0, add = 1;
unsigned long pre_time;

void setup()
{
	for (int i = 0; i < 7; i++)
		pinMode(segs[i], OUTPUT);
	for (byte i = CA1; i <= CA3; i++)
		pinMode(i, OUTPUT);
	for (int i = 0; i < 2; i++)
		pinMode(BUT_PIN[i], INPUT_PULLUP);
	pinMode(A13, OUTPUT);
	digitalWrite(A13, LOW);
	show(0);
	pre_time = millis();
}

void loop()
{
	for (int i = 0; i < 2; i++)
		if (SW(BUT_PIN[i]))
			action(i);
	if (millis() - pre_time >= 300)
	{
		pre_time = millis();
		num += add;
		num > 5 ? num = 0 : NULL;
		num < 0 ? num = 5 : NULL;
		show(num);
	}
}

bool SW(int pin)
{
	delay(20);
	bool sw = digitalRead(pin);
	if (!sw)
	{
		do
		{
			delay(20);
			sw = digitalRead(pin);
		} while (!sw);
		return true;
	}
	return false;
}

void action(int s)
{
	switch (s)
	{
	case 0:
		add = 1;
		break;
	case 1:
		add = -1;
		break;
	}
}

void show(int n)
{
	for (int i = 0; i < 7; i++)
		digitalWrite(segs[i], seven_seg_digits[n][i]);
}