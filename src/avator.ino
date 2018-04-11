#include <M5Stack.h>
#include "avator.h"

Avator *avator;
int count = 0;

void setup()
{
  M5.begin();
  avator = new Avator();
  // M5.Lcd.setBrightness(60);
  avator->init();
}

void loop()
{
  M5.update();
  count = (count + 1) % 100;
  float f = count / 100.0;
  Serial.printf("%f\n", f);
  avator->setMouthOpen(f);
  if (count % 100 == 90)
  {
    avator->setEyeOpen(0);
  }
  if (count % 100 == 0)
  {
    avator->setEyeOpen(1);
    count = random(50);
  }
  avator->draw();
  delay(100);
}
