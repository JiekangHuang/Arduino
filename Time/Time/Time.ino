byte comms[] = { 9,10,11,12 };
byte segs[] = { 2, 3, 4, 5, 6, 7, 8 };

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
	{0, 0, 0, 1, 1, 0, 0} };

void show(String);

void setup()
{
	Serial.begin(9600);
	for (int i = 2; i <= 12; i++)
		pinMode(i, OUTPUT);
}

void loop()
{
	String cur_time_str = "";
	unsigned long cur_time = millis() / 1000;
	cur_time_str += String(cur_time % 10);
	cur_time /= 10;
	cur_time_str += String(cur_time % 6);
	cur_time /= 6;
	cur_time_str += String(cur_time % 10);
	cur_time /= 10;

	show(cur_time_str);
}

void show(String num)
{
	int num_len = num.length();
	for (int i = num_len - 1; i >= 0; i--)
	{
		byte n = num[i] - 48;
		digitalWrite(comms[i], HIGH);
		for (int i = 0; i < 7; i++)
			digitalWrite(segs[i], !seven_seg_digits[n][i]);
		delay(4);
		digitalWrite(comms[i], LOW);
	}
}