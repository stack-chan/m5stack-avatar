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
  this->lastX = 0;
  this->lastY = 0;
  this->lastW = 0;
  this->lastH = 0;
}
void Mouth::clear()
{
  M5.Lcd.fillRect(lastX, lastY, lastW, lastH, secondaryColor);
}
void Mouth::_draw(int x, int y, int w, int h)
{
  if (lastX == x && lastY == y && lastW == w && lastH == h) return;
  clear();
  M5.Lcd.fillRect(x, y, w, h, primaryColor);
  lastX = x;
  lastY = y;
  lastW = w;
  lastH = h;
}
void Mouth::setOpenRatio(float ratio)
{
  openRatio = ratio;
}
/**
 * @deprecated
 */
void Mouth::open(int percent)
{
  float f = percent / 100.0;
  setOpenRatio(f);
  draw();
}
void Mouth::draw()
{
  int h = minHeight + (maxHeight - minHeight) * openRatio;
  int w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
  int x = this->x - w / 2;
  int y = this->y - h / 2;
  _draw(x, y, w, h);
}

// Eye
Eye::Eye(void)
{
  
}
Eye::Eye(int x, int y, int r, uint32_t primaryColor, uint32_t secondaryColor)
{
  this->openRatio = 1;
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
  if (lastX == x && lastY == y && lastR == r) return;
  clear();
  M5.Lcd.fillCircle(x, y, r, primaryColor);
  lastX = x;
  lastY = y;
  lastR = r;
}
void Eye::drawRect(int x, int y, int w, int h)
{
  if (lastX == x + w / 2 && lastY == y + h / 2 && lastR == w) return;
  clear();
  M5.Lcd.fillRect(x, y, w, h, primaryColor);
  lastX = x + w / 2;
  lastY = y + h / 2;
  lastR = w; // TODO: ellipse
}
void Eye::draw()
{
  if (openRatio > 0)
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
void Eye::setOpenRatio(float ratio)
{
  this->openRatio = ratio;
}
/**
 * @deprecated
 */
void Eye::open(boolean isOpen)
{
  float ratio = isOpen ? 1 : 0;
  setOpenRatio(ratio);
  draw();
}

#define PRIMARY_COLOR WHITE
#define SECONDARY_COLOR BLACK

Avator::Avator()
{
  this->mouth = Mouth(163, 145, 50, 100, 4, 60, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeR = Eye(90, 93, 8, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeL = Eye(230, 96, 8, PRIMARY_COLOR, SECONDARY_COLOR);
}
void Avator::openMouth(int percent)
{
  mouth.open(percent);
}
void Avator::setMouthOpen(float f)
{
  mouth.setOpenRatio(f);
}
void Avator::openEye(boolean isOpen)
{
  eyeR.open(isOpen);
  eyeL.open(isOpen);
}
void Avator::setEyeOpen(float f)
{
  eyeR.setOpenRatio(f);
  eyeL.setOpenRatio(f);
}
void Avator::smile()
{
  // TODO
}
/**
 * @deprecated
 */
void Avator::init()
{
  // TODO: start animation loop
}

void Avator::draw()
{
  mouth.draw();
  eyeR.draw();
  eyeL.draw();
}
