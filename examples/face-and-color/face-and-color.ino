#include <M5Stack.h>
#include <Avatar.h>
#include <faces/DogFace.h>

using namespace m5avatar;

Avatar avatar;

Face* faces[2];
const int facesSize = sizeof(faces) / sizeof(Face*);
int faceIdx = 0;

const Expression expressions[] = {
  Expression::Angry,
  Expression::Sleepy,
  Expression::Happy,
  Expression::Sad,
  Expression::Doubt,
  Expression::Neutral
};
const int expressionsSize = sizeof(expressions) / sizeof(Expression);
int idx = 0;

ColorPalette* cps[4];
const int cpsSize = sizeof(cps) / sizeof(ColorPalette*);
int cpsIdx = 0;

bool isShowingQR = false;

void setup()
{
  M5.begin();
  M5.Lcd.setBrightness(30);
  M5.Lcd.clear();

  faces[0] = avatar.getFace();
  faces[1] = new DogFace();

  cps[0] = new ColorPalette();
  cps[1] = new ColorPalette();
  cps[2] = new ColorPalette();
  cps[3] = new ColorPalette();
  cps[1]->set(COLOR_PRIMARY, TFT_YELLOW);
  cps[1]->set(COLOR_BACKGROUND, TFT_DARKCYAN);
  cps[2]->set(COLOR_PRIMARY, TFT_DARKGREY);
  cps[2]->set(COLOR_BACKGROUND, TFT_WHITE);
  cps[3]->set(COLOR_PRIMARY, TFT_RED);
  cps[3]->set(COLOR_BACKGROUND, TFT_PINK);

  avatar.init();
  avatar.setColorPalette(*cps[0]);
}

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed())
  {
    avatar.setFace(faces[faceIdx]);
    faceIdx = (faceIdx + 1) % facesSize;
  }
  if (M5.BtnB.wasPressed())
  {
    avatar.setColorPalette(*cps[cpsIdx]);
    cpsIdx = (cpsIdx + 1) % cpsSize;
  }
  if (M5.BtnC.wasPressed())
  {
    avatar.setExpression(expressions[idx]);
    idx = (idx + 1) % expressionsSize;
  }
}
