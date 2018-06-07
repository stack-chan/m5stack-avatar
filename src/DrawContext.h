// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include "Expression.h"
#include "ColorPalette.h"
#include "Gaze.h"

namespace m5avatar
{
class DrawContext
{
private:
  Expression expression;
  float breath;
  float eyeOpenRatio;
  ColorPalette palette;
  Gaze gaze;

public:
  DrawContext() = delete;
  DrawContext(Expression expression, float breath, ColorPalette palette, Gaze gaze, float eyeOpenRatio);
  ~DrawContext() = default;
  DrawContext(const DrawContext &other) = delete;
  DrawContext &operator=(const DrawContext &other) = delete;
  Expression getExpression() const;
  float getBreath() const;
  float getEyeOpenRatio() const;
  Gaze getGaze() const;
  ColorPalette getColorPalette() const;
};
}