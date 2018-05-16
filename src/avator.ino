#include <M5Stack.h>
#include "avator.h"
#include "const.h"
#include <AquesTalkTTS.h>

using namespace m5avator;

Avator *avator;
int count = 0;
float f = 0;
float last = 0;
const Expression expressions[] = {
  Angry,
  Sleepy,
  Happy,
  Sad
};
const int expressionsSize = sizeof(expressions) / sizeof(Expression);
int idx = 0;
bool isShowingQR = false;

void breath(void *args)
{
  int c = 0;
  for(;;)
  {
    c = c + 1 % 100;
    float f = sin(c * 2 * PI / 100.0);
    avator->setBreath(f);
    delay(33);
  }
}

void drawLoop(void *args)
{
  for(;;)
  {
    int level = TTS.getLevel();
    float f = level / 12000.0;
    float open = min(1.0, last + f / 2.0);
    // count += 3;
    // float f0 = ((count % 360) / 180.0) * PI;
    // float open = (sin(f0) + 1.0) / 2.0;
    last = f;
    avator->setMouthOpen(open);
    if (!isShowingQR)
    {
      avator->draw();
    }
    delay(33);
  }
}

void saccade(void *args)
{
  for(;;)
  {
    float vertical = (float)rand()/(float)(RAND_MAX / 2) - 1;
    float horizontal = (float)rand()/(float)(RAND_MAX / 2) - 1;
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
  iret = TTS.create(AQUESTALK_KEY);
  M5.begin();
  M5.Lcd.setBrightness(30);
  M5.Lcd.clear();
  avator = new Avator();
  xTaskCreatePinnedToCore(
                    drawLoop,     /* Function to implement the task */
                    "drawLoop",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    1,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    1);        /* Core where the task should run */
  xTaskCreatePinnedToCore(
                    saccade,     /* Function to implement the task */
                    "saccade",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    3,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    1);        /* Core where the task should run */
  xTaskCreatePinnedToCore(
                    breath,     /* Function to implement the task */
                    "breath",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    2,         /* Priority of the task */
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
    TTS.play("yukkuri/shiteittene?", 100);
  }
  if (M5.BtnB.wasPressed())
  {
    if(!isShowingQR)
    {
      TTS.play("haiyo", 80);
      delay(800);
    }
    isShowingQR = !isShowingQR;
    delay(200);
    if (isShowingQR)
    {
      M5.Lcd.setBrightness(10);
      M5.Lcd.qrcode("https://twitter.com/meganetaaan");
    }
    else
    {
      M5.Lcd.setBrightness(30);
    }
  }
  delay(125);
}
