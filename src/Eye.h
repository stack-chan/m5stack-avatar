// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <utility/In_eSPI.h>
#include "DrawContext.h"
using namespace m5avatar;

class EyeInterface
{
public:
  virtual ~EyeInterface() {}
  virtual void draw(TFT_eSPI *spi, DrawContext *drawContext) = 0;
  virtual void setOpenRatio(float ratio) = 0;
  virtual void setOffset(int offsetX, int offsetY) = 0;
};

class Eye : public EyeInterface
{
private:
  int x;
  int y;
  int r;
  bool isLeft;
  int offsetX;
  int offsetY;
  float openRatio;
  uint32_t primaryColor;
  uint32_t secondaryColor;
  void drawCircle(TFT_eSPI *spi, int x, int y, int r);
  void drawRect(TFT_eSPI *spi, int x, int y, int w, int h);

public:
  // constructor
  Eye(int x, int y, int r, bool isLeft, uint32_t primaryColor, uint32_t secondaryColor);
  ~Eye();
  void setOpenRatio(float ratio);
  void setOffset(int offsetX, int offsetY);
  void draw(TFT_eSPI *spi, DrawContext *drawContext);
};

