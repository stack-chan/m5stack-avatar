// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "Avatar.h"

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

namespace m5avatar {

unsigned int seed = 0;

#ifndef rand_r
#define init_rand() srand(seed)
#define _rand() rand()
#else
#define init_rand() ;
#define _rand() rand_r(&seed)
#endif

#ifdef SDL_h_
#define TaskResult() return 0
#define TaskDelay(ms) lgfx::delay(ms)
long random(long howbig) {
  return std::rand() % howbig;
}
#else
#define TaskResult() vTaskDelete(NULL)
#define TaskDelay(ms) vTaskDelay(ms/portTICK_PERIOD_MS)
#endif

// TODO(meganetaaan): make read-only
DriveContext::DriveContext(Avatar *avatar) : avatar{avatar} {}

Avatar *DriveContext::getAvatar() { return avatar; }

TaskHandle_t drawTaskHandle;

TaskResult_t drawLoop(void *args) {
  DriveContext *ctx = reinterpret_cast<DriveContext *>(args);
  Avatar *avatar = ctx->getAvatar();
  while (avatar->isDrawing()) {
    if (avatar->isDrawing()) {
      avatar->draw();
    }
    TaskDelay(10);
  }
  TaskResult();
}

TaskResult_t facialLoop(void *args) {
  int c = 0;
  DriveContext *ctx = reinterpret_cast<DriveContext *>(args);
  Avatar *avatar = ctx->getAvatar();
  uint32_t saccade_interval = 1000;
  uint32_t blink_interval = 1000;
  unsigned long last_saccade_millis = 0;
  unsigned long last_blink_millis = 0;
  bool eye_open = true;
  float vertical = 0.0f;
  float horizontal = 0.0f;
  float breath = 0.0f;
  init_rand();
  while (avatar->isDrawing()) {

    if ((lgfx::millis() - last_saccade_millis) > saccade_interval) {
      vertical = _rand() / (RAND_MAX / 2.0) - 1;
      horizontal = _rand() / (RAND_MAX / 2.0) - 1;
      avatar->setGaze(vertical, horizontal);
      saccade_interval = 500 + 100 * random(20);
      last_saccade_millis = lgfx::millis();
    }

    if ((lgfx::millis()- last_blink_millis) > blink_interval) {
      if (eye_open) {
        avatar->setEyeOpenRatio(1);
        blink_interval = 2500 + 100 * random(20);
      } else {
        avatar->setEyeOpenRatio(0);
        blink_interval = 300 + 10 * random(20);
      }
      eye_open = !eye_open;
      last_blink_millis = lgfx::millis();
    }
    c = (c + 1) % 100;
    breath = sin(c * 2 * PI / 100.0);
    avatar->setBreath(breath);
    TaskDelay(33);
  }
  TaskResult();
}

Avatar::Avatar() : Avatar(new Face()) {}

Avatar::Avatar(Face *face)
    : face{face},
      _isDrawing{false},
      expression{Expression::Neutral},
      breath{0},
      eyeOpenRatio{1},
      mouthOpenRatio{0},
      gazeV{0},
      gazeH{0},
      rotation{0},
      scale{1},
      palette{ColorPalette()},
      speechText{""},
      colorDepth{1},
      batteryIconStatus{BatteryIconStatus::invisible}{}

Avatar::~Avatar() {
  delete face;
}

void Avatar::setFace(Face *face) { this->face = face; }

Face *Avatar::getFace() const { return face; }

void Avatar::addTask(TaskFunction_t f
                    , const char* name
                    , const uint32_t stack_size
                    , UBaseType_t priority
                    , TaskHandle_t* const task_handle
                    , const BaseType_t core_id) {
  DriveContext *ctx = new DriveContext(this);
#ifdef SDL_h_
  if (task_handle == NULL) {
    SDL_CreateThreadWithStackSize(f, name, stack_size, ctx);
  } else {
    *task_handle = SDL_CreateThreadWithStackSize(f, name, stack_size, ctx);
  }
#else
  // TODO(meganetaaan): set a task handler
  xTaskCreateUniversal(f,                    /* Function to implement the task */
                          name,              /* Name of the task */
                          stack_size,        /* Stack size in words */
                          ctx,               /* Task input parameter */
                          priority,          /* Priority of the task */
                          task_handle,       /* Task handle. */
                          core_id);          /* Core No*/
#endif
}

void Avatar::init(int colorDepth) {
  // for compatibility with older version
  start(colorDepth);
}

void Avatar::stop() { _isDrawing = false; }

void Avatar::suspend() {
#ifndef SDL_h_
  vTaskSuspend(drawTaskHandle);
#endif
}

void Avatar::resume() {
#ifndef SDL_h_
  vTaskResume(drawTaskHandle);
#endif
}

void Avatar::start(int colorDepth) { 
  // if the task already started, don't create another task;
  if (_isDrawing) return;
  _isDrawing = true;

  this->colorDepth = colorDepth;
  DriveContext *ctx = new DriveContext(this);
#ifdef SDL_h_
  drawTaskHandle = SDL_CreateThreadWithStackSize(drawLoop, "drawLoop", 2048, ctx);
  SDL_CreateThreadWithStackSize(facialLoop, "facialLoop", 1024, ctx);
#else
  // TODO(meganetaaan): keep handle of these tasks
  xTaskCreateUniversal(drawLoop,     /* Function to implement the task */
                          "drawLoop",   /* Name of the task */
                          2048,         /* Stack size in words */
                          ctx,          /* Task input parameter */
                          1,            /* Priority of the task */
                          &drawTaskHandle,        /* Task handle. */
                          APP_CPU_NUM);

  xTaskCreateUniversal(facialLoop,      /* Function to implement the task */
                          "facialLoop",    /* Name of the task */
                          1024,         /* Stack size in words */
                          ctx,          /* Task input parameter */
                          2,            /* Priority of the task */
                          NULL,         /* Task handle. */
                          APP_CPU_NUM);
#endif
}

void Avatar::draw() {
  Gaze g = Gaze(this->gazeV, this->gazeH);
  DrawContext *ctx = new DrawContext(this->expression, this->breath,
                                     &this->palette, g, this->eyeOpenRatio,
                                     this->mouthOpenRatio, this->speechText,
                                     this->rotation, this->scale, this->colorDepth, this->batteryIconStatus, this->batteryLevel, this->speechFont);
  face->draw(ctx);
  delete ctx;
}

bool Avatar::isDrawing() { return _isDrawing; }

void Avatar::setExpression(Expression expression) {
  suspend();
  this->expression = expression;
  resume();
}

Expression Avatar::getExpression() {
  return this->expression;
}

void Avatar::setBreath(float breath) { this->breath = breath; }

float Avatar::getBreath() {
  return this->breath;
}

void Avatar::setRotation(float radian) { this->rotation = radian; }

void Avatar::setScale(float scale) { this->scale = scale; }

void Avatar::setPosition(int top, int left) {
  this->getFace()->getBoundingRect()->setPosition(top, left);
}

void Avatar::setColorPalette(ColorPalette cp) { palette = cp; }

ColorPalette Avatar::getColorPalette(void) const { return this->palette; }

void Avatar::setMouthOpenRatio(float ratio) { this->mouthOpenRatio = ratio; }

void Avatar::setEyeOpenRatio(float ratio) { this->eyeOpenRatio = ratio; }

void Avatar::setGaze(float vertical, float horizontal) {
  this->gazeV = vertical;
  this->gazeH = horizontal;
}

void Avatar::getGaze(float *vertical, float *horizontal) {
  *vertical = this->gazeV;
  *horizontal = this->gazeH; 
}

void Avatar::setSpeechText(const char *speechText) {
  this->speechText = String(speechText);
}

void Avatar::setSpeechFont(const lgfx::IFont *speechFont) {
  this->speechFont = speechFont;
}

void Avatar::setBatteryIcon(bool batteryIcon) {
  if (!batteryIcon) {
    batteryIconStatus = BatteryIconStatus::invisible;
  } else {
    batteryIconStatus = BatteryIconStatus::unknown;
  }
}

void Avatar::setBatteryStatus(bool isCharging, int32_t batteryLevel) {
  if (this->batteryIconStatus != BatteryIconStatus::invisible) {
    if (isCharging) {
      this->batteryIconStatus = BatteryIconStatus::charging;
    } else {
      this->batteryIconStatus = BatteryIconStatus::discharging;  
    }
    this->batteryLevel = batteryLevel;
  }

}

}  // namespace m5avatar
