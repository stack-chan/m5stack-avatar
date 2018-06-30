#include <M5Stack.h>
#include "Avatar.h"
#include "const.h"
#include <AquesTalkTTS.h>
#include "tasks/LipSync.h"

using namespace m5avatar;

Avatar *avatar;
void setup()
{
  int iret;
  iret = TTS.create(AQUESTALK_KEY);
  M5.begin();
  M5.Lcd.setBrightness(30);
  M5.Lcd.clear();
  avatar = new Avatar();

  avatar->init();
  avatar->addTask(lipSync, "lipSync");
}

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed())
  {
    TTS.play("konnichiwa", 80);
    avatar->setSpeechText("Hello");
    delay(1000);
    avatar->setSpeechText("");
  }
}
