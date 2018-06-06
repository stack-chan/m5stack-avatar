// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5Stack.h>
#include "Face.h"

#define PRIMARY_COLOR WHITE
#define SECONDARY_COLOR BLACK

namespace m5avatar {

Face::Face()
: mouth {new Mouth(163, 148, 50, 90, 4, 60)},
  mouthPos {new BoundingRect(148, 163, 0, 0)},
  eyeR {new Eye(90, 93, 8, false)},
  eyeRPos {new BoundingRect(93, 90, 0, 0)},
  eyeL {new Eye(230, 96, 8, true)},
  eyeLPos {new BoundingRect(96, 230, 0, 0)},
  eyeblowR {new Eyeblow(90, 67, 32, 0, false)},
  eyeblowRPos {new BoundingRect(67, 96, 0, 0)},
  eyeblowL {new Eyeblow(230, 72, 32, 0, true)},
  eyeblowLPos {new BoundingRect(72, 230, 0, 0)},
  sprite {new TFT_eSprite(&M5.Lcd)},
  boundingRect {new BoundingRect(0, 0, 320, 240)}
{} 

Face::Face(MouthInterface* mouth, EyeInterface* eyeR, EyeInterface* eyeL, EyeblowInterface* eyeblowR, EyeblowInterface* eyeblowL)
: mouth {mouth},
  eyeR {eyeR},
  eyeL {eyeL},
  eyeblowR {eyeblowR},
  eyeblowL {eyeblowL},
  sprite {new TFT_eSprite(&M5.Lcd)},
  boundingRect {new BoundingRect(0, 0, 320, 240)}
{}

Face::Face(MouthInterface *mouth,
           BoundingRect *mouthPos,
           EyeInterface *eyeR,
           BoundingRect *eyeRPos,
           EyeInterface *eyeL,
           BoundingRect *eyeLPos,
           EyeblowInterface *eyeblowR,
           BoundingRect *eyeblowRPos,
           EyeblowInterface *eyeblowL,
           BoundingRect *eyeblowLPos)
    : mouth{mouth},
      mouthPos{mouthPos},
      eyeR{eyeR},
      eyeRPos{eyeRPos},
      eyeL{eyeL},
      eyeLPos{eyeLPos},
      eyeblowR{eyeblowR},
      eyeblowRPos{eyeblowRPos},
      eyeblowL{eyeblowL},
      eyeblowLPos{eyeblowLPos},
      sprite{new TFT_eSprite(&M5.Lcd)},
      boundingRect{new BoundingRect(0, 0, 320, 240)}
{}

Face::~Face()
{
  delete mouth;
  delete mouthPos;
  delete eyeR;
  delete eyeRPos;
  delete eyeL;
  delete eyeLPos;
  delete eyeblowR;
  delete eyeblowRPos;
  delete eyeblowL;
  delete eyeblowLPos;
  delete sprite;
  delete boundingRect;
}

void Face::setMouthOpen(float f)
{
  mouth->setOpenRatio(f);
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

MouthInterface *Face::getMouth()
{
  return mouth;
}

EyeInterface *Face::getLeftEye()
{
  return eyeL;
}

EyeInterface *Face::getRightEye()
{
  return eyeR;
}

BoundingRect *Face::getBoundingRect()
{
  return boundingRect;
}

/**
 *  @experimental
 */
void drawBalloon(TFT_eSPI *spi)
{
  spi->fillEllipse(280, 220, 60, 40, PRIMARY_COLOR);
  spi->fillTriangle(220, 180, 270, 210, 240, 210, PRIMARY_COLOR);
  spi->setTextSize(2);
  spi->setTextColor(SECONDARY_COLOR, PRIMARY_COLOR);
  spi->drawString("test", 240, 200, 2); // Continue printing from new x position
}

void Face::draw(DrawContext *ctx)
{
  sprite->setColorDepth(8);
  sprite->createSprite(320, 240);
  sprite->fillSprite(ctx->getColorPalette().get(COLOR_BACKGROUND));
  float breath = min(1.0f, ctx->getBreath());

  // copy context to each draw function
  mouth->draw(sprite, ctx);

  BoundingRect erp = *eyeRPos;
  erp.setPosition(erp.getTop() + breath * 3, erp.getLeft());
  eyeR->draw(sprite, erp, ctx);

  BoundingRect elp = *eyeLPos;
  elp.setPosition(elp.getTop() + breath * 3, elp.getLeft());
  eyeL->draw(sprite, elp, ctx);

  eyeblowR->draw(sprite, ctx);
  eyeblowL->draw(sprite, ctx);
  // drawAccessory(sprite, position, ctx);
  sprite->pushSprite(boundingRect->getLeft(), boundingRect->getTop());
  sprite->deleteSprite();
}

} // namespace m5avatar
