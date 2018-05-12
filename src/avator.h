// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include <M5Stack.h>
#include "Sprite.h"

enum Expression {
  Happy,
  Angry,
  Sad,
  Doubt,
  Sleepy,
  Neutral
};

class DrawContext {
private:
  Expression expression;
  float breath;
public:
  DrawContext(void);
  DrawContext(Expression expression, float breath);
  Expression getExpression();
  float getBreath();
};

class Mouth
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
  void draw(DrawContext drawContext);
  void draw(TFT_eSprite *spi, DrawContext drawContext);
};

class Eye
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
  Eye();
  Eye(int x, int y, int r, bool isLeft, uint32_t primaryColor, uint32_t secondaryColor);
  void setOpenRatio(float ratio);
  void setOffset(int offsetX, int offsetY);
  void draw(TFT_eSprite *spi, DrawContext drawContext);
};

class Avator
{
private:
  Mouth mouth;
  Eye eyeR;
  Eye eyeL;
  float breath;
  Expression expression;
  DrawContext drawContext;
  TFT_eSprite *avatorSprite;
  void drawLoop(void);
public:
  // constructor
  Avator(void);

  // TODO: getter
  void openMouth(int percent);
  void openEye(boolean isOpen);
  void setMouthOpen(float f);
  void setEyeOpen(float f);
  void setBreath(float f);
  void setGaze(float vertical, float horizontal);
  void setExpression(Expression exp); // TODO
  void init(void);
  void draw(void);
};