// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef BATTERYICON_H_
#define BATTERYICON_H_
#include <M5GFX.h>
#include <M5Unified.h>
#include "DrawContext.h"
#include "Drawable.h"

namespace m5avatar {

class BatteryIcon final : public Drawable {
 private:
  void drawBatteryIcon(M5Canvas *spi, uint32_t x, uint32_t y) {
    drawBatteryIcon(spi, x, y, 0);
  }

  void drawBatteryIcon(M5Canvas *spi, uint32_t x, uint32_t y, float offset) {
    uint16_t color = 0;
    if (M5.Power.isCharging()) {
      color = (uint16_t)0x00FF00;
    } else {
      color = (uint16_t)0xFF0000;
    }
    //uint32_t battery_level = M5.Power.getBatteryLevel();
    //M5.Log.printf("BatteryLevel:%d\n", battery_level);
    spi->fillRect(x, y + 5, 5, 5, color);
    spi->fillRect(x + 5, y, 30, 15, color);
  }

 public:
  // constructor
  BatteryIcon() = default;
  ~BatteryIcon() = default;
  BatteryIcon(const BatteryIcon &other) = default;
  BatteryIcon &operator=(const BatteryIcon &other) = default;
  void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx) override {
    uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);
    uint16_t bgColor = ctx->getColorDepth() == 1 ? ERACER_COLOR : ctx->getColorPalette()->get(COLOR_BACKGROUND);
    float offset = ctx->getBreath();
    drawBatteryIcon(spi, 5, 5, -offset);
  };

};

}  // namespace m5avatar

#endif  // BATTERYICON_H_
