//
// Use multiple 8x8 dot matrix modules to display a marquee string
// http://www.icshop.com.tw/product_info.php/products_id/13181
//
// MAX7219 datasheet: https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf
//

// the MAX7219 address map (datasheet table 2)
#define MAX7219_DECODE_REG      (0x09)
#define MAX7219_INTENSITY_REG   (0x0A)
#define MAX7219_SCANLIMIT_REG   (0x0B)
#define MAX7219_SHUTDOWN_REG    (0X0C)
#define MAX7219_DISPLAYTEST_REG (0x0F)
#define MAX7219_COLUMN_REG(pos) ((pos) + 1)

// shutdown mode (datasheet table 3)
#define MAX7219_OFF             (0x0)
#define MAX7219_ON              (0x1)

// pin 13 of MAX7219 (CLK)
const int clock_pin = 10;
// pin 12 of MAX7219 (LOAD)
const int data_latch_pin = 9;
// pin 1 of MAX7219 (DIN)
const int data_input_pin = 8;

// number of columns of the display matrx
#define NUM_OF_COLUMNS  (8)

// define the number of chained matrixes
#define NUM_OF_MATRIXES (6)

// matrix pattern for "Hello,LinkIt7697"
const byte char_pattern[] =
{
  B00000000, B00000000, B01111111, B00001000, B00001000, B01111111, // H
  B00000000, B00000000, B00111000, B01010100, B01010100, B00011000, // e
  B00000000, B00000000, B01000001, B01111111, B01000000, B00000000, // l
  B00000000, B00000000, B01000001, B01111111, B01000000, B00000000, // l
  B00000000, B00000000, B00111000, B01000100, B01000100, B00111000, // o
  B00000000, B00000000, B10110000, B01110000, B00000000, B00000000, // ,
  B00000000, B00000000, B01111111, B01000000, B01000000, B01000000, // L
  B00000000, B00000000, B01001000, B01111010, B01000000, B00000000, // i
  B00000000, B00000000, B01111100, B00000100, B00000100, B01111000, // n
  B00000000, B00000000, B01111111, B00010000, B00101000, B01000100, // k
  B00000000, B00000000, B01000001, B01111111, B01000001, B00000000, // I
  B00000000, B00000000, B00001000, B01111110, B01001000, B00000000, // t
  B00000000, B00000000, B01100001, B00010001, B00001001, B00000111, // 7
  B00000000, B00000000, B00111110, B01001001, B01001001, B00110000, // 6
  B00000000, B00000000, B00000110, B01001001, B01001001, B00111110, // 9
  B00000000, B00000000, B01100001, B00010001, B00001001, B00000111, // 7
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000  // space
};

#define DISPLAY_COLUMN_LENGTH (sizeof(char_pattern))

void Run();

// update a specific register value of all MAX7219s
void set_all_registers(byte address, byte value)
{
	digitalWrite(data_latch_pin, LOW);

	for (int i = 0; i < NUM_OF_MATRIXES; i++)
	{
		shiftOut(data_input_pin, clock_pin, MSBFIRST, address);
		shiftOut(data_input_pin, clock_pin, MSBFIRST, value);
	}

	digitalWrite(data_latch_pin, HIGH);
}

void clear_all_matrix()
{
	// clear the dot matrix
	for (int i = 0; i < NUM_OF_COLUMNS; i++)
	{
		set_all_registers(MAX7219_COLUMN_REG(i), B00000000);
	}
}

void init_all_max7219()
{
	// disable test mode. datasheet table 10
	set_all_registers(MAX7219_DISPLAYTEST_REG, MAX7219_OFF);
	// set medium intensity. datasheet table 7
	set_all_registers(MAX7219_INTENSITY_REG, 0x1);
	// turn off display. datasheet table 3
	set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
	// drive 8 digits. datasheet table 8
	set_all_registers(MAX7219_SCANLIMIT_REG, 7);
	// no decode mode for all positions. datasheet table 4
	set_all_registers(MAX7219_DECODE_REG, B00000000);

	// clear matrix display
	clear_all_matrix();
}

void setup()
{
	// init pin states
	pinMode(clock_pin, OUTPUT);
	pinMode(data_latch_pin, OUTPUT);
	pinMode(data_input_pin, OUTPUT);

	// init MAX2719 states
	init_all_max7219();
	for (int i = 0; i < 3; i++)
	{
		set_all_registers(MAX7219_DISPLAYTEST_REG, MAX7219_ON);
		delay(500);
		set_all_registers(MAX7219_DISPLAYTEST_REG, MAX7219_OFF);
		delay(500);
	}
}

unsigned int starting_column_index = 0;

void loop()
{
}

void Run()
{
	int i, j;
	int target_column;

	// turn off display first
	set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_OFF);

	// update all columns
	for (i = 0; i < NUM_OF_COLUMNS; i++)
	{
		digitalWrite(data_latch_pin, LOW);

		// update all matrixes
		for (j = NUM_OF_MATRIXES - 1; j >= 0; j--)
		{
			// jump to the correct column position for each matrix
			target_column = starting_column_index + NUM_OF_COLUMNS * j + i;
			//  make sure the target column is within the bitmap array
			target_column %= DISPLAY_COLUMN_LENGTH;

			shiftOut(data_input_pin, clock_pin, MSBFIRST, MAX7219_COLUMN_REG(i));
			shiftOut(data_input_pin, clock_pin, MSBFIRST, char_pattern[target_column]);
		}

		// latch the data pin to make the register data takes effect
		digitalWrite(data_latch_pin, HIGH);
	}

	// turn on display
	set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_ON);

	// step to the next column
	starting_column_index++;
	// go back to the first column of the string bitmap to be displayed
	if (starting_column_index >= DISPLAY_COLUMN_LENGTH)
	{
		starting_column_index = 0;
	}

	delay(200);
}