// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef AVATAR_H_
#define AVATAR_H_
#include "ColorPalette.h"
#include "Face.h"

namespace m5avatar {
class Avatar {
 private:
  Face *face;
  bool _isDrawing;
  Expression expression;
  float breath;
  float eyeOpenRatio;
  float mouthOpenRatio;
  float gazeV;
  float gazeH;
  float rotation;
  float scale;
  ColorPalette palette;
  const char *speechText;

 public:
  Avatar();
  explicit Avatar(Face *face);
  ~Avatar() = default;
  Avatar(const Avatar &other) = default;
  Avatar &operator=(const Avatar &other) = default;
  Face *getFace() const;
  ColorPalette getColorPalette() const;
  void setColorPalette(ColorPalette cp);
  void setFace(Face *face);
  void init(void);
  void setBreath(float f);
  void setGaze(float vertical, float horizontal);
  void setExpression(Expression exp);
  void setEyeOpenRatio(float ratio);
  void setMouthOpenRatio(float ratio);
  void setSpeechText(const char *speechText);
  void setRotation(float radian);
  void setPosition(int top, int left);
  void setScale(float scale);
  void draw(void);
  bool isDrawing();
  void start();
  void stop();
  void addTask(TaskFunction_t f, const char* name);
};

class DriveContext {
 private:
  // TODO(meganetaaan): cyclic reference
  Avatar *avatar;

 public:
  DriveContext() = delete;
  explicit DriveContext(Avatar *avatar);
  ~DriveContext() = default;
  DriveContext(const DriveContext &other) = delete;
  DriveContext &operator=(const DriveContext &other) = delete;
  Avatar *getAvatar();
};

}  // namespace m5avatar

#endif  // AVATAR_H_
