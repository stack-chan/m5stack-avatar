// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Eye.h"

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

Eye::~Eye()
{

}

void Eye::drawCircle(TFT_eSPI *spi, int x, int y, int r)
{
  spi->fillCircle(x, y, r, primaryColor);
}

void Eye::drawRect(TFT_eSPI *spi, int x, int y, int w, int h)
{
  spi->fillRect(x, y, w, h, primaryColor);
}

void Eye::draw(TFT_eSPI *spi, DrawContext *ctx)
{
  Expression exp = ctx->getExpression();
  float breath = min(1.0, ctx->getBreath());
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
      spi->fillTriangle(x0, y0, x1, y1, x2, y2, primaryColor);
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
        spi->fillCircle(x + offsetX, y + offsetY + breath * 3, r / 1.5, secondaryColor);
      }
      spi->fillRect(x0, y0, w, h, secondaryColor);
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
