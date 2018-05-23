// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include "DrawContext.h"
#include <utility/In_eSPI.h>

namespace m5avatar
{
class MouthInterface
{
public:
  virtual void setOpenRatio(float ratio) = 0;
  virtual void draw(TFT_eSPI *spi, DrawContext *drawContext) = 0;
};
class Mouth final : public MouthInterface
{
private:
  uint16_t x;
  uint16_t y;
  uint16_t minWidth;
  uint16_t maxWidth;
  uint16_t minHeight;
  uint16_t maxHeight;
  float openRatio;
  uint32_t primaryColor;
  uint32_t secondaryColor;

public:
  // constructor
  Mouth() = delete;
  ~Mouth() = default;
  Mouth(const Mouth &other) = default;
  Mouth &operator=(const Mouth &other) = default;
  Mouth(uint16_t x, uint16_t y,
        uint16_t minWidth, uint16_t maxWidth,
        uint16_t minHeight, uint16_t maxHeight,
        uint32_t primaryColor, uint32_t secondaryColor);
  void setOpenRatio(float ratio) override;
  void draw(TFT_eSPI *spi, DrawContext *drawContext) override;
};

}
