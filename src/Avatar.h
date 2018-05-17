// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include <M5Stack.h>
#include "Sprite.h"

namespace m5avatar
{

enum Expression
{
  Happy,
  Angry,
  Sad,
  Doubt,
  Sleepy,
  Neutral
};

class DrawContext
{
private:
  Expression expression;
  float breath;

public:
  DrawContext(void);
  DrawContext(Expression expression, float breath);
  Expression getExpression();
  float getBreath();
};

class MouthInterface
{
public:
  virtual ~MouthInterface() {}
  virtual void setOpenRatio(float ratio) = 0;
  virtual void draw(TFT_eSprite *spi, DrawContext drawContext) = 0;
};
class Mouth : public MouthInterface
{
private:
  int x;
  int y;
  int minWidth;
  int maxWidth;
  int minHeight;
  int maxHeight;
  float openRatio;
  uint32_t primaryColor;
  uint32_t secondaryColor;
  void _drawRect(TFT_eSPI *spi, int x0, int y0, int x1, int y1);
  void _drawCircle(TFT_eSPI *spi, int x0, int y0, int x1, int y1);
  void _drawTriangle(TFT_eSPI *spi, int x0, int y0, int x1, int y1, int x2, int y2);

public:
  // constructor
  Mouth();
  Mouth(int x, int y,
        int minWidth, int maxWidth,
        int minHeight, int maxHeight,
        uint32_t primaryColor, uint32_t secondaryColor);
  void setOpenRatio(float ratio);
  void draw(TFT_eSprite *spi, DrawContext drawContext);
};

class EyeInterface
{
public:
  virtual ~EyeInterface() {}
  virtual void draw(TFT_eSprite *spi, DrawContext drawContext) = 0;
  virtual void setOpenRatio(float ratio) = 0;
  virtual void setOffset(int offsetX, int offsetY) = 0;
};

class Eye : public EyeInterface
{
private:
  int x;
  int y;
  int r;
  bool isLeft;
  int offsetX;
  int offsetY;
  float openRatio;
  uint32_t primaryColor;
  uint32_t secondaryColor;
  void drawCircle(TFT_eSPI *spi, int x, int y, int r);
  void drawRect(TFT_eSPI *spi, int x, int y, int w, int h);

public:
  // constructor
  Eye(int x, int y, int r, bool isLeft, uint32_t primaryColor, uint32_t secondaryColor);
  ~Eye();
  void setOpenRatio(float ratio);
  void setOffset(int offsetX, int offsetY);
  void draw(TFT_eSprite *spi, DrawContext drawContext);
};

class Avatar
{
private:
  MouthInterface *mouth;
  EyeInterface *eyeR;
  EyeInterface *eyeL;
  float breath;
  Expression expression;
  DrawContext drawContext;
  TFT_eSprite *avatarSprite;
  void drawLoop(void);

public:
  // constructor
  Avatar(void);

  // TODO: getter
  void openMouth(int percent);
  void openEye(boolean isOpen);
  void setMouthOpen(float f);
  void setEyeOpen(float f);
  void setBreath(float f);
  void setGaze(float vertical, float horizontal);
  void setExpression(Expression exp); // TODO
  void drawBalloon(TFT_eSPI *spi);
  void init(void);
  void draw(void);
  void draw(boolean yo);
};
} // namespace m5avatar