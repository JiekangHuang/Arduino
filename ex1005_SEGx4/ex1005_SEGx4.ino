#include <TimedAction.h>
#include "mage2560segx4.h"

String text[] = { "2019", "1005" };
unsigned long pre_time;
byte idx = 0, re = 1;

void action(void);

TimedAction run(500, action);
segx4 seg;

void setup()
{
    seg.init();
}

void loop()
{
    run.check();
    seg.show(text[idx]);
}

void action(void)
{
    pre_time = millis();
    idx += re;
    re = -re;
}