//
// Use one MAX7219 to control 5 8x8 dot matrixes
// http://www.icshop.com.tw/product_info.php/products_id/13181
//
// MAX7219 datasheet: https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf
//

// the MAX7219 address map (datasheet table 2)
#define MAX7219_DECODE_REG (0x09)
#define MAX7219_INTENSITY_REG (0x0A)
#define MAX7219_SCANLIMIT_REG (0x0B)
#define MAX7219_SHUTDOWN_REG (0X0C)
#define MAX7219_DISPLAYTEST_REG (0x0F)
#define MAX7219_DIGIT_REG(pos) ((pos) + 1)
#define MAX7219_COLUMN_REG(pos) MAX7219_DIGIT_REG(pos)
#define MAX7219_NOOP_REG (0x00)

// shutdown mode (datasheet table 3)
#define MAX7219_OFF (0x0)
#define MAX7219_ON (0x1)

// pin 13 of MAX7219 (CLK)
const int clock_pin = 15;
// pin 12 of MAX7219 (LOAD)
const int data_latch_pin = 16;
// pin 1 of MAX7219 (DIN)
const int data_input_pin = 17;

// number of columns of the display matrx
#define NUM_OF_COLUMNS (8)
// for each character bitmap, it consumes 4 bytes
#define BYTE_PER_MAP (4)
// define the number of chained matrixes
#define NUM_OF_MATRIXES (5)

// matrix pattern for "Hello,LinkIt7697"
const byte char_pattern[] =
    {
        B01111111, B00001000, B00001000, B01111111, // H
        B00111000, B01010100, B01010100, B00011000, // e
        B01000001, B01111111, B01000000, B00000000, // l
        B01000001, B01111111, B01000000, B00000000, // l
        B00111000, B01000100, B01000100, B00111000, // o
        B10110000, B01110000, B00000000, B00000000, // ,
        B01111111, B01000000, B01000000, B01000000, // L
        B01001000, B01111010, B01000000, B00000000, // i
        B01111100, B00000100, B00000100, B01111000, // n
        B01111111, B00010000, B00101000, B01000100, // k
        B01000001, B01111111, B01000001, B00000000, // I
        B00001000, B01111110, B01001000, B00000000, // t
        B01100001, B00010001, B00001001, B00000111, // 7
        B00111110, B01001001, B01001001, B00110000, // 6
        B00000110, B01001001, B01001001, B00111110, // 9
        B01100001, B00010001, B00001001, B00000111, // 7
        B00000000, B00000000, B00000000, B00000000  // space
};

#define DISPLAY_STR_LENGTH (sizeof(char_pattern) / BYTE_PER_MAP) //17

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

// only update the register in one MAX7219
void set_single_register(int index, byte address, byte value)
{
    // only process for valid index range
    if (index >= 0 && index < NUM_OF_MATRIXES)
    {
        digitalWrite(data_latch_pin, LOW);

        for (int i = NUM_OF_MATRIXES - 1; i >= 0; i--)
        {
            // for specified MAX7219, access the desired register
            if (i == index)
            {
                shiftOut(data_input_pin, clock_pin, MSBFIRST, address);
            }
            else
            {
                // send No-Op operation to all other MAX7219s (the value is "don't-care" for No-Op command)
                shiftOut(data_input_pin, clock_pin, MSBFIRST, MAX7219_NOOP_REG);
            }

            shiftOut(data_input_pin, clock_pin, MSBFIRST, value);
        }

        digitalWrite(data_latch_pin, HIGH);
    }
}

void clear_matrix()
{
    // clear the dot matrix
    for (int i = 0; i < NUM_OF_COLUMNS; i++)
    {
        set_all_registers(MAX7219_COLUMN_REG(i), B00000000);
    }
}

void init_max7219()
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
    clear_matrix();
}

void setup()
{
    // init pin states
    pinMode(clock_pin, OUTPUT);
    pinMode(data_latch_pin, OUTPUT);
    pinMode(data_input_pin, OUTPUT);

    // init MAX2719 states
    init_max7219();
}

unsigned int char_index = 0;
unsigned int matrix_index = 0;

void loop()
{
    int i;

    // turn off display first
    set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_OFF);

    // display one bitmap
    for (i = 0; i < BYTE_PER_MAP; i++)
    {
        // starting from column 2
        set_single_register(matrix_index, MAX7219_COLUMN_REG(2 + i), char_pattern[char_index * BYTE_PER_MAP + i]);
    }

    // turn on display
    set_all_registers(MAX7219_SHUTDOWN_REG, MAX7219_ON);

    // step to the next character
    char_index++;
    // wrap around the character if needed
    if (char_index >= DISPLAY_STR_LENGTH)
    {
        char_index = 0;

        // move to the next matrix
        matrix_index++;

        if (matrix_index >= NUM_OF_MATRIXES)
        {
            clear_matrix();
            matrix_index = 0;
        }
    }

    delay(400);
}