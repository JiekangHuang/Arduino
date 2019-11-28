#include "MAX7219.h"
#include "Snake.h"

const byte CLK = 10;
const byte LOAD = 9;
const byte DIN = 8;

const byte buts[] = { 2, 3, 4, 5 };
#define NUM_OF_MATRIXES (6)

bool SW(int);
void Action(byte);
bool check_food();

MAX7219 max7219(DIN, LOAD, CLK, NUM_OF_MATRIXES);
Snake snake(10, 8);

void setup()
{
	Serial.begin(115200);
	pinMode(CLK, OUTPUT);
	pinMode(LOAD, OUTPUT);
	pinMode(DIN, OUTPUT);

	max7219.init_max7219();

	randomSeed(analogRead(A0));
	snake.check_food(check_food);
	Serial.print(snake.Get_foodx());
	Serial.print(" , ");
	Serial.println(snake.Get_foody());
	delay(4000);
}

void loop()
{
	/*
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

	*/
	//snake.init();
	/*if (check_food())
		snake.add_snake_len();

	*/
	node **snake_map = snake.Get_snake_map();
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			//Serial.print(snake_map+0.val);
			Serial.print((long)*((snake_map + 0) + 0), HEX);
			Serial.print(",");
		}
		Serial.println();
		Serial.println();
	}
	Serial.println();

	//snake.run();
	//Serial.println(sizeof(node));
}

bool check_food(void)
{
	/*node **snake_map = snake.Get_snake_map();
	uint8_t *food_x = &snake.Get_foodx();
	uint8_t *food_y = &snake.Get_foody();
	if ((snake_map + *food_x)[*food_y].val != FOOD)
	{
		*food_x = (uint8_t)random(16);
		*food_y = (uint8_t)random(24);
		(snake_map + *food_x)[*food_y].val = FOOD;
		return true;
	}
	return false;*/
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