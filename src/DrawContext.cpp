// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "DrawContext.h"
namespace m5avatar {

// DrawContext
DrawContext::DrawContext(Expression expression, float breath,
                         ColorPalette* const palette, Gaze rightGaze,
                         float rightEyeOpenRatio, Gaze leftGaze,
                         float leftEyeOpenRatio, float mouthOpenRatio,
                         String speechText, BatteryIconStatus batteryIconStatus,
                         int32_t batteryLevel, const lgfx::IFont* speechFont)
    : DrawContext(expression, breath, palette, rightGaze, rightEyeOpenRatio,
                  leftGaze, leftEyeOpenRatio, mouthOpenRatio, speechText, 0, 1,
                  1, BatteryIconStatus::invisible, 0, speechFont){};

DrawContext::DrawContext(Expression expression, float breath,
                         ColorPalette* const palette, Gaze rightGaze,
                         float rightEyeOpenRatio, Gaze leftGaze,
                         float leftEyeOpenRatio, float mouthOpenRatio,
                         String speechText, float rotation, float scale,
                         int colorDepth, BatteryIconStatus batteryIconStatus,
                         int32_t batteryLevel, const lgfx::IFont* speechFont)
    : expression{expression},
      breath{breath},
      rightGaze{rightGaze},
      rightEyeOpenRatio{rightEyeOpenRatio},
      leftGaze{leftGaze},
      leftEyeOpenRatio{leftEyeOpenRatio},
      mouthOpenRatio{mouthOpenRatio},
      palette{palette},
      speechText{speechText},
      rotation{rotation},
      scale{scale},
      colorDepth{colorDepth},
      batteryIconStatus(batteryIconStatus),
      batteryLevel(batteryLevel),
      speechFont{speechFont} {}

Expression DrawContext::getExpression() const { return expression; }

float DrawContext::getMouthOpenRatio() const { return mouthOpenRatio; }

Gaze DrawContext::getLeftGaze() const { return leftGaze; }

float DrawContext::getLeftEyeOpenRatio() const { return leftEyeOpenRatio; }

Gaze DrawContext::getRightGaze() const { return rightGaze; }

float DrawContext::getRightEyeOpenRatio() const { return rightEyeOpenRatio; }

float DrawContext::getBreath() const { return breath; }

float DrawContext::getRotation() const { return rotation; }

float DrawContext::getScale() const { return scale; }

String DrawContext::getspeechText() const { return speechText; }

ColorPalette* const DrawContext::getColorPalette() const { return palette; }

int DrawContext::getColorDepth() const { return colorDepth; }

const lgfx::IFont* DrawContext::getSpeechFont() const { return speechFont; }

BatteryIconStatus DrawContext::getBatteryIconStatus() const {
  return batteryIconStatus;
}

int32_t DrawContext::getBatteryLevel() const { return batteryLevel; }

}  // namespace m5avatar
