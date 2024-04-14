#include <Avatar.h>
#include <M5Unified.h>

m5avatar::Avatar avatar;

void setup() {
  M5.begin();
  avatar.init();  // start drawing
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    // switch right eye
    avatar.setRightEyeOpenRatio(avatar.getRightEyeOpenRatio() > 0.5f ? 0.0f
                                                                     : 1.0f);
  }
  if (M5.BtnB.wasPressed()) {
    avatar.setIsAutoBlink(!avatar.getIsAutoBlink());
  }
  if (M5.BtnC.wasPressed()) {
    // switch left eye
    avatar.setLeftEyeOpenRatio(avatar.getLeftEyeOpenRatio() > 0.5f ? 0.0f
                                                                   : 1.0f);
  }
  delay(10);
}
