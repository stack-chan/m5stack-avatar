#include <M5Stack.h>
#include "avator.h"

Avator *avator;
int count = 0;
float f = 0;

void drawLoop(void *args)
{
  for(;;)
  {
    avator->draw();
    delay(125);
  }
}

void setup()
{
  M5.begin();
  avator = new Avator();
  // M5.Lcd.setBrightness(60);
  xTaskCreatePinnedToCore(
                    drawLoop,     /* Function to implement the task */
                    "drawLoop",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    1,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    0);        /* Core where the task should run */
}

void loop()
{
  M5.update();
  count = (count + 5) % 100;
  f = count * 2 * PI / 100.0;
  avator->setMouthOpen((sin(f) + 1) / 2);
  if (count % 100 == 90)
  {
    avator->setEyeOpen(0);
  }
  if (count % 100 == 0)
  {
    avator->setEyeOpen(1);
    count = random(50);
  }
  // avator->draw();
  delay(125);
}
