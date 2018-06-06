// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <utility/In_eSPI.h>
#include "DrawContext.h"
#include "Drawable.h"

namespace m5avatar
{
class EyeInterface : public Drawable
{
public:
  virtual void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *drawContext) = 0;
  // virtual void draw(TFT_eSPI *spi, DrawContext *drawContext) = 0; // deprecated
  virtual void setOpenRatio(float ratio) = 0;
  virtual void setOffset(int offsetX, int offsetY) = 0;
};

class Eye final : public EyeInterface
{
private:
  uint16_t x;
  uint16_t y;
  uint16_t r;
  int32_t offsetX;
  int32_t offsetY;
  bool isLeft;
  float openRatio;

public:
  // constructor
  Eye() = delete;
  Eye(uint16_t x, uint16_t y, uint16_t r, bool isLeft);
  ~Eye() = default;
  Eye(const Eye &other) = default;
  Eye &operator=(const Eye &other) = default;
  void setOpenRatio(float ratio) override;
  void setOffset(int32_t offsetX, int32_t offsetY) override;
  void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *drawContext) override;
  // void draw(TFT_eSPI *spi, DrawContext *drawContext) override; // deprecated
};
  
}