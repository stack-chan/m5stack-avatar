// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include "Expression.h"
#include "ColorPalette.h"

namespace m5avatar
{
class DrawContext
{
private:
  Expression expression;
  float breath;
  ColorPalette palette;

public:
  DrawContext() = delete;
  DrawContext(Expression expression, float breath, ColorPalette palette);
  ~DrawContext() = default;
  DrawContext(const DrawContext &other) = delete;
  DrawContext &operator=(const DrawContext &other) = delete;
  const Expression getExpression();
  const float getBreath();
  ColorPalette getColorPalette();
};
}