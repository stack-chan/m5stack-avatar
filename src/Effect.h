// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef EFFECT_H_
#define EFFECT_H_
#include <utility/In_eSPI.h>
#include "DrawContext.h"
#include "Drawable.h"

namespace m5avatar {

class Effect final : public Drawable {
 private:
  void drawSweat(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                 uint32_t color) {
    spi->fillCircle(x, y, r, color);
    uint32_t a = (sqrt(3) * r) / 2;
    spi->fillTriangle(x, y - r * 2, x - a, y - r * 0.5, x + a, y - r * 0.5,
                      color);
  }

  void drawAngerMark(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                     uint32_t color, uint32_t bColor) {
    spi->fillRect(x - (r / 3), y - r, (r * 2) / 3, r * 2, color);
    spi->fillRect(x - r, y - (r / 3), r * 2, (r * 2) / 3, color);
    spi->fillRect(x - (r / 3) + 2, y - r, ((r * 2) / 3) - 4, r * 2, bColor);
    spi->fillRect(x - r, y - (r / 3) + 2, r * 2, ((r * 2) / 3) - 4, bColor);
  }

  void drawHeart(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                 uint32_t color) {
    spi->fillCircle(x - r / 2, y, r / 2, color);
    spi->fillCircle(x + r / 2, y, r / 2, color);
    float a = (sqrt(2) * r) / 4.0;
    spi->fillTriangle(x, y, x - r / 2 - a, y + a, x + r / 2 + a, y + a, color);
    spi->fillTriangle(x, y + (r / 2) + 2 * a, x - r / 2 - a, y + a, x + r / 2 + a, y + a,
                      color);
  }

 public:
  // constructor
  Effect() = default;
  ~Effect() = default;
  Effect(const Effect &other) = default;
  Effect &operator=(const Effect &other) = default;
  void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *ctx) override {
    uint32_t primaryColor = ctx->getColorPalette()->get(COLOR_PRIMARY);
    uint32_t bgColor = ctx->getColorPalette()->get(COLOR_BACKGROUND);
    Expression exp = ctx->getExpression();
    if (exp == Expression::Doubt) {
      drawSweat(spi, 290, 110, 5, primaryColor);
    } else if (exp == Expression::Angry) {
      drawAngerMark(spi, 280, 50, 12, primaryColor, bgColor);
    } else if (exp == Expression::Happy) {
      drawHeart(spi, 280, 50, 12, primaryColor);
    }
  }
};

}  // namespace m5avatar

#endif  // EFFECT_H_
