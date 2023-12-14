// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef AVATAR_H_
#define AVATAR_H_
#include "ColorPalette.h"
#include "Face.h"
#include <M5GFX.h>

#ifdef SDL_h_
typedef SDL_ThreadFunction TaskFunction_t;
typedef int BaseType_t;
typedef unsigned int UBaseType_t;
typedef SDL_Thread* TaskHandle_t;
typedef int TaskResult_t;
#define APP_CPU_NUM (1)
#else
typedef void TaskResult_t;
#endif

#ifndef APP_CPU_NUM
#define APP_CPU_NUM PRO_CPU_NUM
#endif

#ifndef ARDUINO
#include <string>
typedef std::string String;
#endif  // ARDUINO

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
  String speechText;
  int colorDepth;
  BatteryIconStatus batteryIconStatus;
  int32_t batteryLevel;
  const lgfx::IFont *speechFont;

 public:
  Avatar();
  explicit Avatar(Face *face);
  ~Avatar();
  Avatar(const Avatar &other) = default;
  Avatar &operator=(const Avatar &other) = default;
  Face *getFace() const;
  ColorPalette getColorPalette() const;
  void setColorPalette(ColorPalette cp);
  void setFace(Face *face);
  void init(int colorDepth = 1);
  Expression getExpression();
  void setBreath(float f);
  float getBreath();
  void setGaze(float vertical, float horizontal);
  void getGaze(float *vertical, float *horizontal);
  void setExpression(Expression exp);
  void setEyeOpenRatio(float ratio);
  void setMouthOpenRatio(float ratio);
  void setSpeechText(const char *speechText);
  void setSpeechFont(const lgfx::IFont *speechFont);
  void setRotation(float radian);
  void setPosition(int top, int left);
  void setScale(float scale);
  void draw(void);
  bool isDrawing();
  void start(int colorDepth = 1);
  void stop();
  void addTask(TaskFunction_t f
              , const char* name
              , const uint32_t stack_size=2048
              , UBaseType_t priority=4
              , TaskHandle_t* const task_handle=NULL
              , const BaseType_t core_id=APP_CPU_NUM);
  void suspend();
  void resume();
  void setBatteryIcon(bool iconStatus);
  void setBatteryStatus(bool isCharging, int32_t batteryLevel);
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
