// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef DRAWCONTEXT_H_
#define DRAWCONTEXT_H_

#define ERACER_COLOR 0x0000

#include "M5GFX.h"
#include "ColorPalette.h"
#include "Expression.h"
#include "Gaze.h"


namespace m5avatar {
enum BatteryIconStatus { discharging, charging, invisible, unknown };
class DrawContext {
 private:
  Expression expression;
  float breath;
  float eyeOpenRatio;
  float mouthOpenRatio;
  Gaze gaze;
  ColorPalette * const palette;
  const char* speechText;
  float rotation = 0.0;
  float scale = 1.0;
  int colorDepth = 1;
  BatteryIconStatus batteryIconStatus = BatteryIconStatus::invisible;
  int32_t batteryLevel = 0;
  const lgfx::IFont* speechFont = nullptr; // = &fonts::lgfxJapanGothicP_16; //  = &fonts::efontCN_10;

 public:
  DrawContext() = delete;
  DrawContext(Expression expression, float breath, ColorPalette* const palette,
              Gaze gaze, float eyeOpenRatio, float mouthOpenRatio,
              const char* speechText, BatteryIconStatus batteryIconStatus, int32_t batteryLevel, const lgfx::IFont* speechFont);
  DrawContext(Expression expression, float breath, ColorPalette* const palette,
              Gaze gaze, float eyeOpenRatio, float mouthOpenRatio,
              const char* speechText, float rotation, float scale, int colorDepth, BatteryIconStatus batteryIconStatus, int32_t batteryLevel, const lgfx::IFont* speechFont);
  ~DrawContext() = default;
  DrawContext(const DrawContext& other) = delete;
  DrawContext& operator=(const DrawContext& other) = delete;
  Expression getExpression() const;
  float getBreath() const;
  float getEyeOpenRatio() const;
  float getMouthOpenRatio() const;
  float getScale() const;
  float getRotation() const;
  Gaze getGaze() const;
  ColorPalette* const getColorPalette() const;
  const char* getspeechText() const;
  int getColorDepth() const;
  BatteryIconStatus getBatteryIconStatus() const;
  int32_t getBatteryLevel() const;
  const lgfx::IFont* getSpeechFont() const; 
};
}  // namespace m5avatar

#endif  // DRAWCONTEXT_H_
