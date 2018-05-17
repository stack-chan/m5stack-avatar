// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include "Expression.h"

namespace m5avatar
{
class DrawContext
{
private:
  Expression expression;
  float breath;

public:
  DrawContext(void);
  DrawContext(Expression expression, float breath);
  Expression getExpression();
  float getBreath();
};
}