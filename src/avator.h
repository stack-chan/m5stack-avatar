#pragma once
#include <FastLCD.h>

class Mouth
{
private:
  int x;
  int y;
  int minWidth;
  int maxWidth;
  int minHeight;
  int maxHeight;
  int lastX;
  int lastY;
  int lastW;
  int lastH;
  float openRatio;
  uint32_t primaryColor;
  uint32_t secondaryColor;
  void clear(void);
  void _draw(int x1, int y1, int x2, int y2);
public:
  // constructor
  Mouth();
  Mouth(int x, int y,
  int minWidth, int maxWidth,
  int minHeight, int maxHeight,
  uint32_t primaryColor, uint32_t secondaryColor);
  void setOpenRatio(float ratio);
  void open(int percent);
  void draw(void);
};

class Eye
{
private:
  int x;
  int y;
  int r;
  int lastX;
  int lastY;
  int lastR;
  float openRatio;
  uint32_t primaryColor;
  uint32_t secondaryColor;
  void clear(void);
  void drawCircle(int x, int y, int r);
  void drawRect(int x, int y, int w, int h);
public:
  // constructor
  Eye();
  Eye(int x, int y, int r, uint32_t primaryColor, uint32_t secondaryColor);
  void setOpenRatio(float ratio);
  void open(boolean isOpen);
  void draw(void);
};

class Avator
{
private:
  Mouth mouth;
  Eye eyeR;
  Eye eyeL;
public:
  // constructor
  Avator(void);

  void openMouth(int percent);
  void openEye(boolean isOpen);
  void setMouthOpen(float f);
  void setEyeOpen(float f);
  void smile(void);
  void init(void);
  void draw(void);
};