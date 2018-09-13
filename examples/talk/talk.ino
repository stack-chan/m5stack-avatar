#include <AquesTalkTTS.h>
#include <Avatar.h>
#include <M5Stack.h>
#include <tasks/LipSync.h>

using namespace m5avatar;

// AquesTalk License Key
// NULL or wrong value is just ignored
const char* AQUESTALK_KEY = "XXXX-XXXX-XXXX-XXXX";

Avatar avatar;
void setup() {
  int iret;
  M5.begin();
  // For Kanji-to-speech mode (requires dictionary file saved on microSD)
  // See http://blog-yama.a-quest.com/?eid=970195
  // iret = TTS.createK(AQUESTALK_KEY);
  iret = TTS.create(AQUESTALK_KEY);
  M5.Lcd.setBrightness(30);
  M5.Lcd.clear();
  avatar.init();
  avatar.addTask(lipSync, "lipSync");
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    // Need to initialize with createK(AQUESTALK_KEY)
    // TTS.play("こんにちは。", 80);
    TTS.play("konnichiwa", 80);
    avatar.setSpeechText("Hello");
    delay(1000);
    avatar.setSpeechText("");
  }
}
