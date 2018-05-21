#include <M5Stack.h>
#include "Avatar.h"
#include "const.h"
#include <AquesTalkTTS.h>

using namespace m5avatar;
#define PRIMARY_COLOR WHITE
#define SECONDARY_COLOR BLACK

class MyFace : public Face
{
public:
  MyFace()
  {
    this->mouth = new Mouth(163, 160, 55, 60, 4, 20, PRIMARY_COLOR, SECONDARY_COLOR);
    this->eyeR = new Eye(90, 93, 14, false, PRIMARY_COLOR, SECONDARY_COLOR);
    this->eyeL = new Eye(230, 96, 14, true, PRIMARY_COLOR, SECONDARY_COLOR);
    this->eyeblowR = new Eyeblow(90, 67, 32, 6, false, PRIMARY_COLOR, SECONDARY_COLOR);
    this->eyeblowL = new Eyeblow(230, 72, 32, 6, true, PRIMARY_COLOR, SECONDARY_COLOR);
    this->sprite = new TFT_eSprite(&M5.Lcd);
  }
};

Avatar *avatar;
Face *face1;
Face *face2;
EyeInterface *eyeL;
EyeInterface *eyeR;
const Expression expressions[] = {Angry, Sleepy, Happy, Sad, Neutral};
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
  // avatar->getFace()->setRightEye(eyeR);
  // avatar->getFace()->setLeftEye(eyeL);
  face1 = new MyFace();
  face2 = avatar->getFace();
  faces[0] = face1;
  faces[1] = face2;
  avatar->init();
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
