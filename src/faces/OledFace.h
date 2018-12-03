// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef FACES_OLEDFACE_H_
#define FACES_OLEDFACE_H_

#include <M5Stack.h>  // TODO(meganetaaan): include only the Sprite function not a whole library
#include "../BoundingRect.h"
#include "../DrawContext.h"
#include "../Drawable.h"

namespace m5avatar {
class OledFace : public Face {
 public:
  OledFace()
      : Face(new Mouth(), new BoundingRect(168, 163), new Eye(),
             new BoundingRect(103, 80), new Eye(),
             new BoundingRect(106, 240), new Eyeblow(15, 2, false),
             new BoundingRect(67, 96), new Eyeblow(15, 2, true),
             new BoundingRect(72, 230)) {}
};

}  // namespace m5avatar

#endif  // FACES_OLEDFACE_H_

