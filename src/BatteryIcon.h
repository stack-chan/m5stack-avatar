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
  void drawBatteryIcon(M5Canvas *spi, uint32_t x, uint32_t y, uint16_t fgcolor, uint16_t bgcolor, float offset) {
    //int32_t battery_level = M5.Power.getBatteryLevel();
    //M5.Log.printf("batterylevel:%d\n", battery_level);
//    if (M5.Power.isCharging()) {
      //color = TFT_GREEN;
    //} else {
      //color = TFT_RED;
    //}
    //uint32_t battery_level = M5.Power.getBatteryLevel();
    //M5.Log.printf("BatteryLevel:%d\n", battery_level);
    spi->drawRect(x, y + 5, 5, 5, fgcolor);
    spi->drawRect(x + 5, y, 30, 15, fgcolor);
    int battery_width = 30 * (float)(M5.Power.getBatteryLevel() / 100.0f);
    spi->fillRect(x + 5 + 30 - battery_width, y, battery_width, 15, fgcolor);
  }

 public:
  // constructor
  BatteryIcon() = default;
  ~BatteryIcon() = default;
  BatteryIcon(const BatteryIcon &other) = default;
  BatteryIcon &operator=(const BatteryIcon &other) = default;
  void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx) override {
    if (ctx->getBatteryIcon()) {
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);
      uint16_t bgColor = ctx->getColorDepth() == 1 ? ERACER_COLOR : ctx->getColorPalette()->get(COLOR_BACKGROUND);
      float offset = ctx->getBreath();
      drawBatteryIcon(spi, 285, 5, primaryColor, bgColor, -offset);
    }
  };

};

}  // namespace m5avatar

#endif  // BATTERYICON_H_
