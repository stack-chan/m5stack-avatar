#include <M5Stack.h>
#include "Avatar.h"

using namespace m5avatar;

class MyFace : public Face
{
<<<<<<< HEAD
  public:
    MyFace()
    : Face(new Mouth(163, 148, 55, 60, 4, 20),
      new Eye(90, 93, 14, false),
      new Eye(230, 96, 14, true),
      new Eyeblow(90, 67, 32, 6, false),
      new Eyeblow(230, 72, 32, 6, true))
=======
  private:
    MouthInterface *mouth;
    EyeInterface *eyeR;
    EyeInterface *eyeL;
    EyeblowInterface *eyeblowR;
    EyeblowInterface *eyeblowL;
    TFT_eSprite *sprite;
    BoundingRect *boundingRect;
  public:
    MyFace()
    : mouth {new Mouth(163, 148, 55, 60, 4, 20, PRIMARY_COLOR, SECONDARY_COLOR)},
      eyeR {new Eye(90, 93, 14, false, PRIMARY_COLOR, SECONDARY_COLOR)},
      eyeL {new Eye(230, 96, 14, true, PRIMARY_COLOR, SECONDARY_COLOR)},
      eyeblowR {new Eyeblow(90, 67, 32, 6, false, PRIMARY_COLOR, SECONDARY_COLOR)},
      eyeblowL {new Eyeblow(230, 72, 32, 6, true, PRIMARY_COLOR, SECONDARY_COLOR)},
      sprite {new TFT_eSprite(&M5.Lcd)},
      boundingRect{new BoundingRect(0, 0, M5.Lcd.width(), M5.Lcd.height())}
>>>>>>> 1e20f2c90f14c6b9c8c2f36deb3c6589d03d9a09
    {}
};

Avatar *avatar;
<<<<<<< HEAD

Face* faces[2];
=======
Face *face1;
Face *face2;
// Face *face3;
const Expression expressions[] = {Expression::Angry, Expression::Sleepy, Expression::Happy, Expression::Sad, Expression::Neutral};
Face* faces[2];
int faceIdx = 0;
>>>>>>> 1e20f2c90f14c6b9c8c2f36deb3c6589d03d9a09
const int facesSize = sizeof(faces) / sizeof(Face*);
int faceIdx = 0;

const Expression expressions[] = {
  Expression::Angry,
  Expression::Sleepy,
  Expression::Happy,
  Expression::Sad,
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
  avatar = new Avatar();
<<<<<<< HEAD

  faces[0] = avatar->getFace();
  faces[1] = new MyFace();

  cps[0] = new ColorPalette();
  cps[1] = new ColorPalette();
  cps[2] = new ColorPalette();
  cps[3] = new ColorPalette();
  cps[1]->set(COLOR_PRIMARY, TFT_YELLOW);
  cps[1]->set(COLOR_BACKGROUND, TFT_DARKCYAN);
  cps[2]->set(COLOR_PRIMARY, TFT_BLACK);
  cps[2]->set(COLOR_BACKGROUND, TFT_WHITE);
  cps[3]->set(COLOR_PRIMARY, TFT_RED);
  cps[3]->set(COLOR_BACKGROUND, TFT_PINK);

=======
  face1 = new MyFace();
  face2 = avatar->getFace();
  // face3 = new CatFace();
  faces[0] = face1;
  faces[1] = face2;
  // faces[2] = face3;
>>>>>>> 1e20f2c90f14c6b9c8c2f36deb3c6589d03d9a09
  avatar->init();
  avatar->setColorPalette(*cps[0]);
}

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed())
  {
<<<<<<< HEAD
=======
    Serial.printf("face[%d]: %p\n", faceIdx, faces[faceIdx]);

    Serial.printf("setFace...");
>>>>>>> 1e20f2c90f14c6b9c8c2f36deb3c6589d03d9a09
    avatar->setFace(faces[faceIdx]);
    faceIdx = (faceIdx + 1) % facesSize;
  }
  if (M5.BtnB.wasPressed())
  {
<<<<<<< HEAD
    avatar->setColorPalette(*cps[cpsIdx]);
    cpsIdx = (cpsIdx + 1) % cpsSize;
=======
    if (!isShowingQR)
    {
      TTS.play("haiyo-", 80);
      delay(800);
    }
    isShowingQR = !isShowingQR;
    delay(200);
    if (isShowingQR)
    {
      avatar->stop();
      delay(200);
      M5.Lcd.setBrightness(10);
      M5.Lcd.qrcode("https://twitter.com/meganetaaan");
    }
    else
    {
      avatar->start();
      M5.Lcd.setBrightness(30);
    }
>>>>>>> 1e20f2c90f14c6b9c8c2f36deb3c6589d03d9a09
  }
  if (M5.BtnC.wasPressed())
  {
    avatar->setExpression(expressions[idx]);
    idx = (idx + 1) % expressionsSize;
  }
}
