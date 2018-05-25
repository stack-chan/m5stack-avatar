// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Mouth.h"

namespace m5avatar {

Mouth::Mouth(uint16_t x, uint16_t y, uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight, uint16_t maxHeight, uint32_t primaryColor, uint32_t secondaryColor)
: x{x}, y{y}, minWidth{minWidth}, maxWidth{maxWidth}, minHeight{minHeight}, maxHeight{maxHeight}, primaryColor{primaryColor}, secondaryColor{secondaryColor}, openRatio{0}
{}

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
  spi->fillRect(x, y, w, h, primaryColor);
}

}
