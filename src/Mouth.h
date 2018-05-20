// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include "DrawContext.h"
#include <utility/In_eSPI.h>
using namespace m5avatar;

class MouthInterface
{
public:
  virtual ~MouthInterface() {}
  virtual void setOpenRatio(float ratio) = 0;
  virtual void draw(TFT_eSPI *spi, DrawContext *drawContext) = 0;
};
class Mouth : public MouthInterface
{
private:
  int x;
  int y;
  int minWidth;
  int maxWidth;
  int minHeight;
  int maxHeight;
  float openRatio;
  uint32_t primaryColor;
  uint32_t secondaryColor;
  void _drawRect(TFT_eSPI *spi, int x0, int y0, int x1, int y1);
  void _drawCircle(TFT_eSPI *spi, int x0, int y0, int x1, int y1);
  void _drawTriangle(TFT_eSPI *spi, int x0, int y0, int x1, int y1, int x2, int y2);

public:
  // constructor
  Mouth();
  Mouth(int x, int y,
        int minWidth, int maxWidth,
        int minHeight, int maxHeight,
        uint32_t primaryColor, uint32_t secondaryColor);
  void setOpenRatio(float ratio);
  void draw(TFT_eSPI *spi, DrawContext *drawContext);
};
