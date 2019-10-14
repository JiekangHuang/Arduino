/*
 Name:		ex0928_LED.ino
 Created:	2019/9/28 上午 10:45:34
 Author:	s2862
*/
int LED_PIN[] = { 2, 3, 4, 5, 6, 7, 8, 9 };

int BUT_PIN[] = { 33,34,35,36 };
int delay_time = 500;

bool SW(int);
void action(int);
void clean(void);
void sw1_act();
void sw2_act();
void sw3_act();
void sw4_act();

void setup()
{
	for (int i = 0; i < 8; i++)
		pinMode(LED_PIN[i], OUTPUT);
	for (int i = 0; i < 4; i++)
		pinMode(BUT_PIN[i], INPUT);

	pinMode(A15, OUTPUT);
	digitalWrite(A15, LOW);
	clean();
}

void loop()
{
	for (int i = 0; i < 4; i++)
		if (SW(BUT_PIN[i]))
			action(i);
}

bool SW(int pin)
{
	delay(20);
	bool sw = digitalRead(pin);
	if (sw)
	{
		do
		{
			delay(20);
			sw = digitalRead(pin);
		} while (sw);
		return true;
	}
	return false;
}

void action(int s)
{
	for (int i = 0; i < 3; i++)
	{
		switch (s)
		{
		case 0:
			sw1_act();
			break;
		case 1:
			sw2_act();
			break;
		case 2:
			sw3_act();
			break;
		case 3:
			sw4_act();
			break;
		}
		clean();
	}
}

void clean(void)
{
	for (int i = 0; i < 8; i++)
		digitalWrite(LED_PIN[i], HIGH);
}

void sw1_act()
{
	int idx = 0, j = 0;;
	for (int i = 0; i < 2; i++)
	{
		clean();
		for (int j = 0; j < 4; j++)
			digitalWrite(LED_PIN[idx++], LOW);
		delay(delay_time);
	}
}

void sw2_act()
{
	int idx = 0, re = 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			digitalWrite(LED_PIN[idx], LOW);
			delay(delay_time);
			idx += re;
			clean();
		}
		re = -re;
	}
}

void sw3_act()
{
	int idx_a = 3, idx_b = 4, re = 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			digitalWrite(LED_PIN[idx_a], LOW);
			digitalWrite(LED_PIN[idx_b], LOW);
			idx_a -= re;
			idx_b += re;
			delay(delay_time);
			clean();
		}
		re = -re;
	}
}

void sw4_act()
{
	bool val = false;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 8; j++)
			digitalWrite(LED_PIN[j], val);
		val = !val;
		delay(delay_time);
		clean();
	}
}