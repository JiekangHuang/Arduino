#include <TimedAction.h>
#include "mage2560segx4.h"

String text[] = { "2019", "1228" };
uint16_t text_num[] = { 2020,1223 };
byte idx = 0, re = 1;

void action(void);

TimedAction run(500, action);
segx4 seg;

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	run.check();
	seg.show_str_num(text_num[idx]);
}

void action(void)
{
	idx += re;
	re = -re;
}