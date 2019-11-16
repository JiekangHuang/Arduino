#define Ls138_A 30             // 定義 74138 A 腳位
#define Ls138_B 31             // 定義 74138 B 腳位
#define Ls138_C 32             // 定義 74138 C 腳位
#define R0 2             // 定義 8x8點矩陣LED ROW0連接腳位
#define R1 3             // 定義 8x8點矩陣LED ROW1連接腳位
#define R2 4             // 定義 8x8點矩陣LED ROW2連接腳位
#define R3 5             // 定義 8x8點矩陣LED ROW3連接腳位
#define R4 6             // 定義 8x8點矩陣LED ROW4連接腳位
#define R5 7             // 定義 8x8點矩陣LED ROW5連接腳位
#define R6 8             // 定義 8x8點矩陣LED ROW6連接腳位
#define R7 9             // 定義 8x8點矩陣LED ROW7連接腳位
#define row_size 8          // 定義 Matrix row 大小
#define col_size 8          // 定義 Matrix colum 小
#define delay_time 300       // 延遲時間
//#define display_Number 2     //顯示字的數目
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
                0, 0, 0, 0, 0, 0, 0, 0,\
                0, 0, 0, 0, 0, 0, 0, 0}                              

// 所有要顯示字的 array
boolean word_array[4][row_size][col_size] = { data_A,data_N,data_0 ,data_1};

// LED Matrix
boolean led[row_size][col_size];
// 水平方向 led
byte row_pin[row_size] = { R0, R1, R2, R3, R4, R5, R6, R7 };



void word_to_led(int n) {          // 將第 n 個 word 讀入 led
  for (int i = 0; i < row_size; i++)
    for (int j = 0; j < col_size; j++)
      led[i][j] = word_array[n][i][j];
}

void clear_led() {    // 將 led 全關
  for (int i = 0; i < row_size; i++)
    digitalWrite(row_pin[i], LOW);
}

void display_led(boolean led[row_size][col_size], int continue_time) {
  for (int k = 0; k < continue_time; k++) {
    for (int i = 0; i < col_size; i++) {
      clear_led();
      low_74138pin(i);
      for (int j = 0; j < row_size; j++)
        if (led[j][i] == 1)
          digitalWrite(row_pin[j], HIGH);
    }
  }
}

void low_74138pin(int num) {
  switch (num) {
  case 0:
    digitalWrite(Ls138_A, LOW);
    digitalWrite(Ls138_B, LOW);
    digitalWrite(Ls138_C, LOW);
    break;
  case 1:
    digitalWrite(Ls138_A, HIGH);
    digitalWrite(Ls138_B, LOW);
    digitalWrite(Ls138_C, LOW);
    break;
  case 2:
    digitalWrite(Ls138_A, LOW);
    digitalWrite(Ls138_B, HIGH);
    digitalWrite(Ls138_C, LOW);
    break;
  case 3:
    digitalWrite(Ls138_A, HIGH);
    digitalWrite(Ls138_B, HIGH);
    digitalWrite(Ls138_C, LOW);
    break;
  case 4:
    digitalWrite(Ls138_A, LOW);
    digitalWrite(Ls138_B, LOW);
    digitalWrite(Ls138_C, HIGH);
    break;
  case 5:
    digitalWrite(Ls138_A, HIGH);
    digitalWrite(Ls138_B, LOW);
    digitalWrite(Ls138_C, HIGH);
    break;
  case 6:
    digitalWrite(Ls138_A, LOW);
    digitalWrite(Ls138_B, HIGH);
    digitalWrite(Ls138_C, HIGH);
    break;
  case 7:
    digitalWrite(Ls138_A, HIGH);
    digitalWrite(Ls138_B, HIGH);
    digitalWrite(Ls138_C, HIGH);
    break;
  }
}

void setup()   // 初始設定
{
  pinMode(Ls138_A, OUTPUT);
  pinMode(Ls138_B, OUTPUT);
  pinMode(Ls138_C, OUTPUT);
  pinMode(R0, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  clear_led();
  pinMode(A14, OUTPUT);
  digitalWrite(A14, LOW);
}

void loop() {         // 主程式迴圈
  for(int i=0;i<4;i++)
  {
    word_to_led(i);    
    display_led(led, 1000);  
    clear_led();
    delay(delay_time);
  }
}
