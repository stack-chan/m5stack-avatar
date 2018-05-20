// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// TODO make TTS not global
#include <AquesTalkTTS.h>
#include "Avatar.h"
using namespace m5avatar;

// TODO: make read-only
DriveContext::DriveContext(Avatar *avatar)
{
  this->avatar = avatar;
}

Avatar* DriveContext::getAvatar()
{
  return avatar;
}

void updateBreath(void *args)
{
  int c = 0;
  DriveContext *ctx = (DriveContext *)args;
  for (;;)
  {
    c = c + 1 % 100;
    float f = sin(c * 2 * PI / 100.0);
    ctx->getAvatar()->setBreath(f);
    delay(33);
  }
}

void drawLoop(void *args)
{
  DriveContext *ctx = (DriveContext *)args;
  Avatar *avatar = ctx->getAvatar();
  float last = 0;
  int count = 0;
  for (;;)
  {
    // TODO define lipsync as another task
    int level = TTS.getLevel();
    float f = level / 12000.0;
    float open = min(1.0, f);
    // count += 3;
    // float f0 = ((count % 360) / 180.0) * PI;
    // float open = (sin(f0) + 1.0) / 2.0;
    avatar->getFace()->setMouthOpen(open);
    if (ctx->isDrawing())
    {
      avatar->draw();
    }
    delay(33);
  }
}

void saccade(void *args)
{
  DriveContext *ctx = (DriveContext *)args;
  for (;;)
  {
    float vertical = (float)rand() / (float)(RAND_MAX / 2) - 1;
    float horizontal = (float)rand() / (float)(RAND_MAX / 2) - 1;
    ctx->getAvatar()->setGaze(vertical, horizontal);
    delay(500 + 100 * random(20));
  }
}

void blink(void *args)
{
  DriveContext *ctx = (DriveContext *)args;
  for (;;)
  {
    ctx->getAvatar()->getFace()->setEyesOpen(1);
    delay(2500 + 100 * random(20));
    ctx->getAvatar()->getFace()->setEyesOpen(0);
    delay(300 + 10 * random(20));
  }
}

Avatar::Avatar()
{
  this->face = new Face();
  Avatar(*face);
}

Avatar::Avatar(Face *face)
{
  this->face = face;
  expression = Neutral;
  breath = 0.0;
}

Avatar::~Avatar()
{
  // TODO: release tasks
}

void Avatar::setFace(Face *face)
{
  this->face = face;
}

Face* Avatar::getFace()
{
  return face;
}

void Avatar::init()
{
  DriveContext *ctx = new DriveContext(this);
  // TODO: keep handle of these tasks
  xTaskCreatePinnedToCore(
      drawLoop,   /* Function to implement the task */
      "drawLoop", /* Name of the task */
      4096,       /* Stack size in words */
      ctx,       /* Task input parameter */
      1,          /* Priority of the task */
      NULL,       /* Task handle. */
      1);         /* Core where the task should run */
  xTaskCreatePinnedToCore(
      saccade,   /* Function to implement the task */
      "saccade", /* Name of the task */
      4096,      /* Stack size in words */
      ctx,      /* Task input parameter */
      3,         /* Priority of the task */
      NULL,      /* Task handle. */
      1);        /* Core where the task should run */
  xTaskCreatePinnedToCore(
      updateBreath,   /* Function to implement the task */
      "breath", /* Name of the task */
      4096,     /* Stack size in words */
      ctx,     /* Task input parameter */
      2,        /* Priority of the task */
      NULL,     /* Task handle. */
      1);       /* Core where the task should run */
  xTaskCreatePinnedToCore(
      blink,   /* Function to implement the task */
      "blink", /* Name of the task */
      4096,    /* Stack size in words */
      ctx,    /* Task input parameter */
      2,       /* Priority of the task */
      NULL,    /* Task handle. */
      1);      /* Core where the task should run */
}

void Avatar::stop()
{
  isDrawing = false;
}

void Avatar::start()
{
  isDrawing = true;
}

void Avatar::draw()
{
  DrawContext* ctx = new DrawContext(this->expression, this->breath);
  face->draw(ctx);
  delete ctx;
}

void Avatar::setExpression(Expression expression)
{
  this->expression = expression;
}

void Avatar::setBreath(float breath)
{
  this->breath = breath;
}

void Avatar::setGaze(float vertical, float horizontal)
{
  this->gazeV = vertical;
  this->gazeH = horizontal;
  int v = floor(4 * vertical);
  int h = floor(4 * horizontal);
  face->getLeftEye()->setOffset(v, h);
  face->getRightEye()->setOffset(v, h);
}
