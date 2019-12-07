/*
 Name:		keyboard_LED.ino
 Created:	2019/11/30 下午 08:30:52
 Author:	s2862
*/
#include <Keypad.h>

const byte LED_PIN[] = { 6,7,8,9 };

#define ROWS 4
#define COLS 4

uint8_t hexaKeys[ROWS][COLS] =
{
  {0x0F,0x0E,0x0D,0x0C},
  {0x0B,0x03,0x06,0x09},
  {0x0A,0x02,0x05,0x08},
  {0x1A,0x01,0x04,0x07}
};

byte rowPins[ROWS] = { 25, 24, 23, 22 };
byte colPins[COLS] = { 29, 28, 27, 26 };

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
	Serial.begin(115200);
	for (int i = 2; i <= 9; i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}

	pinMode(A15, OUTPUT);
	digitalWrite(A15, LOW);
}

void loop()
{
	//1.從鍵盤讀取字元
	uint8_t customKey = customKeypad.getKey();
	if (customKey)
	{
		//0x00例外處理
		customKey == 0x1A ? customKey = 0x00 : NULL;
		//2.讀取二進位每一個元
		for (int i = 0; i < 4; i++)
		{
			bool value = customKey & 1;
			//右位移1位元
			customKey >>= 1;
			//4.輸出到LED上
			digitalWrite(LED_PIN[i], !value);
		}
	}
}