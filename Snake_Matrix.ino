#include "MAX7219.h"
#include "Snake.h"

const byte CLK = 13;
const byte LOAD = 10;
const byte DIN = 11;

const buts = {2, 3, 4, 5};
#define NUM_OF_MATRIXES (6)

MAX7219 max7219(DIN, LOAD, CLK, NUM_OF_MATRIXES);
Snake snake();

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

	max7219.display();

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
	switch (bt_idx)
	{
	case 0:
		snake.Set_cur_dir(1);
		break;
	case 1:
		snake.Set_cur_dir(2);
		break;
	case 2:
		snake.Set_cur_dir(3);
		break;
	case 3:
		snake.Set_cur_dir(4);
		break;
	}
}
