#define CA1 30
#define CA2 31
#define CA3 32

byte segs[] = {2, 3, 4, 5, 6, 7, 8};

byte seven_seg_digits[10][7] =
	{
		{0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 1},
		{0, 0, 1, 0, 0, 1, 0},
		{0, 0, 0, 0, 1, 1, 0},
		{1, 0, 0, 1, 1, 0, 0},
		{0, 1, 0, 0, 1, 0, 0},
		{0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0}};

bool _74LS138[][3] =
	{
		{0, 0, 0},
		{0, 0, 1},
		{0, 1, 0},
		{0, 1, 1},
		{1, 0, 0},
		{1, 0, 1},
		{1, 1, 0},
		{1, 1, 1}};

String text[] = {"2019", "1005"};
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
	for (int i = 0, j = CA3; i < 3; i++, j--)
		digitalWrite(j, _74LS138[x][i]);
}

void show(String num)
{
	int num_len = num.length();
	for (byte i = 0; i < num_len; i++)
	{
		byte n = num[num_len - i] - 48;
		pickDigit(i);
		for (int i = 0; i < 7; i++)
			digitalWrite(segs[i], seven_seg_digits[n][i]);
		delay(4);
	}
}