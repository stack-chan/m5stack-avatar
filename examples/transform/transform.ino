#include <M5Stack.h>
#include <Avatar.h>

using namespace m5avatar;

Avatar avatar;
int degrees = 0;

void setup()
{
  M5.begin();
  avatar.init();
}

void loop()
{
  M5.update();
  degrees = (degrees + 1) % 360;
  float radian = degrees / 180.0 * PI;
  float scale = sin(radian) / 2.0 + 1.0;
  avatar.setRotation(radian);
  avatar.setScale(scale);
  delay(33);
}
