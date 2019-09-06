/*
 Name:		ex0928_LED.ino
 Created:	2019/9/28 上午 10:45:34
 Author:	s2862
*/

int PIN[] = { 2,3,4,5,6,7,8,9 };

int count = 0;
int re = 1;
void setup()
{
	for (int i = 0; i < 8; i++)
	{
		pinMode(PIN[i], OUTPUT);
	}
	pinMode(A15, OUTPUT);
	digitalWrite(A15, LOW);
}

void loop()
{
	for (int i = 0; i < 8; i++)
		digitalWrite(PIN[i], HIGH);
	digitalWrite(PIN[count], LOW);
	delay(500);
	count += re;
	if (count == 7 || count == 0)
		re *= -1;
}