// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <utility/In_eSPI.h>
#include "DrawContext.h"
#include "Drawable.h"

namespace m5avatar
{

class Balloon final : public Drawable
{
public:
  // constructor
  Balloon() = default;
  ~Balloon() = default;
  Balloon(const Balloon &other) = default;
  Balloon &operator=(const Balloon &other) = default;
  uint32_t primaryColor = TFT_BLACK;
  uint32_t backgroundColor = TFT_WHITE;
  void draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *drawContext) override
  {
    const char *text = drawContext->getspeechText();
    if (strlen(text) == 0)
    {
      return;
    }
    spi->fillEllipse(280, 220, 60, 40, backgroundColor);
    spi->fillTriangle(220, 180, 270, 210, 240, 210, backgroundColor);
    spi->setTextSize(2);
    spi->setTextColor(primaryColor, backgroundColor);
    spi->drawString(text, 240, 200, 2); // Continue printing from new x position
  }
};

} // namespace m5avatar
