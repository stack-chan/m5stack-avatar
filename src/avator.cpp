// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "avator.h"

#define PRIMARY_COLOR WHITE
#define SECONDARY_COLOR BLACK

DrawContext::DrawContext()
{
  
}
// DrawContext
DrawContext::DrawContext(Expression expression, float breath)
{
  this->expression = expression;
  this->breath = breath;
}

Expression DrawContext::getExpression()
{
  return expression;
}

float DrawContext::getBreath()
{
  return breath;
}

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
  this->openRatio = 0;
}

void Mouth::_drawCircle(TFT_eSPI *spi, int x, int y, int w, int h)
{
  spi->fillRect(x, y, w, h, primaryColor);
}

void Mouth::_drawRect(TFT_eSPI *spi, int x, int y, int w, int h)
{
  spi->fillRect(x, y, w, h, primaryColor);
}

void Mouth::_drawTriangle(TFT_eSPI *spi, int x0, int y0, int x1, int y1, int x2, int y2)
{
  spi->fillTriangle(x0, y0, x1, y1, x2, y2, primaryColor);
}

void Mouth::setOpenRatio(float ratio)
{
  openRatio = ratio;
}

void Mouth::draw(TFT_eSprite *spi, DrawContext ctx)
{
  float breath = min(1.0, ctx.getBreath());
  int h = minHeight + (maxHeight - minHeight) * openRatio;
  int w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
  int x = this->x - w / 2;
  int y = this->y - h / 2 + breath * 2;
  Serial.printf("Mouth::draw(%d, %d, %d, %d)\n", x, y, w, h);
  _drawRect(spi, x, y, w, h);
}

// Eye
Eye::Eye(void)
{
  
}
Eye::Eye(int x, int y, int r, bool isLeft, uint32_t primaryColor, uint32_t secondaryColor)
{
  this->openRatio = 1;
  this->x = x;
  this->y = y;
  this->r = r;
  this->isLeft = isLeft;
  this->offsetX = 0;
  this->offsetY = 0;
  this->primaryColor = primaryColor;
  this->secondaryColor = secondaryColor;
}
void Eye::drawCircle(TFT_eSPI *spi, int x, int y, int r)
{
  spi->fillCircle(x, y, r, primaryColor);
}

void Eye::drawRect(TFT_eSPI *spi, int x, int y, int w, int h)
{
  spi->fillRect(x, y, w, h, primaryColor);
}

void Eye::draw(TFT_eSprite *spi, DrawContext ctx)
{
  Expression exp = ctx.getExpression();
  float breath = min(1.0, ctx.getBreath());
  if (openRatio > 0)
  {
    drawCircle(spi, x + offsetX, y + offsetY + breath * 3, r);
    // TODO: Refactor
    if (exp == Angry || exp == Sad)
    {
      int x0, y0, x1, y1, x2, y2;
      x0 = x + offsetX - r;
      y0 = y + offsetY - r + breath * 3;
      x1 = x0 + r * 2;
      y1 = y0;
      x2 = !isLeft != !(exp == Sad) ? x0 : x1;
      y2 = y0 + r;
      spi->fillTriangle(x0, y0, x1, y1, x2, y2, SECONDARY_COLOR);
    }
    if (exp == Happy || exp == Sleepy)
    {
      int x0, y0, w, h;
      x0 = x + offsetX - r;
      y0 = y + offsetY - r + breath * 3;
      w = r * 2 + 4;
      h = r + 2;
      if (exp == Happy)
      {
        y0 += r;
        spi->fillCircle(x + offsetX, y + offsetY + breath * 3, r / 1.5, SECONDARY_COLOR);
      }
      spi->fillRect(x0, y0, w, h, SECONDARY_COLOR);
    }
  }
  else
  {
    int x1 = x - r + offsetX;
    int y1 = y - 2 + offsetY + breath * 1;
    int w = r * 2;
    int h = 4;
    drawRect(spi, x1, y1, w, h);
  }
}

void Eye::setOpenRatio(float ratio)
{
  this->openRatio = ratio;
}

void Eye::setOffset(int offsetX, int offsetY)
{
  this->offsetX = offsetX;
  this->offsetY = offsetY;
}

Avator::Avator()
{
  this->mouth = Mouth(163, 148, 50, 100, 4, 60, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeR = Eye(90, 93, 8, false, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeL = Eye(230, 96, 8, true, PRIMARY_COLOR, SECONDARY_COLOR);
  this->drawContext = DrawContext(expression, breath);
  this->avatorSprite = new TFT_eSprite(&M5.Lcd);
  avatorSprite->setColorDepth(1);
  avatorSprite->createSprite(320, 240);
  avatorSprite->setBitmapColor(PRIMARY_COLOR, SECONDARY_COLOR);
  expression = Neutral;
  breath = 0.0;
}

/**
 * @deprecated
 */
void Avator::openMouth(int percent)
{
  float f = percent / 100.0;
  mouth.setOpenRatio(f);
  draw();
}

void Avator::setMouthOpen(float f)
{
  mouth.setOpenRatio(f);
}

/**
 * @deprecated
 */
void Avator::openEye(boolean isOpen)
{
  float ratio = isOpen ? 1 : 0;
  eyeR.setOpenRatio(ratio);
  eyeL.setOpenRatio(ratio);
  draw();
}

void Avator::setEyeOpen(float f)
{
  eyeR.setOpenRatio(f);
  eyeL.setOpenRatio(f);
}

void Avator::setExpression(Expression expression)
{
  this->expression = expression;
}

/**
 * @deprecated
 */
void Avator::init()
{
  // TODO: start animation loop
}

/**
 * @experimental
 */
void Avator::setBreath(float breath)
{
  this->breath = breath;
}

void Avator::setGaze(float vertical, float horizontal)
{
  int v = floor(4 * vertical);
  int h = floor(4 * horizontal);
  eyeL.setOffset(v, h);
  eyeR.setOffset(v, h);
}

void Avator::draw()
{
  avatorSprite->fillSprite(SECONDARY_COLOR);
  this->drawContext = DrawContext(expression, breath);
  mouth.draw(avatorSprite, drawContext);
  eyeR.draw(avatorSprite, drawContext);
  eyeL.draw(avatorSprite, drawContext);
  avatorSprite->pushSprite(0, 0);
}
