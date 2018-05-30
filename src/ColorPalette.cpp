// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "ColorPalette.h"

namespace m5avatar
{
  ColorPalette::ColorPalette()
  {
    colors[COLOR_PRIMARY] = TFT_WHITE;
    colors[COLOR_SECONDARY] = TFT_BLACK;
  }

  uint32_t ColorPalette::get(std::string key)
  {
    // NOTE: if no value it returns BLACK(0x00) as the default value of the type(int)
    return colors[key];
  }

  void ColorPalette::set(std::string key, uint32_t value)
  {
    auto itr = colors.find(key);
    if (itr != colors.end())
    {
      Serial.println("Overwriting");
      itr->second = value;
    }
    else
    {
      colors[key] = value;
    }
  }
}