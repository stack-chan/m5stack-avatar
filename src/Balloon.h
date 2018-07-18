// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef BALLOON_H_
#define BALLOON_H_
#include <M5Stack.h>
#include "DrawContext.h"
#include "Drawable.h"

const int16_t TEXT_HEIGHT = 8;
const int16_t TEXT_SIZE = 2;
const int16_t MIN_WIDTH = 40;
const uint32_t primaryColor = TFT_BLACK;
const uint32_t backgroundColor = TFT_WHITE;
const int cx = 240;
const int cy = 220;

namespace m5avatar {
class Balloon final : public Drawable {
 public:
  // constructor
  Balloon() = default;
  ~Balloon() = default;
  Balloon(const Balloon &other) = default;
  Balloon &operator=(const Balloon &other) = default;
  void draw(TFT_eSPI *spi, BoundingRect rect,
            DrawContext *drawContext) override {
    const char *text = drawContext->getspeechText();
    if (strlen(text) == 0) {
      return;
    }
    M5.Lcd.setTextSize(TEXT_SIZE);
    M5.Lcd.setTextDatum(MC_DATUM);
    spi->setTextSize(TEXT_SIZE);
    spi->setTextColor(primaryColor, backgroundColor);
    spi->setTextDatum(MC_DATUM);
    int textWidth = M5.Lcd.textWidth(text, 2);
    int textHeight = TEXT_HEIGHT * TEXT_SIZE;
    spi->fillEllipse(cx, cy, _max(textWidth, MIN_WIDTH) + 2, textHeight * 2 + 2,
                     primaryColor);
    spi->fillTriangle(cx - 62, cy - 42, cx - 8, cy - 10, cx - 41, cy - 8,
                      primaryColor);
    spi->fillEllipse(cx, cy, _max(textWidth, MIN_WIDTH), textHeight * 2,
                     backgroundColor);
    spi->fillTriangle(cx - 60, cy - 40, cx - 10, cy - 10, cx - 40, cy - 10,
                      backgroundColor);
    spi->drawString(text, cx, cy,
                    2);  // Continue printing from new x position
  }
};

}  // namespace m5avatar

#endif  // BALLOON_H_
