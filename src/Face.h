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
  Drawable *eyeR;
  Drawable *eyeL;
  EyeblowInterface *eyeblowR;
  EyeblowInterface *eyeblowL;
  TFT_eSprite *sprite;
  BoundingRect *boundingRect;
  BoundingRect *mouthPos;
  BoundingRect *eyeRPos;
  BoundingRect *eyeLPos;
  BoundingRect *eyeblowRPos;
  BoundingRect *eyeblowLPos;

public:
  // constructor
  Face();
  Face(MouthInterface* mouth, Drawable* eyeR, Drawable* eyeL, EyeblowInterface* eyeblowR, EyeblowInterface* eyeblowL);
  // TODO: apply builder pattern
  Face(MouthInterface *mouth,
       BoundingRect *mouthPos,
       Drawable *eyeR,
       BoundingRect *eyeRPos,
       Drawable *eyeL,
       BoundingRect *eyeLPos,
       EyeblowInterface *eyeblowR,
       BoundingRect *eyeblowRPos,
       EyeblowInterface *eyeblowL,
       BoundingRect *eyeblowLPos);
  ~Face();
  Face(const Face &other) = default;
  Face &operator=(const Face &other) = default;

  Drawable *getLeftEye();
  Drawable *getRightEye();

  // void setParts(PartsType p, Drawable parts);
  // Drawable *getParts(PartsType p);

  MouthInterface *getMouth();
  BoundingRect *getBoundingRect();

  void setLeftEye(Drawable *eye);
  void setRightEye(Drawable *eye);
  void setMouth(MouthInterface *mouth);
  void setLeftEyeblow();
  void setRightEyeblow();

  void setMouthOpen(float f);
  void draw(DrawContext *ctx);
};
} // namespace m5avatar