// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "Gaze.h"

namespace m5avatar {
Gaze::Gaze() : v{0}, h{0} {}

Gaze::Gaze(float v, float h) : v{v}, h{h} {}

float Gaze::getVertical() const { return v; }

float Gaze::getHorizontal() const { return h; }
}  // namespace m5avatar
