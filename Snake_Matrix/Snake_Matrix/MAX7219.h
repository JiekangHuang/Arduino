#include "node.h"

#define MAX7219_DECODE_REG (0x09)
#define MAX7219_INTENSITY_REG (0x0A)
#define MAX7219_SCANLIMIT_REG (0x0B)
#define MAX7219_SHUTDOWN_REG (0X0C)
#define MAX7219_DISPLAYTEST_REG (0x0F)
#define MAX7219_DIGIT_REG(pos) ((pos) + 1)
#define MAX7219_COLUMN_REG(pos) MAX7219_DIGIT_REG(pos)
#define MAX7219_NOOP_REG (0x00)

#define MAX7219_OFF (0x0)
#define MAX7219_ON (0x1)

#define NUM_OF_COLUMNS (8)

class MAX7219
{
private:
	int num_of_matrixes;
	byte DIN, LOAD, CLK;

public:
	MAX7219(byte, byte, byte, int);
	~MAX7219();
	void set_all_registers(byte, byte);
	void set_single_register(int, byte, byte);
	void clear_matrix();
	void init_max7219();
	void display(node*);
	void display_on();
	void display_off();
};

MAX7219::MAX7219(byte DIN, byte LOAD, byte CLK, int num_of_matrixes)
{
	this->DIN = DIN;
	this->LOAD = LOAD;
	this->CLK = CLK;
	this->num_of_matrixes = num_of_matrixes;
}

MAX7219::~MAX7219()
{
}

void MAX7219::set_all_registers(byte address, byte value)
{
	digitalWrite(LOAD, LOW);
	for (int i = 0; i < num_of_matrixes; i++)
	{
		shiftOut(DIN, CLK, MSBFIRST, address);
		shiftOut(DIN, CLK, MSBFIRST, value);
	}
	digitalWrite(LOAD, HIGH);
}

void MAX7219::set_single_register(int index, byte address, byte value)
{
	if (index >= 0 && index < num_of_matrixes)
	{
		digitalWrite(LOAD, LOW);
		for (int i = num_of_matrixes - 1; i >= 0; i--)
		{
			if (i == index)
				shiftOut(DIN, CLK, MSBFIRST, address);
			else
				shiftOut(DIN, CLK, MSBFIRST, MAX7219_NOOP_REG);
			shiftOut(DIN, CLK, MSBFIRST, value);
		}
		digitalWrite(LOAD, HIGH);
	}
}

void MAX7219::clear_matrix()
{
	for (int i = 0; i < NUM_OF_COLUMNS; i++)
		set_all_registers(MAX7219_COLUMN_REG(i), B00000000);
}

void MAX7219::init_max7219()
{
	pinMode(CLK, OUTPUT);
	pinMode(LOAD, OUTPUT);
	pinMode(DIN, OUTPUT);

	set_all_registers(MAX7219_DISPLAYTEST_REG, MAX7219_OFF);
	set_all_registers(MAX7219_INTENSITY_REG, 0x2);
	set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
	set_all_registers(MAX7219_SCANLIMIT_REG, 7);
	set_all_registers(MAX7219_DECODE_REG, B00000000);
	clear_matrix();
}

void MAX7219::display(node *snake_map)
{
	//this->set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_OFF);

	for (int i = 0; i < NUM_OF_COLUMNS; i++)
	{
		digitalWrite(LOAD, LOW);
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				byte value = 0x0;
				for (int m = 0; m < NUM_OF_COLUMNS - 1; m++)
				{
					byte data = ((((j*NUM_OF_COLUMNS + i) * 24) + snake_map + (k * NUM_OF_COLUMNS + m)))->val;
					if (data == 0x2)
						data = 0x1;
					value |= data;
					value <<= 1;
				}
				value |= (((j*NUM_OF_COLUMNS + i) * 24) + snake_map + (k * NUM_OF_COLUMNS + NUM_OF_COLUMNS - 1))->val;
				shiftOut(DIN, CLK, MSBFIRST, MAX7219_COLUMN_REG(i));
				shiftOut(DIN, CLK, MSBFIRST, value);
			}
		}
		digitalWrite(LOAD, HIGH);
	}

	//this->set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_ON);
}

inline void MAX7219::display_off()
{
	this->set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
}
inline void MAX7219::display_on()
{
	this->set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_ON);
}
