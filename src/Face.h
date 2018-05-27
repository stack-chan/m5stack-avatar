// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include <M5Stack.h> // TODO: include only the Sprite function not a whole library
#include "Mouth.h"
#include "Eye.h"
#include "Eyeblow.h"

namespace m5avatar
{

class BoundingRect
{
  private:
  int16_t top;
  int16_t left;
  int16_t width;
  int16_t height;

  public:
  BoundingRect() = default;
  ~BoundingRect() = default;
  // BoundingRect(int16_t top = 0, int16_t left = 0, int16_t width = 320, int16_t height = 240);
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

class Face
{
private:
  MouthInterface *mouth;
  EyeInterface *eyeR;
  EyeInterface *eyeL;
  EyeblowInterface *eyeblowR;
  EyeblowInterface *eyeblowL;
  TFT_eSprite *sprite;
  BoundingRect *boundingRect;

public:
  // constructor
  Face();
  ~Face();
  Face(const Face &other) = default;
  Face &operator=(const Face &other) = default;

  EyeInterface *getLeftEye();
  EyeInterface *getRightEye();
  MouthInterface *getMouth();
  BoundingRect *getBoundingRect();

  void setLeftEye(EyeInterface *eye);
  void setRightEye(EyeInterface *eye);
  void setMouth(MouthInterface *mouth);
  void setLeftEyeblow();
  void setRightEyeblow();

  void setMouthOpen(float f);
  void setEyesOpen(float f);
  void draw(DrawContext *ctx);
};
} // namespace m5avatar