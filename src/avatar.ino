#include <M5Stack.h>
#include "Avatar.h"
#include "const.h"
#include <AquesTalkTTS.h>

using namespace m5avatar;

Avatar *avatar;
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

void setup()
{
  int iret;
  iret = TTS.create(AQUESTALK_KEY);
  M5.begin();
  M5.Lcd.setBrightness(30);
  M5.Lcd.clear();
  avatar = new Avatar();
  avatar->init();
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
