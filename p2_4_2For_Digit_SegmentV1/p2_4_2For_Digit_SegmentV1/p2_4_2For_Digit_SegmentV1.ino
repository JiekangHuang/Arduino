//使用四位數七段顯示器當計數器

// 定義共陽極與 Arduino 的腳位對應關係
#define CA1 30
#define CA2 31
#define CA3 32

// 定義每個七段顯示器顯示的時間 (延遲時間), 預設 1ms
int delay_time = 4;

void setup() {
	pinMode(2, OUTPUT);  //14 > 2 A
	pinMode(3, OUTPUT);  //13 > 3 B
	pinMode(4, OUTPUT);  // 8 > 4 C
	pinMode(5, OUTPUT);  // 7 > 5 D
	pinMode(6, OUTPUT);  // 6 > 6 E
	pinMode(7, OUTPUT);  // 2 > 7 F
	pinMode(8, OUTPUT);  // 1 > 8 G
	pinMode(9, OUTPUT);  //RDP> 9 decimal point
	digitalWrite(9, HIGH);
	pinMode(CA1, OUTPUT);
	pinMode(CA2, OUTPUT);
	pinMode(CA3, OUTPUT);
	pinMode(A13, OUTPUT);
	digitalWrite(A13, LOW);
}

void loop() {
	// 從 0000 計數到 9999
	for (unsigned int number = 0; number < 10000; number++) {
		// 每一秒鐘計數一次
		unsigned long startTime = millis();
		for (unsigned long elapsed = 0; elapsed < 300; elapsed = millis() - startTime) {
			// 多工掃瞄，輪流點亮個、十、百、以及千位數的七段顯示器

			// 顯示個位數
			pickDigit(1);
			pickNumber(number % 10);
			delay(delay_time);
			// 顯示十位數
			pickDigit(2);
			pickNumber((number / 10) % 10);
			delay(delay_time);
			// 顯示百位數
			pickDigit(3);
			pickNumber((number / 100) % 10);
			delay(delay_time);
			// 顯示千位數
			pickDigit(4);
			pickNumber((number / 1000) % 10);
			delay(delay_time);
		}
	}
}

// 選擇顯示的位數 (4:千、3:百、2:十、或 1:個位數)
void pickDigit(int x) {
	digitalWrite(CA1, HIGH);
	digitalWrite(CA2, HIGH);
	digitalWrite(CA3, HIGH);

	switch (x) {
	case 1: digitalWrite(CA1, LOW); digitalWrite(CA2, LOW); digitalWrite(CA3, LOW); break;
	case 2: digitalWrite(CA1, HIGH); digitalWrite(CA2, LOW); digitalWrite(CA3, LOW); break;
	case 3: digitalWrite(CA1, LOW); digitalWrite(CA2, HIGH); digitalWrite(CA3, LOW); break;
	case 4: digitalWrite(CA1, HIGH); digitalWrite(CA2, HIGH); digitalWrite(CA3, LOW); break;
	}
}

void pickNumber(int x) {
	switch (x) {
	case 1: one(); break;
	case 2: two(); break;
	case 3: three(); break;
	case 4: four(); break;
	case 5: five(); break;
	case 6: six(); break;
	case 7: seven(); break;
	case 8: eight(); break;
	case 9: nine(); break;
	default: zero(); break;
	}
}

// 顯示數字 '1'
void one() {
	digitalWrite(2, HIGH);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(7, HIGH);
	digitalWrite(8, HIGH);
}

// 顯示數字 '2'
void two() {
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, HIGH);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(7, HIGH);
	digitalWrite(8, LOW);
}

// 顯示數字 '3'
void three() {
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, HIGH);
	digitalWrite(7, HIGH);
	digitalWrite(8, LOW);
}

// 顯示數字 '4'
void four() {
	digitalWrite(2, HIGH);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(7, LOW);
	digitalWrite(8, LOW);
}

// 顯示數字 '5'
void five() {
	digitalWrite(2, LOW);
	digitalWrite(3, HIGH);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, HIGH);
	digitalWrite(7, LOW);
	digitalWrite(8, LOW);
}

// 顯示數字 '6'
void six() {
	digitalWrite(2, LOW);
	digitalWrite(3, HIGH);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(7, LOW);
	digitalWrite(8, LOW);
}

// 顯示數字 '7'
void seven() {
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(7, HIGH);
	digitalWrite(8, HIGH);
}

// 顯示數字 '8'
void eight() {
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(7, LOW);
	digitalWrite(8, LOW);
}

// 顯示數字 '9'
void nine() {
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, HIGH);
	digitalWrite(7, LOW);
	digitalWrite(8, LOW);
}

// 顯示數字 '0'
void zero() {
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(7, LOW);
	digitalWrite(8, HIGH);
}