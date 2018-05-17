// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#include "Avatar.h"
#include <AquesTalkTTS.h>
using namespace m5avatar;

class DriveContext
{
  private:
    Avatar *avatar;
    // Use wrapper class for voice engine
    AquesTalkTTS *TTS;
    bool _isDrawing;
  public:
    DriveContext(Avatar *avatar);
    ~DriveContext(){};
    Avatar* getAvatar();
    bool isDrawing();
};

class AvatarDriver
{
  private:
    DriveContext *ctx;
  public:
    AvatarDriver(Avatar *avatar);
    ~AvatarDriver();
    void run();
};