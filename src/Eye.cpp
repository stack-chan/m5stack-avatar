// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Eye.h"
namespace m5avatar {

Eye::Eye(uint16_t x, uint16_t y, uint16_t r, bool isLeft)
: x{x}, y{y}, r{r}, isLeft{isLeft}, offsetX{0}, offsetY{0}, openRatio{1}
{}

void Eye::draw(TFT_eSPI *spi, DrawContext *ctx)
{
  Expression exp = ctx->getExpression();
  uint32_t primaryColor = ctx->getColorPalette().get(COLOR_PRIMARY);
  uint32_t secondaryColor = ctx->getColorPalette().get(COLOR_SECONDARY);
  float breath = std::min(1.0f, ctx->getBreath());
  if (openRatio > 0)
  {
    spi->fillCircle(x + offsetX, y + offsetY + breath * 3, r, primaryColor);
    // TODO: Refactor
    if (exp == Expression::Angry || exp == Expression::Sad)
    {
      int x0, y0, x1, y1, x2, y2;
      x0 = x + offsetX - r;
      y0 = y + offsetY - r + breath * 3;
      x1 = x0 + r * 2;
      y1 = y0;
      x2 = !isLeft != !(exp == Expression::Sad) ? x0 : x1;
      y2 = y0 + r;
      spi->fillTriangle(x0, y0, x1, y1, x2, y2, secondaryColor);
    }
    if (exp == Expression::Happy || exp == Expression::Sleepy)
    {
      int x0, y0, w, h;
      x0 = x + offsetX - r;
      y0 = y + offsetY - r + breath * 3;
      w = r * 2 + 4;
      h = r + 2;
      if (exp == Expression::Happy)
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
    spi->fillRect(x1, y1, w, h, primaryColor);
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

}
