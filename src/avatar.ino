#include <M5Stack.h>
#include "Avatar.h"
#include "const.h"
#include <AquesTalkTTS.h>
#include "parts/CatFace.h"
#include "tasks/LipSync.h"

using namespace m5avatar;

class MyFace : public Face
{
  public:
    MyFace()
    : Face(new Mouth(163, 148, 55, 60, 4, 20),
      new Eye(90, 93, 14, false),
      new Eye(230, 96, 14, true),
      new Eyeblow(90, 67, 32, 6, false),
      new Eyeblow(230, 72, 32, 6, true))
    {}
};

Avatar *avatar;
Face *face1;
Face *face2;
// Face *face3;
const Expression expressions[] = {Expression::Angry, Expression::Sleepy, Expression::Happy, Expression::Sad, Expression::Neutral};
ColorPalette* cps[2] = {
  new ColorPalette(),
  new ColorPalette()
};

Face* faces[2];
int faceIdx = 0;
const int facesSize = sizeof(faces) / sizeof(Face*);
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
  face1 = new MyFace();
  face2 = avatar->getFace();
  // face3 = new CatFace();
  faces[0] = face1;
  faces[1] = face2;
  // faces[2] = face3;
  cps[0]->set(COLOR_PRIMARY, TFT_YELLOW);
  cps[0]->set(COLOR_BACKGROUND, TFT_DARKCYAN);

  avatar->init();
  avatar->setColorPalette(*cps[0]);
  avatar->addTask(lipSync, "lipSync");
}

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed())
  {
    Serial.printf("face[%d]: %p", faceIdx, faces[faceIdx]);

    Serial.printf("setFace...");
    avatar->setFace(faces[faceIdx]);
    faceIdx = (faceIdx + 1) % facesSize;
  }
  if (M5.BtnB.wasPressed())
  {
    if (!isShowingQR)
    {
      TTS.play("haiyo-", 80);
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
  if (M5.BtnC.wasPressed())
  {
    avatar->setExpression(expressions[idx]);
    idx = (idx + 1) % expressionsSize;
  }
  delay(125);
}
