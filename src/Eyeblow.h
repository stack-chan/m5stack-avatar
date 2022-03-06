// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef EYEBLOW_H_
#define EYEBLOW_H_

#define LGFX_USE_V1
#include <M5GFX.h>
#include "BoundingRect.h"
#include "DrawContext.h"
#include "Drawable.h"

namespace m5avatar {
class Eyeblow final : public Drawable {
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
  void draw(M5Canvas *spi, BoundingRect rect,
            DrawContext *drawContext) override;
};

}  // namespace m5avatar

#endif  // EYEBLOW_H_
