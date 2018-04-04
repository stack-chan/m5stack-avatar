#include <M5Stack.h>
#include "avator.h"

Avator avator;
int count = 0;

void setup()
{
  M5.begin();
  M5.Lcd.setBrightness(60);
}

void loop()
{
  M5.update();
  count++;
  avator.openMouth(count * 10 % 100);
  delay(1000);
}
