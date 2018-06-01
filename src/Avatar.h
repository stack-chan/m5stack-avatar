// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include "Face.h"
#include <AquesTalkTTS.h> // TODO
#include "ColorPalette.h"

namespace m5avatar
{
class Avatar
{
  private:
    Face* face;
    Expression expression;
    float gazeV;
    float gazeH;
    // TODO: below are not of face rather avatar
    float breath;
    bool _isDrawing;
    ColorPalette palette;
  public:
    Avatar();
    Avatar(Face* face);
    ~Avatar() = default;
    Avatar(const Avatar &other) = default;
    Avatar &operator=(const Avatar &other) = default;
    Face* getFace() const;
    ColorPalette getColorPalette() const;
    void setColorPalette(ColorPalette cp);
    void setFace(Face *face);
    void init(void);
    void setBreath(float f);
    void setGaze(float vertical, float horizontal);
    void setExpression(Expression exp);
    void drawBalloon(TFT_eSPI *spi); // Experimental
    void draw(void);
    bool isDrawing();
    void start();
    void stop();
    void addTask(TaskFunction_t f, std::string name);
};

class DriveContext
{
private:
  // TODO: cyclic reference
  Avatar *avatar;
  // Use wrapper class for voice engine
  AquesTalkTTS *TTS;

public:
  DriveContext() = delete;
  DriveContext(Avatar *avatar);
  ~DriveContext() = default;
  DriveContext(const DriveContext &other) = delete;
  DriveContext &operator=(const DriveContext &other) = delete;
  Avatar *getAvatar();
};

}
