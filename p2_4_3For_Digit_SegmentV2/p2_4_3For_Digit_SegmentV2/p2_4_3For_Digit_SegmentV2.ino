// 四位數七段顯示器當計數器 V2

// 定義共陽極與 Arduino 的腳位對應關係
#define CA1 30
#define CA2 31
#define CA3 32

// 定義七個節段的腳位，將 A, B, C, D, E, F, G 依序放入陣列
byte segs[7] = { 2, 3, 4, 5, 6, 7, 8 };

// 定義共陽極七段顯示器的字型(digit pattern)
// define the LED digit patterns, from 0 - 9
// 0 = LED on, 1 = LED off, in this order:
//                Mapping to       a,b,c,d,e,f,g of Seven-Segment LED
byte seven_seg_digits[10][7] = { { 0,0,0,0,0,0,1 },  // = 0
								 { 1,0,0,1,1,1,1 },  // = 1
								 { 0,0,1,0,0,1,0 },  // = 2
								 { 0,0,0,0,1,1,0 },  // = 3
								 { 1,0,0,1,1,0,0 },  // = 4
								 { 0,1,0,0,1,0,0 },  // = 5
								 { 0,1,0,0,0,0,0 },  // = 6
								 { 0,0,0,1,1,1,1 },  // = 7
								 { 0,0,0,0,0,0,0 },  // = 8
								 { 0,0,0,1,1,0,0 }   // = 9
};

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
			lightDigit1(number % 10);
			delay(delay_time);
			// 顯示十位數
			lightDigit2((number / 10) % 10);
			delay(delay_time);
			// 顯示百位數
			lightDigit3((number / 100) % 10);
			delay(delay_time);
			// 顯示千位數
			lightDigit4((number / 1000) % 10);
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

// 點亮個位數
void lightDigit1(byte number) {
	pickDigit(1);
	lightSegments(number);
}

// 點亮十位數
void lightDigit2(byte number) {
	pickDigit(2);
	lightSegments(number);
}

// 點亮百位數
void lightDigit3(byte number) {
	pickDigit(3);
	lightSegments(number);
}

// 點亮千位數
void lightDigit4(byte number) {
	pickDigit(4);
	lightSegments(number);
}

// 點亮七段顯示器
void lightSegments(byte number) {
	for (int i = 0; i < 7; i++) {
		digitalWrite(segs[i], seven_seg_digits[number][i]);
	}
}