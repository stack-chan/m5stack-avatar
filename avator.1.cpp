#include <M5Stack.h>

class Mouth
{
private:
  int x;
  int y;
  int minWidth;
  int maxWidth;
  int minHeight;
  int maxHeight;
  int lastX1;
  int lastX2;
  int lastY1;
  int lastY2;
  uint32_t primaryColor;
  uint32_t secondaryColor;
  void clear()
  {
    M5.Lcd.fillRect(lastX1, lastY1, lastX2, lastY2, secondaryColor);
  }
  void draw(int x1, int y1, int x2, int y2)
  {
    clear();
    M5.Lcd.fillRect(x1, x2, y1, y2, primaryColor);
    lastX1 = x1;
    lastY1 = y1;
    lastX2 = x2;
    lastY2 = y2;
  }
public:
  Mouth(int x, int y,
  int minWidth, int maxWidth,
  int minHeight, int maxHeight,
  uint32_t primaryColor, uint32_t secondaryColor)
  {
    // TODO: validation
    this->x = x;
    this->y = y;
    this->minWidth = minWidth;
    this->maxWidth = maxWidth;
    this->minHeight = minHeight;
    this->maxHeight = maxHeight;
    this->primaryColor = primaryColor;
    this->secondaryColor = secondaryColor;
    this->lastX1 = 0;
    this->lastX2 = 0;
    this->lastY1 = 0;
    this->lastY2 = 0;
  }
  void open(int percent)
  {
    int h = minHeight + (maxHeight - minHeight) * percent / 100;
    int w = minWidth + (maxWidth - minWidth) * percent / 100;
    int x = this->x - w / 2;
    int y = this->y - h / 2;
    draw(x, y, x + w, y + h);
  }
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
  uint32_t primaryColor;
  uint32_t secondaryColor;
  void clear()
  {
    M5.Lcd.fillRect(lastX - lastR, lastY - lastR,
    lastX + lastR, lastY + lastR, secondaryColor);
  }
  void drawCircle(int x, int y, int r)
  {
    clear();
    M5.Lcd.fillCircle(x, y, r, primaryColor);
    lastX = x;
    lastY = y;
    lastR = r;
  }
  void drawRect(int x1, int y1, int x2, int y2)
  {
    clear();
    M5.Lcd.fillRect(x1, y1, x2, y2, primaryColor);
    lastX = x1 + (x2 - x1) / 2;
    lastY = y1 + (y2 - y1) / 2;
    lastR = x2 - x1; // TODO: ellipse
  }
public:
  Eye(int x, int y, int r, uint32_t primaryColor, uint32_t secondaryColor)
  {
    this->x = x;
    this->y = y;
    this->r = r;
    this->lastX = 0;
    this->lastY = 0;
    this->lastR = 0;
    this->primaryColor = primaryColor;
    this->secondaryColor = secondaryColor;
  }
  void open(boolean isOpen)
  {
    if(isOpen)
    {
      // TODO: "wideness"
      drawCircle(x, y, r);
    }
    else
    {
      int x1 = x - r;
      int y1 = y = r;
      int x2 = x + r;
      int y2 = y + r;
      drawRect(x1, y1, x2, y2);
    }
  }
};

#define PRIMARY_COLOR = WHITE
#define SECONDARY_COLOR = BLACK

class Avator
{
private:
  Mouth mouth;
  Eye eyeR;
  Eye eyeL;
public:
  Avator()
  {
    mouth = new Mouth(160, 200, 30, 100, 8, 60, PRIMARY_COLOR, SECONDARY_COLOR);
    eyeR = new Eye(90, 83, 8, PRIMARY_COLOR, SECONDARY_COLOR);
    eyeL = new Eye(230, 96, 8, PRIMARY_COLOR, SECONDARY_COLOR);
  }
  void openMouth(int percent)
  {
    mouth.open(percent);
  }
  void openEye(boolean isOpen)
  {
    eyeR->openEye(isOpen);
    eyeL->openEye(isOpen);
  }
  void smile()
  {
    // TODO
  }
  void init()
  {
    // TODO: start animation
  }
};
