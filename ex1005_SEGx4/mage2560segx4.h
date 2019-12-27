#pragma once
#define CA1 30
#define CA2 31
#define CA3 32

byte segs_pin[] = { 2, 3, 4, 5, 6, 7, 8 };

byte seven_seg_digits[10][7] =
{
    {0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1},
    {0, 0, 1, 0, 0, 1, 0},
    {0, 0, 0, 0, 1, 1, 0},
    {1, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0} };

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

class segx4
{
private:
    void pickDigit(byte x);
public:
    segx4();
    ~segx4();
    void init(void);
    void show(String num);
};

segx4::segx4()
{
}

segx4::~segx4()
{
}

inline void segx4::init(void)
{
    for (int i = 0; i < 7; i++)
        pinMode(segs_pin[i], OUTPUT);
    for (byte i = CA1; i <= CA3; i++)
        pinMode(i, OUTPUT);
    pinMode(A13, OUTPUT);
    digitalWrite(A13, LOW);
}

void segx4::pickDigit(byte x)
{
    for (int i = 0, j = CA3; i < 3; i++, j--)
        digitalWrite(j, _74LS138[x][i]);
}

void segx4::show(String num)
{
    int num_len = num.length();
    for (byte i = 0; i < num_len; i++)
    {
        byte n = num[num_len - 1 - i] - 48;
        pickDigit(i);
        for (int i = 0; i < 7; i++)
            digitalWrite(segs_pin[i], seven_seg_digits[n][i]);
        delay(4);
    }
}
