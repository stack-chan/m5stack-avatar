// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include "Face.h"
#include <AquesTalkTTS.h> // TODO

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
  public:
    Avatar();
    Avatar(Face* face);
    ~Avatar();
    Face* getFace();
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
    // TODO
    // void addTask(Task task);
};

class DriveContext
{
private:
  // TODO: cyclic reference
  Avatar *avatar;
  // Use wrapper class for voice engine
  AquesTalkTTS *TTS;
  bool _isDrawing;

public:
  DriveContext(Avatar *avatar);
  ~DriveContext(){};
  Avatar *getAvatar();
};

}
