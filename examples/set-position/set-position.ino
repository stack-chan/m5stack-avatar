#include <M5Stack.h>
#include <Avatar.h>

using namespace m5avatar;

Avatar avatar;

void setup()
{
  M5.begin();
  avatar.setPosition(50, 50);
  avatar.init(); // start drawing
}

void loop()
{
}
