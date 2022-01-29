// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "Avatar.h"
namespace m5avatar {
const uint32_t DEFAULT_STACK_SIZE = 2048;

unsigned int seed = 0;

// TODO(meganetaaan): make read-only
DriveContext::DriveContext(Avatar *avatar) : avatar{avatar} {}

Avatar *DriveContext::getAvatar() { return avatar; }

void updateBreath(void *args) {
  int c = 0;
  DriveContext *ctx = reinterpret_cast<DriveContext *>(args);
  Avatar *avatar = ctx->getAvatar();
  while (avatar->isDrawing()) {
    c = c + 1 % 100;
    float f = sin(c * 2 * PI / 100.0);
    avatar->setBreath(f);
    vTaskDelay(33);
  }
  vTaskDelete(NULL);
}

void drawLoop(void *args) {
  DriveContext *ctx = reinterpret_cast<DriveContext *>(args);
  Avatar *avatar = ctx->getAvatar();
  while (avatar->isDrawing()) {
    if (avatar->isDrawing()) {
      avatar->draw();
    }
    vTaskDelay(10);
  }
  vTaskDelete(NULL);
}

void saccade(void *args) {
  DriveContext *ctx = reinterpret_cast<DriveContext *>(args);
  Avatar *avatar = ctx->getAvatar();
  while (avatar->isDrawing()) {
    float vertical = rand_r(&seed) / (RAND_MAX / 2.0) - 1;
    float horizontal = rand_r(&seed) / (RAND_MAX / 2.0) - 1;
    avatar->setGaze(vertical, horizontal);
    vTaskDelay(500 + 100 * random(20));
  }
  vTaskDelete(NULL);
}

void blink(void *args) {
  DriveContext *ctx = reinterpret_cast<DriveContext *>(args);
  Avatar *avatar = ctx->getAvatar();
  while (avatar->isDrawing()) {
    avatar->setEyeOpenRatio(1);
    vTaskDelay(2500 + 100 * random(20));
    avatar->setEyeOpenRatio(0);
    vTaskDelay(300 + 10 * random(20));
  }
  vTaskDelete(NULL);
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
      speechText{""} {}

void Avatar::setFace(Face *face) { this->face = face; }

Face *Avatar::getFace() const { return face; }

void Avatar::addTask(TaskFunction_t f, const char* name) {
  DriveContext *ctx = new DriveContext(this);
  // TODO(meganetaaan): set a task handler
  xTaskCreate(f, /* Function to implement the task */
                          name, /* Name of the task */
                          DEFAULT_STACK_SIZE, /* Stack size in words */
                          ctx,                /* Task input parameter */
                          1,                  /* P2014riority of the task */
                          NULL);              /* Task handle. */
  // xTaskCreatePinnedToCore(f, /* Function to implement the task */
  //                         name, /* Name of the task */
  //                         DEFAULT_STACK_SIZE, /* Stack size in words */
  //                         ctx,                /* Task input parameter */
  //                         1,                  /* P2014riority of the task */
  //                         NULL,               /* Task handle. */
  //                         1); /* Core where the task should run */
}

void Avatar::init() {
  // for compatibility with older version
  start();
}

void Avatar::stop() { _isDrawing = false; }

void Avatar::start() { 
  // if the task already started, don't create another task;
  if (_isDrawing) return;
  _isDrawing = true;

  DriveContext *ctx = new DriveContext(this);
  // TODO(meganetaaan): keep handle of these tasks
  xTaskCreate(drawLoop,     /* Function to implement the task */
                          "drawLoop",   /* Name of the task */
                          2048,         /* Stack size in words */
                          ctx,          /* Task input parameter */
                          1,            /* Priority of the task */
                          NULL);        /* Task handle. */
  xTaskCreate(saccade,      /* Function to implement the task */
                          "saccade",    /* Name of the task */
                          1024,         /* Stack size in words */
                          ctx,          /* Task input parameter */
                          2,            /* Priority of the task */
                          NULL);        /* Task handle. */
  xTaskCreate(updateBreath, /* Function to implement the task */
                          "breath",     /* Name of the task */
                          1024,         /* Stack size in words */
                          ctx,          /* Task input parameter */
                          2,            /* Priority of the task */
                          NULL);        /* Task handle. */
  xTaskCreate(blink,        /* Function to implement the task */
                          "blink",      /* Name of the task */
                          1024,         /* Stack size in words */
                          ctx,          /* Task input parameter */
                          2,            /* Priority of the task */
                          NULL);        /* Task handle. */
}

void Avatar::draw() {
  Gaze g = Gaze(this->gazeV, this->gazeH);
  DrawContext *ctx = new DrawContext(this->expression, this->breath,
                                     &this->palette, g, this->eyeOpenRatio,
                                     this->mouthOpenRatio, this->speechText,
                                     this->rotation, this->scale);
  face->draw(ctx);
  delete ctx;
}

bool Avatar::isDrawing() { return _isDrawing; }

void Avatar::setExpression(Expression expression) {
  this->expression = expression;
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
  this->speechText = speechText;
}

}  // namespace m5avatar
