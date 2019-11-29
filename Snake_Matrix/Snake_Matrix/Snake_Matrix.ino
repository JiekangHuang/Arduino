#include "MAX7219.h"
#include "Snake.h"

const byte CLK = 10;
const byte LOAD = 9;
const byte DIN = 8;

const byte buts[] = { 2, 3, 4, 5 };
#define NUM_OF_MATRIXES (6)

bool SW(int);
void Action(byte);
bool check_food(void);
void print_to_Serial(void);

MAX7219 max7219(DIN, LOAD, CLK, NUM_OF_MATRIXES);
Snake snake(10, 8);

uint64_t pre_time;

void setup()
{
	Serial.begin(115200);

	max7219.init_max7219();

	randomSeed(analogRead(0));
	snake.check_food(check_food);

	pre_time = millis();
	max7219.display_on();
	Serial.print(snake.Get_foodx());
	Serial.print(" , ");
	Serial.println(snake.Get_foody());
}

void loop()
{
	/*
	1.裝四顆方向按鈕
	2.死亡跑馬燈(GG!!)
	3.解決scan speed too low --ok
	4.使用三位數七段顯示器顯示蛇長
	5.難度設定
	6.最高紀錄(可有可無)
	*/
	/*for (int i = 0; i < 4; i++)
		if (SW(buts[i]))
			Action(i);*/
	if (millis() - pre_time >= 500)
	{
		if (!snake.is_move(check_food))
		{
			max7219.display_off();
			Serial.println("is dead!!");
			while (true)
				;
		}
		pre_time = millis();
	}
	max7219.display(snake.Get_snake_map());
	/*Serial.print((uint8_t)random(16));
	Serial.print(" , ");
	Serial.println((uint8_t)random(24));*/
	uint8_t *food_x = &snake.Get_foodx();
	uint8_t *food_y = &snake.Get_foody();
	*food_x = (uint8_t)random(16);
	*food_y = (uint8_t)random(24);
}

bool check_food(void)
{
	node *snake_map = snake.Get_snake_map();
	uint8_t *food_x = &snake.Get_foodx();
	uint8_t *food_y = &snake.Get_foody();
	byte *value = &(*food_x * COL + snake_map + *food_y)->val;
	if (*value != FOOD)
	{
		do
		{
			*food_x = (uint8_t)random(16);
			*food_y = (uint8_t)random(24);
		} while (((*food_x * COL + snake_map + *food_y)->val) != NON);

		value = &(*food_x * COL + snake_map + *food_y)->val;
		*value = FOOD;
		return true;
	}
	return false;
}

void print_to_Serial(void)
{
	node *snake_map = snake.Get_snake_map();
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			Serial.print((i * COL + snake_map + j)->val);
			//測試記憶體位置
			//Serial.print((long)(i * 24 + snake_map + j), HEX);
		}
		Serial.println();
	}
	Serial.println();
}

bool SW(int pin)
{
	bool sw = digitalRead(pin);
	if (sw)
	{
		do
		{
			delay(5);
			sw = digitalRead(pin);
		} while (sw);
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