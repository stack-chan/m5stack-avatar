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
  void drawBubbleMark(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                      uint32_t color) {
    drawBubbleMark(spi, x, y, r, color, 0);
  }

  void drawBubbleMark(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                      uint32_t color, float offset) {
    r = r + floor(r * 0.2 * offset);
    spi->drawCircle(x, y, r, color);
    spi->drawCircle(x - (r / 4), y - (r / 4), r / 4, color);
  }

  void drawSweatMark(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                 uint32_t color) {
    drawSweatMark(spi, x, y, r, color, 0);
  }

  void drawSweatMark(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                 uint32_t color, float offset) {
    y = y + floor(5 * offset);
    r = r + floor(r * 0.2 * offset);
    spi->fillCircle(x, y, r, color);
    uint32_t a = (sqrt(3) * r) / 2;
    spi->fillTriangle(x, y - r * 2, x - a, y - r * 0.5, x + a, y - r * 0.5,
                      color);
  }

  void drawChillMark(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                     uint32_t color) {
    drawChillMark(spi, x, y, r, color, 0);
  }

  void drawChillMark(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                     uint32_t color, float offset) {
    uint32_t h = r + abs(r * 0.2 * offset);
    spi->fillRect(x - (r / 2), y, 3, h / 2, color);
    spi->fillRect(x, y, 3, h * 3 / 4, color);
    spi->fillRect(x + (r / 2), y, 3, h, color);
  }

  void drawAngerMark(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                     uint32_t color, uint32_t bColor) {
    drawAngerMark(spi, x, y, r, color, bColor, 0);
  }

  void drawAngerMark(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                     uint32_t color, uint32_t bColor, float offset) {
    r = r + abs(r * 0.4 * offset);
    spi->fillRect(x - (r / 3), y - r, (r * 2) / 3, r * 2, color);
    spi->fillRect(x - r, y - (r / 3), r * 2, (r * 2) / 3, color);
    spi->fillRect(x - (r / 3) + 2, y - r, ((r * 2) / 3) - 4, r * 2, bColor);
    spi->fillRect(x - r, y - (r / 3) + 2, r * 2, ((r * 2) / 3) - 4, bColor);
  }

  void drawHeartMark(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                 uint32_t color) {
    drawHeartMark(spi, x, y, r, color, 0);
  }

  void drawHeartMark(TFT_eSPI *spi, uint32_t x, uint32_t y, uint32_t r,
                 uint32_t color, float offset) {
    r = r + floor(r * 0.4 * offset);
    spi->fillCircle(x - r / 2, y, r / 2, color);
    spi->fillCircle(x + r / 2, y, r / 2, color);
    float a = (sqrt(2) * r) / 4.0;
    spi->fillTriangle(x, y, x - r / 2 - a, y + a, x + r / 2 + a, y + a, color);
    spi->fillTriangle(x, y + (r / 2) + 2 * a, x - r / 2 - a, y + a,
                      x + r / 2 + a, y + a, color);
  }

 public:
  // constructor
  Effect() = default;
  ~Effect() = default;
  Effect(const Effect &other) = default;
  Effect &operator=(const Effect &other) = default;
  void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *ctx) override {
    uint32_t primaryColor = ctx->getColorPalette()->get(COLOR_PRIMARY);
    uint32_t bgColor = COLOR_DEPTH == 1 ? ERACER_COLOR : ctx->getColorPalette()->get(COLOR_BACKGROUND);
    float offset = ctx->getBreath();
    Expression exp = ctx->getExpression();
    switch (exp) {
      case Expression::Doubt:
        drawSweatMark(spi, 290, 110, 7, primaryColor, -offset);
        break;
      case Expression::Angry:
        drawAngerMark(spi, 280, 50, 12, primaryColor, bgColor, offset);
        break;
      case Expression::Happy:
        drawHeartMark(spi, 280, 50, 12, primaryColor, offset);
        break;
      case Expression::Sad:
        drawChillMark(spi, 270, 0, 30, primaryColor, offset);
        break;
      case Expression::Sleepy:
        drawBubbleMark(spi, 290, 40, 10, primaryColor, offset);
        drawBubbleMark(spi, 270, 52, 6, primaryColor, -offset);
        break;
      default:
        // noop
        break;
    }
  }
};

}  // namespace m5avatar

#endif  // EFFECT_H_
