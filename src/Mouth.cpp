// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "Mouth.h"

namespace m5avatar {

Mouth::Mouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
             uint16_t maxHeight)
    : minWidth{minWidth},
      maxWidth{maxWidth},
      minHeight{minHeight},
      maxHeight{maxHeight} {}

void Mouth::draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *ctx) {
  uint32_t primaryColor = ctx->getColorPalette()->get(COLOR_PRIMARY);
  float breath = _min(1.0f, ctx->getBreath());
  float openRatio = ctx->getMouthOpenRatio();
  int h = minHeight + (maxHeight - minHeight) * openRatio;
  int w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
  int x = rect.getLeft() - w / 2;
  int y = rect.getTop() - h / 2 + breath * 2;
  spi->fillRect(x, y, w, h, primaryColor);
}

}  // namespace m5avatar
