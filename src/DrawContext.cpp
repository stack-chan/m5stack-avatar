// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "DrawContext.h"
namespace m5avatar {

// DrawContext
DrawContext::DrawContext(Expression expression, float breath,
                         ColorPalette* const palette, Gaze gaze,
                         float eyeOpenRatio, float mouthOpenRatio,
                         const char* speechText, BatteryIconStatus batteryIcon, int32_t batteryLevel, const lgfx::IFont* speechFont)
    : DrawContext(expression, breath, palette, gaze, eyeOpenRatio, mouthOpenRatio, speechText, 0, 1, 1, BatteryIconStatus::invisible, 0, speechFont){};

DrawContext::DrawContext(Expression expression, float breath,
                         ColorPalette* const palette, Gaze gaze,
                         float eyeOpenRatio, float mouthOpenRatio,
                         const char* speechText, float rotation, float scale, int colorDepth, BatteryIconStatus batteryIconStatus, int32_t batteryLevel, const lgfx::IFont* speechFont) 
    : expression{expression},
      breath{breath},
      eyeOpenRatio{eyeOpenRatio},
      mouthOpenRatio{mouthOpenRatio},
      gaze{gaze},
      palette{palette},
      speechText{speechText},
      rotation{rotation},
      scale{scale},
      colorDepth{colorDepth},
      batteryIconStatus(batteryIconStatus),
      batteryLevel(batteryLevel),
      speechFont{speechFont}{}

Expression DrawContext::getExpression() const { return expression; }

float DrawContext::getMouthOpenRatio() const { return mouthOpenRatio; }

float DrawContext::getEyeOpenRatio() const { return eyeOpenRatio; }

float DrawContext::getBreath() const { return breath; }

float DrawContext::getRotation() const { return rotation; }

float DrawContext::getScale() const { return scale; }

const char* DrawContext::getspeechText() const { return speechText; }

Gaze DrawContext::getGaze() const { return gaze; }

ColorPalette* const DrawContext::getColorPalette() const { return palette; }

int DrawContext::getColorDepth() const { return colorDepth; }

const lgfx::IFont* DrawContext::getSpeechFont() const { return speechFont; }

BatteryIconStatus DrawContext::getBatteryIconStatus() const { return batteryIconStatus; }

int32_t DrawContext::getBatteryLevel() const { return batteryLevel; }

}  // namespace m5avatar
