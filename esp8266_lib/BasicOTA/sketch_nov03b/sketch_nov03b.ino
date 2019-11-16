#define row_size 8
#define col_size 8
#define delay_time 300
const int data_A[row_size] = {
  B00011000,
  B00100100,
  B00100100,
  B01000010,
  B01111110,
  B01000010,
  B01000010,
  B01000010 };

const int  data_N[row_size] = {
  B01000010,
  B01100010,
  B01100010,
  B01010010,
  B01001010,
  B01000110,
  B01000110,
  B01000010 };

int word_array[4][row_size] = { *data_A };
void setup() {
  Serial.begin(9600);
}

void loop() {

      Serial.println((word_array[0][0]+8));
}
