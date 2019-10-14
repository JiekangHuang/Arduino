/*
 Name:		ex0928_LED.ino
 Created:	2019/9/28 上午 10:45:34
 Author:	s2862
*/
int LED_PIN[] = { 2,3,4,5,6,7,8,9 };

int idx = 0;
int re = 1;
void setup()
{
	for (int i = 0; i < 8; i++)
		pinMode(LED_PIN[i], OUTPUT);

	pinMode(A15, OUTPUT);
	digitalWrite(A15, LOW);
}

void loop()
{
	for (int i = 0; i < 8; i++)
		digitalWrite(LED_PIN[i], HIGH);
	digitalWrite(LED_PIN[idx], LOW);
	delay(500);

	idx += re;
	if (idx == 7 || idx == 0)
		re *= -1;
}