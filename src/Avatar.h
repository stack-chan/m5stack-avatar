// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef AVATAR_H_
#define AVATAR_H_
#include <M5GFX.h>

#include "ColorPalette.h"
#include "Face.h"

#ifdef SDL_h_
typedef SDL_ThreadFunction TaskFunction_t;
typedef int BaseType_t;
typedef unsigned int UBaseType_t;
typedef SDL_Thread *TaskHandle_t;
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

  // eyes variables
  float rightEyeOpenRatio_;
  float rightGazeV_;
  float rightGazeH_;

  float leftEyeOpenRatio_;
  float leftGazeV_;
  float leftGazeH_;

  bool isAutoBlink_;

  float mouthOpenRatio;

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
  // expression i/o
  Expression getExpression();
  void setExpression(Expression exp);
  // breath i/o
  void setBreath(float f);
  float getBreath();
  // gaze i/o
  void setRightGaze(float vertical, float horizontal);
  void getRightGaze(float *vertical, float *horizontal);
  void setLeftGaze(float vertical, float horizontal);
  void getLeftGaze(float *vertical, float *horizontal);

  /**
   * @brief Get the Gaze of Avatar
   *
   * [warning] this function return the mean gaze of left gaze & right gaze
   * This is not the gaze representing avatar's direction of awareness
   *
   * @param vertical cache for vertical value. this value will be overwritten
   * by this method.
   * @param horizontal cache for horizontal value. this value will be
   * overwritten by this method.
   */
  void getGaze(float *vertical, float *horizontal);

  // eyes open ratio
  void setEyeOpenRatio(float ratio);
  void setRightEyeOpenRatio(float ratio);
  float getRightEyeOpenRatio();
  void setLeftEyeOpenRatio(float ratio);
  float getLeftEyeOpenRatio();
  void setIsAutoBlink(bool b);
  bool getIsAutoBlink();

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
  void addTask(TaskFunction_t f, const char *name,
               const uint32_t stack_size = 2048, UBaseType_t priority = 4,
               TaskHandle_t *const task_handle = NULL,
               const BaseType_t core_id = APP_CPU_NUM);
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
