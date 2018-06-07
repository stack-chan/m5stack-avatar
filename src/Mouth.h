// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include "Drawable.h"
#include "DrawContext.h"
#include "BoundingRect.h"
#include <utility/In_eSPI.h>

namespace m5avatar
{
class Mouth final : public Drawable
{
private:
  uint16_t minWidth;
  uint16_t maxWidth;
  uint16_t minHeight;
  uint16_t maxHeight;

public:
  // constructor
  Mouth() = delete;
  ~Mouth() = default;
  Mouth(const Mouth &other) = default;
  Mouth &operator=(const Mouth &other) = default;
  Mouth(uint16_t minWidth, uint16_t maxWidth,
        uint16_t minHeight, uint16_t maxHeight);
  Mouth(uint16_t x, uint16_t y,
        uint16_t minWidth, uint16_t maxWidth,
        uint16_t minHeight, uint16_t maxHeight);
  void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *drawContext) override;
};

}
