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

void saccade(void *args)
{
  for(;;)
  {
    float vertical = random(-1, 1);
    float horizontal = random(-1, 1);
    avator->setGaze(vertical, horizontal);
    delay(500 + 100 * random(20));
  }
}

void blink(void *args)
{
  for(;;)
  {
    avator->setEyeOpen(1);
    delay(2500 + 100 * random(20));
    avator->setEyeOpen(0);
    delay(300 + 10 * random(20));
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
  xTaskCreatePinnedToCore(
                    saccade,     /* Function to implement the task */
                    "saccade",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    3,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    1);        /* Core where the task should run */
  xTaskCreatePinnedToCore(
                    blink,     /* Function to implement the task */
                    "blink",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    2,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    1);        /* Core where the task should run */
}

void loop()
{
  M5.update();
  count = (count + 5) % 100;
  f = count * 2 * PI / 100.0;
  avator->setMouthOpen((sin(f) + 1) / 4);
  delay(125);
}
