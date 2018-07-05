// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef BOUNDINGRECT_H_
#define BOUNDINGRECT_H_
#include <Arduino.h>

namespace m5avatar {
class BoundingRect {
 private:
  int16_t top;
  int16_t left;
  int16_t width;
  int16_t height;

 public:
  BoundingRect() = default;
  ~BoundingRect() = default;
  BoundingRect(int16_t top, int16_t left);
  BoundingRect(int16_t top, int16_t left, int16_t width, int16_t height);
  BoundingRect(const BoundingRect &other) = default;
  BoundingRect &operator=(const BoundingRect &other) = default;
  int16_t getTop();
  int16_t getLeft();
  int16_t getRight();
  int16_t getBottom();
  int16_t getCenterX();
  int16_t getCenterY();
  int16_t getWidth();
  int16_t getHeight();
  void setPosition(int16_t top, int16_t left);
  void setSize(int16_t width, int16_t height);
};
}  // namespace m5avatar

#endif  // BOUNDINGRECT_H_
