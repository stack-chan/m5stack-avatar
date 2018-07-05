// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef TASKS_LIPSYNC_H_
#define TASKS_LIPSYNC_H_

#include <AquesTalkTTS.h>
#include <M5Stack.h>
#include <Arduino.h>
#include "../Avatar.h"

namespace m5avatar {
extern void lipSync(void *args) {
  DriveContext *ctx = reinterpret_cast<DriveContext *> (args);
  Avatar *avatar = ctx->getAvatar();
  for (;;) {
    int level = TTS.getLevel();
    float f = level / 12000.0;
    float open = min(1.0, f);
    avatar->setMouthOpenRatio(open);
    delay(33);
  }
}
}  // namespace m5avatar

#endif  // SRC_TASKS_LIPSYNC_H_
