// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef FACES_BMPFACE_H_
#define FACES_BMPFACE_H_

#include <M5Unified.h> // TODO(meganetaaan): include only the Sprite function not a whole library

#include "../BoundingRect.h"
#include "../DrawContext.h"
#include "../Drawable.h"
#include "../Face.h"
#include "eye_small.h"

namespace m5avatar
{
class BMPEye : public Drawable
{
  void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
  {
    uint16_t color = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);
    uint16_t cx = rect.getCenterX();
    uint16_t cy = rect.getCenterY();
    float openRatio = ctx->getEyeOpenRatio();
    Gaze g = ctx->getGaze();
    uint32_t offsetX = g.getHorizontal() * 3;
    uint32_t offsetY = g.getVertical() * 3;
    if (openRatio == 0) {
      // close
      int x1 = cx - eye_small_width / 2 + offsetX;
      int y1 = cy + offsetY;
      int w = eye_small_width;
      int h = 4;
      spi->fillRect(x1, y1, w, h, color);
      return;
    }
    spi->drawXBitmap(
        cx - eye_small_width / 2,
        cy - eye_small_height / 2,
        eye_small, eye_small_width, eye_small_height, color);
  }
};

class BMPFace : public Face
{
public:
  BMPFace()
      : Face(new Mouth(50, 90, 4, 60), new BoundingRect(148, 163),
             new BMPEye(),
             new BoundingRect(103, 80), new BMPEye(),
             new BoundingRect(106, 240), new Eyeblow(15, 2, false),
             new BoundingRect(67, 96), new Eyeblow(15, 2, true),
             new BoundingRect(72, 230)) {}
};

} // namespace m5avatar

#endif // FACES_BMPFACE_H_
