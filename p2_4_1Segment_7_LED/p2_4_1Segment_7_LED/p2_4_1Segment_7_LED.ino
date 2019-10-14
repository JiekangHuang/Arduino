//                                    Arduino pin: 2,3,4,5,6,7,8

byte seven_seg_digits[10][7] = { { 0,0,0,0,0,0,1 },  // = 0 x
									  { 1,0,0,1,1,1,1 },  // = 1 x
									  { 0,0,1,0,0,1,0 },  // = 2 x
									  { 0,0,0,0,1,1,0 },  // = 3 x
									  { 1,0,0,1,1,0,0 },  // = 4 x
									  { 0,1,0,0,1,0,0 },  // = 5 x
									  { 0,1,0,0,0,0,0 },  // = 6 x
									  { 0,0,0,1,1,1,1 },  // = 7 x
									  { 0,0,0,0,0,0,0 },  // = 8 x
									  { 0,0,0,1,1,0,0 }   // = 9 x
};

// set the Arduino pins connected to the LED segments on Radio Shack 276-075
// which is National Semiconductor ELS-321HDB/A (very different from
// standard 7-seg display
// comment list below is LED pin# > Arduino pin# | segment name

void setup() {
	pinMode(2, OUTPUT);  //14 > 2 A
	pinMode(3, OUTPUT);  //13 > 3 B
	pinMode(4, OUTPUT);  // 8 > 4 C
	pinMode(5, OUTPUT);  // 7 > 5 D
	pinMode(6, OUTPUT);  // 6 > 6 E
	pinMode(7, OUTPUT);  // 2 > 7 F
	pinMode(8, OUTPUT);  // 1 > 8 G
	pinMode(9, OUTPUT);  //RDP> 9 decimal point
	writeDot(1);  // start with the "dot" off
	pinMode(A13, OUTPUT);
	digitalWrite(A13, LOW); //LED輸出
	pinMode(30, OUTPUT); pinMode(31, OUTPUT); pinMode(32, OUTPUT);
	digitalWrite(32, LOW); digitalWrite(31, LOW); digitalWrite(30, LOW);
}

void writeDot(byte dot) {
	digitalWrite(9, dot); // decimal point - pin 9 on Arduino
}

void sevenSegWrite(byte digit) {
	byte pin = 2; // Arduino pin where the segment list starts
	for (byte segCount = 0; segCount < 7; ++segCount) {
		digitalWrite(pin, seven_seg_digits[digit][segCount]);
		++pin;
	}
}

// displays digits from 9 to 0
void loop() {
	for (byte count = 0; count < 10; count++) {
		delay(1000);
		sevenSegWrite(count);
	}
	// delay(1000);
}