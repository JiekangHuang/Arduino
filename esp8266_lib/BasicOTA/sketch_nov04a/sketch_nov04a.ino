#include <TimedAction.h>

#define Ls138_b 30
#define Ls138_e 32

#define row_size 8
#define col_size 8
#define delay_time 300

#define data_A {0, 0, 0, 1, 1, 0, 0, 0,\
                0, 0, 1, 0, 0, 1, 0, 0,\
                0, 0, 1, 0, 0, 1, 0, 0,\
                0, 1, 0, 0, 0, 0, 1, 0,\
                0, 1, 1, 1, 1, 1, 1, 0,\
                0, 1, 0, 0, 0, 0, 1, 0,\
                0, 1, 0, 0, 0, 0, 1, 0,\
                0, 1, 0, 0, 0, 0, 1, 0}

#define data_N {0, 1, 0, 0, 0, 0, 1, 0,\
                0, 1, 1, 0, 0, 0, 1, 0,\
                0, 1, 1, 0, 0, 0, 1, 0,\
                0, 1, 0, 1, 0, 0, 1, 0,\
                0, 1, 0, 0, 1, 0, 1, 0,\
                0, 1, 0, 0, 0, 1, 1, 0,\
                0, 1, 0, 0, 0, 1, 1, 0,\
                0, 1, 0, 0, 0, 0, 1, 0}
                
#define data_1 {1, 1, 1, 1, 1, 1, 1, 1,\
                1, 1, 1, 1, 1, 1, 1, 1,\
                1, 1, 1, 1, 1, 1, 1, 1,\
                1, 1, 1, 1, 1, 1, 1, 1,\
                1, 1, 1, 1, 1, 1, 1, 1,\
                1, 1, 1, 1, 1, 1, 1, 1,\
                1, 1, 1, 1, 1, 1, 1, 1,\
                1, 1, 1, 1, 1, 1, 1, 1}  
                
#define data_0 {0, 0, 0, 0, 0, 0, 0, 0,\
                0, 0, 0, 0, 0, 0, 0, 0,\
                0, 0, 0, 0, 0, 0, 0, 0,\
                0, 0, 0, 0, 0, 0, 0, 0,\
                0, 0, 0, 0, 0, 0, 0, 0,\
                0, 0, 0, 0, 0, 0, 0, 0,\
                0, 0, 0, 0, 0, 0, 0, 1,\
                0, 0, 0, 0, 0, 0, 0, 0}                              

// 所有要顯示字的 array
boolean word_array[4][row_size][col_size] = { data_A,data_N,data_0 ,data_1};
boolean led[row_size][col_size];
//const int word_array[][row_size] =
//{
//  //A
//   {B00011000,
//  B00100100,
//  B00100100,
//  B01000010,
//  B01111110,
//  B01000010,
//  B01000010,
//  B01000010 },
//  //N
//   {B01000010,
//  B01100010,
//  B01100010,
//  B01010010,
//  B01001010,
//  B01000110,
//  B01000110,
//  B01000010 },
//
//   {B00000000,
//  B00000000,
//  B00000000,
//  B00000000,
//  B00000000,
//  B00000000,
//  B00000000,
//  B00000000 },
//
//   {B11111111,
//  B11111111,
//  B11111111,
//  B11111111,
//  B11111111,
//  B11111111,
//  B11111111,
//  B11111111 },
//
//   {B00000000,
//  B00000000,
//  B00000000,
//  B00000000,
//  B00000000,
//  B00000000,
//  B00000001,
//  B00000000 }
//};

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

//int led[row_size];
byte row_pin[row_size] = { 2, 3, 4, 5, 6, 7, 8, 9 };

void word_to_led(int);
void display_led(int led[row_size]);
void low_74138pin(int);

void setup()
{
  Serial.begin(9600);
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
  word_to_led(0);
  display_led(led);
}
void word_to_led(int n) {          // 將第 n 個 word 讀入 led
  for (int i = 0; i < row_size; i++)
    for (int j = 0; j < col_size; j++)
      led[i][j] = word_array[n][i][j];
}

void clear_led()
{
  for (int i = 0; i < row_size; i++)
    digitalWrite(row_pin[i], LOW);
}

void display_led(boolean led[row_size][col_size])
{
  for (int i = 0; i < col_size; i++) {
      clear_led();
      low_74138pin(i);
      for (int j = 0; j < row_size; j++)
        if (led[j][i] == 1)
          digitalWrite(row_pin[j], HIGH);
    }
}

void low_74138pin(int num)
{
  for (int i = 0, j = Ls138_e; i < 3; i++, j--)
    digitalWrite(j, _74LS138[num][i]);
}
