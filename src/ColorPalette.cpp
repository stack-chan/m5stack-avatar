// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "ColorPalette.h"

namespace m5avatar {
ColorPalette::ColorPalette()
    : colors{{COLOR_PRIMARY, TFT_WHITE},
             {COLOR_SECONDARY, TFT_BLACK},
             {COLOR_BACKGROUND, TFT_BLACK},
             {COLOR_BALLOON_FOREGROUND, TFT_BLACK},
             {COLOR_BALLOON_BACKGROUND, TFT_WHITE}} {}

uint16_t ColorPalette::get(const char* key) const {
  auto itr = colors.find(key);
  if (itr != colors.end()) {
    return itr->second;
  } else {
    // NOTE: if no value it returns BLACK(0x00) as the default value of the
    // type(int)
    M5_LOGI("no color with the key %s", key);
    return TFT_BLACK;
  }
}

void ColorPalette::set(const char* key, uint16_t value) {
  auto itr = colors.find(key);
  if (itr != colors.end()) {
    M5_LOGI("Overwriting");
  }
  itr->second = value;
}
}  // namespace m5avatar
