#define CA1 30
#define CA2 31
#define CA3 32

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

String text[] = { "2019" ,"1005" };
unsigned long pre_time;
byte idx = 0, re = 1;

void pickDigit(byte);
void show(String);

void setup()
{
	for (int i = 0; i < 7; i++)
		pinMode(segs[i], OUTPUT);
	for (byte i = CA1; i <= CA3; i++)
		pinMode(i, OUTPUT);
	pinMode(A13, OUTPUT);
	digitalWrite(A13, LOW);
	pre_time = millis();
}

void loop()
{
	if (millis() - pre_time >= 500)
	{
		pre_time = millis();
		idx += re;
		re = -re;
	}
	show(text[idx]);
}

void pickDigit(byte x)
{
	switch (x)
	{
	case 0:
		digitalWrite(CA1, LOW);
		digitalWrite(CA2, LOW);
		digitalWrite(CA3, LOW);
		break;
	case 1:
		digitalWrite(CA1, HIGH);
		digitalWrite(CA2, LOW);
		digitalWrite(CA3, LOW);
		break;
	case 2:
		digitalWrite(CA1, LOW);
		digitalWrite(CA2, HIGH);
		digitalWrite(CA3, LOW);
		break;
	case 3:
		digitalWrite(CA1, HIGH);
		digitalWrite(CA2, HIGH);
		digitalWrite(CA3, LOW);
		break;
	}
}

void show(String num)
{
	for (byte i = 0; i < num.length(); i++)
	{
		byte n = atoi(&num[3 - i]);
		pickDigit(i);
		for (int i = 0; i < 7; i++)
			digitalWrite(segs[i], seven_seg_digits[n][i]);
		delay(4);
	}
}