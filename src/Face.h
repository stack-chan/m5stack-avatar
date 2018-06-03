// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include <M5Stack.h> // TODO: include only the Sprite function not a whole library
#include "Mouth.h"
#include "Eye.h"
#include "Eyeblow.h"
#include "BoundingRect.h"

namespace m5avatar
{

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
  Face(MouthInterface* mouth, EyeInterface* eyeR, EyeInterface* eyeL, EyeblowInterface* eyeblowR, EyeblowInterface* eyeblowL);
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