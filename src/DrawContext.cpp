// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "DrawContext.h"
namespace m5avatar {

// DrawContext
DrawContext::DrawContext(Expression expression, float breath, ColorPalette palette, Gaze gaze)
: expression{expression}, breath{breath}, palette(palette), gaze{gaze}
{}

Expression DrawContext::getExpression() const
{
  return expression;
}

float DrawContext::getBreath() const
{
  return breath;
}

Gaze DrawContext::getGaze() const
{
  return gaze;
}

ColorPalette DrawContext::getColorPalette() const
{
  return palette;
}

}
