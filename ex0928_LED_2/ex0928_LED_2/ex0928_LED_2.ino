/*
 Name:		ex0928_LED.ino
 Created:	2019/9/28 上午 10:45:34
 Author:	s2862
*/

int LED_PIN[2][4] = { {5,4,3,2}, {6,7,8,9 } };

int idx = 0;
int re = 1;
void setup()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			pinMode(LED_PIN[i][j], OUTPUT);
	pinMode(A15, OUTPUT);
	digitalWrite(A15, LOW);
}

void loop()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			digitalWrite(LED_PIN[i][j], HIGH);
	digitalWrite(LED_PIN[0][idx], LOW);
	digitalWrite(LED_PIN[1][idx], LOW);
	delay(500);
	idx += re;
	if (idx == 3 || idx == 0)
		re *= -1;
}