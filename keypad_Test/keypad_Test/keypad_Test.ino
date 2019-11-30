/*
   p2_9_1.ino
*/

#include <Keypad.h>                 // 加入Keypad函式庫

const byte ROWS = 4;                // 設定鍵盤為4列
const byte COLS = 4;                // 設定鍵盤為4行

char hexaKeys[ROWS][COLS] = {       // 定義Keypad的按鍵
  {'F','E','D','C'},
  {'B','3','6','9'},
  {'A','2','5','8'},
  {'0','1','4','7'}
};
byte rowPins[ROWS] = { 25, 24, 23, 22 }; // 定義Arduino的接腳接到Keypad的Row1, Row2, Row3, Row4ypad
byte colPins[COLS] = { 29, 28, 27, 26 }; // 定義Arduino的接腳接到Keypad的Col1, Col2, Col3, Col4

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); // 建立Keypad物件

void setup() {
	Serial.begin(9600);                 // 將串列埠通訊鮑率設為9600bps
}

void loop() {
	char customKey = customKeypad.getKey();   // 讀取鍵盤的輸入
	//if (customKey) {                           // 判別有按鍵按下時
	Serial.println(customKey != NULL);              // 按鍵輸出至序列埠觀測視窗
//}
}