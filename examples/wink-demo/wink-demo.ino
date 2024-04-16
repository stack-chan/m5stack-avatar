#include <Avatar.h>
#include <M5Unified.h>

m5avatar::Avatar avatar;
m5avatar::ColorPalette* palettes[2];

void setup() {
  M5.begin();

  palettes[0] = new m5avatar::ColorPalette();
  palettes[1] = new m5avatar::ColorPalette();
  palettes[1]->set(COLOR_PRIMARY, TFT_YELLOW);
  palettes[1]->set(COLOR_BACKGROUND, TFT_DARKCYAN);

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
    avatar.setColorPalette(
        *palettes[static_cast<uint8_t>(!avatar.getIsAutoBlink())]);
  }
  if (M5.BtnC.wasPressed()) {
    // switch left eye
    avatar.setLeftEyeOpenRatio(avatar.getLeftEyeOpenRatio() > 0.5f ? 0.0f
                                                                   : 1.0f);
  }
  delay(10);
}
