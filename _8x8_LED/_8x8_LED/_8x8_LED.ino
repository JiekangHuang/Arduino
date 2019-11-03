#include <TimedAction.h>

#define Ls138_b 30
#define Ls138_e 32

#define row_size 8
#define col_size 8
#define delay_time 500

const int word_array[][row_size] =
{
	//A
   {B00011000,
	B00100100,
	B00100100,
	B01000010,
	B01111110,
	B01000010,
	B01000010,
	B01000010 },
	//N
   {B01000010,
	B01100010,
	B01100010,
	B01010010,
	B01001010,
	B01000110,
	B01000110,
	B01000010 },
	//0
   {B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000 },
	//1
   {B11111111,
	B11111111,
	B11111111,
	B11111111,
	B11111111,
	B11111111,
	B11111111,
	B11111111 },
	//test
   {B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000001,
	B00000000 }
};

bool _74LS138[][3] =
{
	{0, 0, 0},
	{0, 0, 1},
	{0, 1, 0},
	{0, 1, 1},
	{1, 0, 0},
	{1, 0, 1},
	{1, 1, 0},
	{1, 1, 1} };

int led[row_size];
byte row_pin[row_size] = { 2, 3, 4, 5, 6, 7, 8, 9 };

void word_to_led(int);
void display_led(int led[row_size]);
void low_74138pin(int);
void add();

int idx = 0;

TimedAction addText = TimedAction(delay_time, add);

void setup()
{
	for (int i = Ls138_b; i <= Ls138_e; i++)
		pinMode(i, OUTPUT);
	for (int i = 0; i < 8; i++)
		pinMode(row_pin[i], OUTPUT);
	clear_led();
	pinMode(A14, OUTPUT);
	digitalWrite(A14, LOW);
}

void loop()
{
	addText.check();
	word_to_led(idx);
	display_led(led);
}

void word_to_led(int n)
{
	for (int i = 0; i < row_size; i++)
		led[i] = word_array[n][i];
}

void clear_led()
{
	for (int i = 0; i < row_size; i++)
		digitalWrite(row_pin[i], LOW);
}

void display_led(int led[row_size])
{
	for (int i = col_size - 1; i >= 0; i--)
	{
		clear_led();
		low_74138pin(i); //選擇col
		for (int j = 0; j < row_size; j++)
		{
			digitalWrite(row_pin[j], (led[j] & 1));  //輸出row
			led[j] >>= 1;
		}
	}
}

void low_74138pin(int num)
{
	for (int i = 0, j = Ls138_e; i < 3; i++, j--)
		digitalWrite(j, _74LS138[num][i]);
}

void add()
{
	idx++;
	idx > 3 ? idx = 0 : NULL;
}