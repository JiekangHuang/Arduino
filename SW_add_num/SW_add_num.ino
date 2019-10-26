/*
 Name:		SW_add_num.ino
 Created:	2019/10/26 上午 10:46:33
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

void setup()
{
	for (int i = 0; i < 7; i++)
		pinMode(segs[i], OUTPUT);
	for (byte i = CA1; i <= CA3; i++)
		pinMode(i, OUTPUT);
	for (int i = 0; i < 4; i++)
		pinMode(BUT_PIN[i], INPUT_PULLUP);
	pinMode(A13, OUTPUT);
	digitalWrite(A13, LOW);
	show(0);
}

void loop()
{
	for (int i = 0; i < 2; i++)
		if (SW(BUT_PIN[i]))
			action(i);
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
	static int num = 0;
	switch (s)
	{
	case 0:
		++num;
		break;
	case 1:
		--num;
		break;
	}
	num > 9 ? num = 0 : NULL;
	num < 0 ? num = 9 : NULL;
	show(num);
}

void show(int n)
{
	for (int i = 0; i < 7; i++)
		digitalWrite(segs[i], seven_seg_digits[n][i]);
}