#include <M5Stack.h>
#include <Avatar.h>

using namespace m5avatar;

Avatar avatar;

void setup()
{
  M5.begin();
  avatar.init(); // start drawing
}

void loop()
{
  // avatar's face updates in another thread
  // so no need to loop-by-loop rendering
}
