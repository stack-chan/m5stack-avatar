// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef GAZE_H_
#define GAZE_H_

namespace m5avatar {
class Gaze {
 private:
  float v;
  float h;

 public:
  Gaze();
  Gaze(float v, float h);
  ~Gaze() = default;
  Gaze(const Gaze &other) = default;
  Gaze &operator=(const Gaze &other) = default;
  float getVertical() const;
  float getHorizontal() const;
};
}  // namespace m5avatar

#endif  // GAZE_H_
