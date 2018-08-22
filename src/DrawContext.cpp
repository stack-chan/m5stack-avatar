// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "DrawContext.h"
namespace m5avatar {

// DrawContext
DrawContext::DrawContext(Expression expression, float breath,
                         ColorPalette* const palette, Gaze gaze,
                         float eyeOpenRatio, float mouthOpenRatio,
                         const char* speechText)
    : DrawContext(expression, breath, palette, gaze, eyeOpenRatio, mouthOpenRatio, speechText, 0, 1){};

DrawContext::DrawContext(Expression expression, float breath,
                         ColorPalette* const palette, Gaze gaze,
                         float eyeOpenRatio, float mouthOpenRatio,
                         const char* speechText, float rotation, float scale)
    : expression{expression},
      breath{breath},
      eyeOpenRatio{eyeOpenRatio},
      mouthOpenRatio{mouthOpenRatio},
      gaze{gaze},
      palette{palette},
      speechText{speechText},
      rotation{rotation},
      scale{scale}{}

Expression DrawContext::getExpression() const { return expression; }

float DrawContext::getMouthOpenRatio() const { return mouthOpenRatio; }

float DrawContext::getEyeOpenRatio() const { return eyeOpenRatio; }

float DrawContext::getBreath() const { return breath; }

float DrawContext::getRotation() const { return rotation; }

float DrawContext::getScale() const { return scale; }

const char* DrawContext::getspeechText() const { return speechText; }

Gaze DrawContext::getGaze() const { return gaze; }

ColorPalette* const DrawContext::getColorPalette() const { return palette; }

}  // namespace m5avatar
