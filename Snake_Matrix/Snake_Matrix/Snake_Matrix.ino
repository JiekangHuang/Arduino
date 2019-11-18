#include "MAX7219.h"
#include "Snake.h"

const byte CLK = 13;
const byte LOAD = 10;
const byte DIN = 11;

const byte buts[] = { 2, 3, 4, 5 };
#define NUM_OF_MATRIXES (6)

MAX7219 max7219(DIN, LOAD, CLK, NUM_OF_MATRIXES);
Snake snake;

bool SW(int);
void Action(byte);

void setup()
{
	pinMode(CLK, OUTPUT);
	pinMode(LOAD, OUTPUT);
	pinMode(DIN, OUTPUT);

	max7219.init_max7219();
}

void loop()
{
	for (int i = 0; i < 4; i++)
		if (SW(buts[i]))
			Action(i);

	max7219.display(snake.Get_snake_map());

	if (!snake.is_move())
	{
		digitalWrite(13, HIGH);
		max7219.clear_matrix();
		while (true)
			;
	}
}

bool SW(int pin)
{
	bool sw = digitalRead(pin);
	if (!sw)
	{
		do
		{
			delay(5);
			sw = digitalRead(pin);
		} while (!sw);
		return true;
	}
	return false;
}

void Action(byte bt_idx)
{
	static byte pre_dir = -1;

	if (abs(bt_idx - pre_dir) == 2)
		//Direction is opposite to last time
		return;
	snake.Set_cur_dir(bt_idx + 1);
	pre_dir = bt_idx;
}