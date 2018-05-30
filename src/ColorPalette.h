// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include <M5Stack.h>
#include <map>
namespace m5avatar
{
  const std::string COLOR_PRIMARY = "primary";
  const std::string COLOR_SECONDARY = "secondary";
  // enum class ColorType
  // {
  //   ONEBYTE,
  //   TWOBYTE,
  //   ONEBIT
  // }
  /**
   * Color palette for drawing face
   */
  class ColorPalette
  {
    private:
    // ColorType colorType;
    // uint32_t colors[2];
    std::map<std::string, uint32_t> colors;

    public:
    ColorPalette();
    ~ColorPalette() = default;
    ColorPalette(const ColorPalette &other) = default;
    ColorPalette &operator=(const ColorPalette &other) = default;

    uint32_t get(std::string key);
    void set(std::string key, uint32_t value);
    void clear(void);
  };
}