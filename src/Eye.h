// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef EYE_H_
#define EYE_H_

#include <utility/In_eSPI.h>
#include "DrawContext.h"
#include "Drawable.h"

namespace m5avatar {

class Eye final : public Drawable {
 private:
  uint16_t r;
  bool isLeft;

 public:
  // constructor
  Eye() = delete;
  Eye(uint16_t x, uint16_t y, uint16_t r, bool isLeft);  // deprecated
  Eye(uint16_t r, bool isLeft);
  ~Eye() = default;
  Eye(const Eye &other) = default;
  Eye &operator=(const Eye &other) = default;
  void draw(TFT_eSPI *spi, BoundingRect rect,
            DrawContext *drawContext) override;
  // void draw(TFT_eSPI *spi, DrawContext *drawContext) override; // deprecated
};

}  // namespace m5avatar

#endif  // EYE_H_
