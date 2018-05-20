// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <utility/In_eSPI.h>
#include "DrawContext.h"
using namespace m5avatar;

class EyeblowInterface
{
public:
  virtual ~EyeblowInterface() {}
  virtual void draw(TFT_eSPI *spi, DrawContext *drawContext) = 0;
};

class Eyeblow : public EyeblowInterface
{
private:
  int x;
  int y;
  int width;
  int height;
  bool isLeft;
  uint32_t primaryColor;
  uint32_t secondaryColor;

public:
  // constructor
  Eyeblow(int x, int y, int w, int h, bool isLeft, uint32_t primaryColor, uint32_t secondaryColor);
  ~Eyeblow();
  void draw(TFT_eSPI *spi, DrawContext *drawContext);
};

