// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <utility/In_eSPI.h>
#include "Drawable.h"
#include "BoundingRect.h"
#include "DrawContext.h"

namespace m5avatar
{
class Eyeblow final : public Drawable
{
private:
  uint16_t width;
  uint16_t height;
  bool isLeft;

public:
  // constructor
  Eyeblow() = delete;
  Eyeblow(uint16_t w, uint16_t h, bool isLeft);
  ~Eyeblow() = default;
  Eyeblow(const Eyeblow &other) = default;
  Eyeblow &operator=(const Eyeblow &other) = default;
  void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *drawContext) override;
};

}
