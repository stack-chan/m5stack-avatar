// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include <utility/In_eSPI.h>
#include "DrawContext.h"
#include "BoundingRect.h"

namespace m5avatar
{
class Drawable

{
public:
  virtual ~Drawable();
  virtual void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *drawContext) = 0;
  // virtual void draw(TFT_eSPI *spi, DrawContext *drawContext) = 0;
};

}