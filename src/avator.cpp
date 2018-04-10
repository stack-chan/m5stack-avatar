#include <M5Stack.h>
#include "./avator.h"

// Mouth
Mouth::Mouth(void)
{

}
Mouth::Mouth(int x, int y, int minWidth, int maxWidth, int minHeight, int maxHeight, uint32_t primaryColor, uint32_t secondaryColor)
{
  // TODO: validation
  this->x = x;
  this->y = y;
  this->minWidth = minWidth;
  this->maxWidth = maxWidth;
  this->minHeight = minHeight;
  this->maxHeight = maxHeight;
  this->primaryColor = primaryColor;
  this->secondaryColor = secondaryColor;
  this->lastX = 0;
  this->lastY = 0;
  this->lastW = 0;
  this->lastH = 0;
}
void Mouth::clear()
{
  M5.Lcd.fillRect(lastX, lastY, lastW, lastH, secondaryColor);
}
void Mouth::draw(int x, int y, int w, int h)
{
  clear();
  M5.Lcd.fillRect(x, y, w, h, primaryColor);
  lastX = x;
  lastY = y;
  lastW = w;
  lastH = h;
}
void Mouth::open(int percent)
{
  int h = minHeight + (maxHeight - minHeight) * percent / 100;
  int w = minWidth + (maxWidth - minWidth) * (100 - percent) / 100;
  int x = this->x - w / 2;
  int y = this->y - h / 2;
  draw(x, y, w, h);
}

// Eye
Eye::Eye(void)
{
  
}
Eye::Eye(int x, int y, int r, uint32_t primaryColor, uint32_t secondaryColor)
{
  this->x = x;
  this->y = y;
  this->r = r;
  this->lastX = 0;
  this->lastY = 0;
  this->lastR = 0;
  this->primaryColor = primaryColor;
  this->secondaryColor = secondaryColor;
}
void Eye::clear()
{
  M5.Lcd.fillRect(lastX - lastR - 2, lastY - lastR - 2,
                  lastR * 2 + 4, lastR * 2 + 4, secondaryColor);
}
void Eye::drawCircle(int x, int y, int r)
{
  clear();
  M5.Lcd.fillCircle(x, y, r, primaryColor);
  lastX = x;
  lastY = y;
  lastR = r;
}
void Eye::drawRect(int x, int y, int w, int h)
{
  clear();
  M5.Lcd.fillRect(x, y, w, h, primaryColor);
  lastX = x + w / 2;
  lastY = y + h / 2;
  lastR = w; // TODO: ellipse
}
void Eye::open(boolean isOpen)
{
  if (isOpen)
  {
    // TODO: "wideness"
    drawCircle(x, y, r);
  }
  else
  {
    int x1 = x - r;
    int y1 = y - 2;
    int w = r * 2;
    int h = 4;
    drawRect(x1, y1, w, h);
  }
}

#define PRIMARY_COLOR WHITE
#define SECONDARY_COLOR BLACK

Avator::Avator()
{
  this->mouth = Mouth(163, 145, 40, 100, 4, 60, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeR = Eye(90, 93, 8, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeL = Eye(230, 96, 8, PRIMARY_COLOR, SECONDARY_COLOR);
}
void Avator::openMouth(int percent)
{
  mouth.open(percent);
}
void Avator::openEye(boolean isOpen)
{
  eyeR.open(isOpen);
  eyeL.open(isOpen);
}
void Avator::smile()
{
  // TODO
}
void Avator::init()
{
  mouth.open(0);
  eyeR.open(true);
  eyeL.open(true);
  // TODO: start animation
}
