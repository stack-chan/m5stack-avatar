// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef DRAWCONTEXT_H_
#define DRAWCONTEXT_H_

#include "ColorPalette.h"
#include "Expression.h"
#include "Gaze.h"

namespace m5avatar {
class DrawContext {
 private:
  Expression expression;
  float breath;
  float eyeOpenRatio;
  float mouthOpenRatio;
  Gaze gaze;
  ColorPalette * const palette;
  const char* speechText;

 public:
  DrawContext() = delete;
  DrawContext(Expression expression, float breath, ColorPalette* const palette,
              Gaze gaze, float eyeOpenRatio, float mouthOpenRatio,
              const char* speechText);
  ~DrawContext() = default;
  DrawContext(const DrawContext& other) = delete;
  DrawContext& operator=(const DrawContext& other) = delete;
  Expression getExpression() const;
  float getBreath() const;
  float getEyeOpenRatio() const;
  float getMouthOpenRatio() const;
  Gaze getGaze() const;
  ColorPalette* const getColorPalette() const;
  const char* getspeechText() const;
};
}  // namespace m5avatar

#endif  // DRAWCONTEXT_H_
