/*
 Name:		ex0928_LED.ino
 Created:	2019/9/28 上午 10:45:34
 Author:	s2862
*/

int PIN[2][4] = { {5,4,3,2}, {6,7,8,9 } };

byte count = 0;
byte re = 1;
void setup()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			pinMode(PIN[i][j], OUTPUT);
	pinMode(A15, OUTPUT);
	digitalWrite(A15, LOW);
}

void loop()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			digitalWrite(PIN[i][j], HIGH);
	for (int j = 0; j < 4; j++)
	{
		digitalWrite(PIN[0][count], LOW);
		digitalWrite(PIN[1][count], LOW);
	}
	delay(500);
	count += re;
	if (count == 3 || count == 0)
		re *= -1;
}