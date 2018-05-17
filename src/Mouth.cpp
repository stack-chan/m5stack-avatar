// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Mouth.h"
using namespace m5avatar;

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

void Mouth::draw(TFT_eSPI *spi, DrawContext *ctx)
{
  float breath = min(1.0, ctx->getBreath());
  int h = minHeight + (maxHeight - minHeight) * openRatio;
  int w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
  int x = this->x - w / 2;
  int y = this->y - h / 2 + breath * 2;
  Serial.printf("Mouth::draw(%d, %d, %d, %d)\n", x, y, w, h);
  _drawRect(spi, x, y, w, h);
}
