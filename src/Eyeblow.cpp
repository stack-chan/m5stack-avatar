// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Eyeblow.h"
using namespace m5avatar;

Eyeblow::Eyeblow(int x, int y, int w, int h, bool isLeft, uint32_t primaryColor, uint32_t secondaryColor)
{
  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;
  this->isLeft = isLeft;
  this->primaryColor = primaryColor;
  this->secondaryColor = secondaryColor;
}

Eyeblow::~Eyeblow()
{

}

void Eyeblow::draw(TFT_eSPI *spi, DrawContext *ctx)
{
  Expression exp = ctx->getExpression();
  if (width == 0 || height == 0)
  {
    return;
  }
  // draw two triangles to make rectangle
  if (exp == Angry || exp == Sad)
  {
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int a = isLeft ^ exp == Sad ? -1 : 1;
    int dx = a * 3;
    int dy = a * 5;
    x1 = x - width / 2;
    x2 = x1 - dx;
    x4 = x + width / 2;
    x3 = x4 + dx;
    y1 = y - height / 2 - dy;
    y2 = y + height / 2 - dy;
    y3 = y - height / 2 + dy;
    y4 = y + height / 2 + dy;
    spi->fillTriangle(x1, y1, x2, y2, x3, y3, primaryColor);
    spi->fillTriangle(x2, y2, x3, y3, x4, y4, primaryColor);
  }
  else
  {
    int x1 = x - width / 2;
    int y1 = y - height / 2;
    if (exp == Happy)
    {
      y1 = y1 - 5;
    }
    spi->fillRect(x1, y1, width, height, primaryColor);
  }
}
