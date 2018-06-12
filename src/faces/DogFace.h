// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include <M5Stack.h> // TODO: include only the Sprite function not a whole library
#include "../Drawable.h"
#include "../BoundingRect.h"
#include "../DrawContext.h"

namespace m5avatar
{
  class DogEye : public Drawable
  {
    void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *ctx)
    {
      uint32_t cx = rect.getCenterX();
      uint32_t cy = rect.getCenterY();
      Gaze g = ctx->getGaze();
      ColorPalette cp = ctx->getColorPalette();
      uint32_t offsetX = g.getHorizontal() * 8;
      uint32_t offsetY = g.getVertical() * 5;
      float eor = ctx->getEyeOpenRatio();

      if (eor == 0)
      {
        // eye closed
        spi->fillRect(cx - 15, cy - 2, 30, 4, cp.get(COLOR_PRIMARY));
        return;
      }
      spi->fillEllipse(cx, cy, 30, 25, cp.get(COLOR_PRIMARY));
      spi->fillEllipse(cx, cy, 28, 23, cp.get(COLOR_BACKGROUND));
      // spi->fillEllipse(cx, cy, 30, 20, cp.get(COLOR_PRIMARY));
      // spi->fillEllipse(cx, cy, 28, 17, cp.get(COLOR_BACKGROUND));

      spi->fillEllipse(cx + offsetX, cy + offsetY, 18, 18, cp.get(COLOR_PRIMARY));
      spi->fillEllipse(cx + offsetX - 3, cy + offsetY - 3, 3, 3, cp.get(COLOR_BACKGROUND));
    }
  };

  class DogMouth : public Drawable
  {
    void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *ctx)
    {
      uint32_t cx = rect.getCenterX();
      uint32_t cy = rect.getCenterY();
      ColorPalette cp = ctx->getColorPalette();
      spi->fillEllipse(cx, cy - 15, 10, 6, cp.get(COLOR_PRIMARY));
      spi->fillEllipse(cx - 28, cy, 30, 15, cp.get(COLOR_PRIMARY));
      spi->fillEllipse(cx + 28, cy, 30, 15, cp.get(COLOR_PRIMARY));
      spi->fillEllipse(cx - 29, cy - 4, 27, 15, cp.get(COLOR_BACKGROUND));
      spi->fillEllipse(cx + 29, cy - 4, 27, 15, cp.get(COLOR_BACKGROUND));
    }
  };
  
  class DogFace: public Face
  {
  public:
    DogFace()
        : Face(new DogMouth(),
               new BoundingRect(168, 163),
               // new Eye(14, false),
               // new Eye(14, true),
               new DogEye(),
               new BoundingRect(103, 80),
               new DogEye(),
               new BoundingRect(106, 240),
               new Eyeblow(15, 2, false),
               new BoundingRect(67, 96),
               new Eyeblow(15, 2, true),
               new BoundingRect(72, 230))
    {
    }
  };


  } // namespace m5avatar