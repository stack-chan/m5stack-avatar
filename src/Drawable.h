// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <utility/In_eSPI.h>
#include "BoundingRect.h"
#include "DrawContext.h"

namespace m5avatar {
class Drawable {
 public:
  virtual ~Drawable() = default;
  virtual void draw(TFT_eSPI *spi, BoundingRect rect,
                    DrawContext *drawContext) = 0;
  // virtual void draw(TFT_eSPI *spi, DrawContext *drawContext) = 0;
};

}  // namespace m5avatar

#endif  // DRAWABLE_H_
