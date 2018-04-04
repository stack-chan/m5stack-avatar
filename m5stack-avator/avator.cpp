#include <M5Stack.h>
#include "avator.h"

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
  this->lastX1 = 0;
  this->lastX2 = 0;
  this->lastY1 = 0;
  this->lastY2 = 0;
}
void Mouth::clear()
{
  // M5.Lcd.fillRect(lastX1, lastY1, lastX2, lastY2, secondaryColor);
  M5.Lcd.clear();
}
void Mouth::draw(int x1, int y1, int x2, int y2)
{
  clear();
  Serial.printf("%d, %d, %d, %d\n", x1, y1, x2, y2);
  M5.Lcd.fillRect(x1, x2, y1, y2, primaryColor);
  lastX1 = x1;
  lastY1 = y1;
  lastX2 = x2;
  lastY2 = y2;
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
void Eye::clear()
{
  M5.Lcd.fillRect(lastX - lastR, lastY - lastR,
                  lastX + lastR, lastY + lastR, secondaryColor);
}
void Eye::drawCircle(int x, int y, int r)
{
  clear();
  M5.Lcd.fillCircle(x, y, r, primaryColor);
  lastX = x;
  lastY = y;
  lastR = r;
}
void Eye::drawRect(int x1, int y1, int x2, int y2)
{
  clear();
  M5.Lcd.fillRect(x1, y1, x2, y2, primaryColor);
  lastX = x1 + (x2 - x1) / 2;
  lastY = y1 + (y2 - y1) / 2;
  lastR = x2 - x1; // TODO: ellipse
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
    int y1 = y = r;
    int x2 = x + r;
    int y2 = y + r;
    drawRect(x1, y1, x2, y2);
  }
}

#define PRIMARY_COLOR WHITE
#define SECONDARY_COLOR BLACK

Avator::Avator()
{
  this->mouth = Mouth(160, 200, 30, 100, 8, 60, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeR = Eye(90, 83, 8, PRIMARY_COLOR, SECONDARY_COLOR);
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
  // TODO: start animation
}
