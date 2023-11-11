#include <M5Unified.h>
#include <Avatar.h>

using namespace m5avatar;

Avatar avatar;

void setup()
{
  M5.begin();
  avatar.init(); // start drawing

  // adjust position
  const auto r = avatar.getFace()->getBoundingRect();
  const auto scale_w = M5.Display.width() / (float)r->getWidth();
  const auto scale_h = M5.Display.height() / (float)r->getHeight();
  const auto scale = std::min(scale_w, scale_h);
  avatar.setScale(scale);
  const auto offs_x = (r->getWidth() - M5.Display.width()) / 2;
  const auto offs_y = (r->getHeight() - M5.Display.height()) / 2;
  avatar.setPosition(-offs_y, -offs_x);
}

void loop()
{
  // avatar's face updates in another thread
  // so no need to loop-by-loop rendering
}
