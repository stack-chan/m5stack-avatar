#include <M5Stack.h>
#include "avator.h"
#include <AquesTalkTTS.h>
#include <FastLCD.h>

Avator *avator;
int count = 0;
float f = 0;
float last = 0;

void drawLoop(void *args)
{
  for(;;)
  {
    int level = TTS.getLevel();
    float f = level / 12000.0;
    float open = min(1.0, last + f / 2.0);
    last = f;
    avator->setMouthOpen(open);
    avator->draw();
    delay(33);
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
  int iret;

  iret = TTS.create(NULL);
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
  if (M5.BtnA.wasPressed())
  {
    TTS.play("to-kyo-tokkyo;kyokakyoku", 100);
  }
  delay(125);
}
