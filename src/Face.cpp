// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5Stack.h>
#include "Face.h"

#define PRIMARY_COLOR WHITE
#define SECONDARY_COLOR BLACK
using namespace m5avatar;

Face::Face()
{
  this->mouth = new Mouth(163, 148, 50, 90, 4, 60, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeR = new Eye(90, 93, 8, false, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeL = new Eye(230, 96, 8, true, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeblowR = new Eyeblow(90, 67, 32, 0, false, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeblowL = new Eyeblow(230, 72, 32, 0, true, PRIMARY_COLOR, SECONDARY_COLOR);
  this->sprite = new TFT_eSprite(&M5.Lcd);
}

void Face::setMouthOpen(float f)
{
  mouth->setOpenRatio(f);
}

void Face::setEyeOpen(float f)
{
  setEyesOpen(f);
}

void Face::setEyesOpen(float f)
{
  eyeR->setOpenRatio(f);
  eyeL->setOpenRatio(f);
}

void Face::setMouth(MouthInterface *mouth)
{
  this->mouth = mouth;
}

void Face::setLeftEye(EyeInterface *eyeL)
{
  this->eyeL = eyeL;
}

void Face::setRightEye(EyeInterface *eyeR)
{
  this->eyeR = eyeR;
}

MouthInterface* Face::getMouth()
{
  return mouth;
}

EyeInterface* Face::getLeftEye()
{
  return eyeL;
}

EyeInterface* Face::getRightEye()
{
  return eyeR;
}

/**
 *  @experimental
 */
void drawBalloon(TFT_eSPI *spi)
{
  spi->fillEllipse(280, 220, 60, 40, PRIMARY_COLOR);
  spi->fillTriangle(220, 180, 270, 210, 240, 210, PRIMARY_COLOR);
  // spi->setTextSize(2);
  // spi->setTextColor(SECONDARY_COLOR, PRIMARY_COLOR);
  // spi->setCursor(240, 200);
  // spi->printf("test");
}

void Face::draw(DrawContext *ctx)
{
  sprite->setColorDepth(1);
  sprite->setBitmapColor(PRIMARY_COLOR, SECONDARY_COLOR);
  sprite->createSprite(320, 240);
  sprite->fillSprite(SECONDARY_COLOR);
  // copy context to each draw function
  mouth->draw(sprite, ctx);
  eyeR->draw(sprite, ctx);
  eyeL->draw(sprite, ctx);
  eyeblowR->draw(sprite, ctx);
  eyeblowL->draw(sprite, ctx);
  sprite->pushSprite(0, 0);
  sprite->deleteSprite();
}
