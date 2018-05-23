// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <utility/In_eSPI.h>
#include "DrawContext.h"

namespace m5avatar
{
class EyeblowInterface
{
public:
  virtual void draw(TFT_eSPI *spi, DrawContext *drawContext) = 0;
};

class Eyeblow final : public EyeblowInterface
{
private:
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  bool isLeft;
  uint32_t primaryColor;
  uint32_t secondaryColor;

public:
  // constructor
  Eyeblow() = delete;
  Eyeblow(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool isLeft, uint32_t primaryColor, uint32_t secondaryColor);
  ~Eyeblow() = default;
  Eyeblow(const Eyeblow &other) = default;
  Eyeblow &operator=(const Eyeblow &other) = default;
  void draw(TFT_eSPI *spi, DrawContext *drawContext);
};

}
