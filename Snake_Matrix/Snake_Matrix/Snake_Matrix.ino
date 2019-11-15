#include <Arduino.h>
#include "MAX7219.h"

const byte CLK = 13;
const byte LOAD = 10;
const byte DIN = 11;

#define NUM_OF_MATRIXES (6)

byte snake_map[24][32];

MAX7219 max7219(DIN, LOAD, CLK, NUM_OF_MATRIXES);

void display()
{
	unsigned int matrix_index = 0;
	max7219.set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_OFF);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < NUM_OF_COLUMNS; k++)
			{
				byte data = 0x0;
				for (int m = 0; m < NUM_OF_COLUMNS; m++)
				{
					data |= snake_map[i * NUM_OF_COLUMNS + m][j * NUM_OF_COLUMNS + k];
					data <<= 1;
				}
				max7219.set_single_register(matrix_index, MAX7219_COLUMN_REG(k), data);
			}
			matrix_index++;
		}

	max7219.set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_ON);
}

void setup()
{
	pinMode(CLK, OUTPUT);
	pinMode(LOAD, OUTPUT);
	pinMode(DIN, OUTPUT);

	max7219.init_max7219();
}

void loop()
{
	display();
}