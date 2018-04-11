#include <M5Stack.h>
#include "avator.h"

Avator *avator;
int count = 0;

void setup()
{
  avator = new Avator();
  M5.begin();
  M5.Lcd.setBrightness(60);
  avator->init();
}

void loop()
{
  M5.update();
  count++;
  int percent = count * 10 % 100;
  avator->openMouth(count % 100);
  if (count % 100 == 90)
  {
    avator->openEye(false);
  }
  if (count % 100 == 0)
  {
    avator->openEye(true);
    count = random(50);
  }
  delay(50);
}
