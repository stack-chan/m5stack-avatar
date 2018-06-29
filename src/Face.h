// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include <M5Stack.h> // TODO: include only the Sprite function not a whole library
#include "Mouth.h"
#include "Eye.h"
#include "Eyeblow.h"
#include "BoundingRect.h"
#include "Balloon.h"

namespace m5avatar
{

class Face
{
private:
  Drawable *mouth;
  Drawable *eyeR;
  Drawable *eyeL;
  Drawable *eyeblowR;
  Drawable *eyeblowL;
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
  Face(Drawable* mouth, Drawable* eyeR, Drawable* eyeL, Drawable* eyeblowR, Drawable* eyeblowL);
  // TODO: apply builder pattern
  Face(Drawable *mouth,
       BoundingRect *mouthPos,
       Drawable *eyeR,
       BoundingRect *eyeRPos,
       Drawable *eyeL,
       BoundingRect *eyeLPos,
       Drawable *eyeblowR,
       BoundingRect *eyeblowRPos,
       Drawable *eyeblowL,
       BoundingRect *eyeblowLPos);
  ~Face();
  Face(const Face &other) = default;
  Face &operator=(const Face &other) = default;

  Drawable *getLeftEye();
  Drawable *getRightEye();

  // void setParts(PartsType p, Drawable parts);
  // Drawable *getParts(PartsType p);

  Drawable *getMouth();
  BoundingRect *getBoundingRect();

  void setLeftEye(Drawable *eye);
  void setRightEye(Drawable *eye);
  void setMouth(Drawable *mouth);
  void setLeftEyeblow();
  void setRightEyeblow();

  void draw(DrawContext *ctx);
};
} // namespace m5avatar