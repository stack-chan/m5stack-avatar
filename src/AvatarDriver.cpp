// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// TODO make TTS not global
#include <AquesTalkTTS.h>
#include "Avatar.h"
#include "AvatarDriver.h"
using namespace m5avatar;

// TODO: make read-only
DriveContext::DriveContext(Avatar *avatar)
{
  this->avatar = avatar;
  this->_isDrawing = true;
}

Avatar* DriveContext::getAvatar()
{
  return avatar;
}

bool DriveContext::isDrawing()
{
  return _isDrawing;
}

void breath(void *args)
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
  for (;;)
  {
    int level = TTS.getLevel();
    float f = level / 12000.0;
    float open = min(1.0, last + f / 2.0);
    // count += 3;
    // float f0 = ((count % 360) / 180.0) * PI;
    // float open = (sin(f0) + 1.0) / 2.0;
    last = f;
    avatar->setMouthOpen(open);
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
    ctx->getAvatar()->setEyeOpen(1);
    delay(2500 + 100 * random(20));
    ctx->getAvatar()->setEyeOpen(0);
    delay(300 + 10 * random(20));
  }
}

AvatarDriver::AvatarDriver(Avatar *avatar)
{
  DriveContext *ctx = new DriveContext(avatar);
  this->ctx = ctx;
}

AvatarDriver::~AvatarDriver()
{
  // TODO: release tasks
}

void AvatarDriver::run()
{
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
      breath,   /* Function to implement the task */
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