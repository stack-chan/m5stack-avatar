// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Face.h"

#define PRIMARY_COLOR WHITE
#define SECONDARY_COLOR BLACK

namespace m5avatar {

Face::Face()
: mouth {new Mouth(163, 148, 50, 90, 4, 60)},
  mouthPos {new BoundingRect(148, 163)},
  eyeR {new Eye(8, false)},
  eyeRPos {new BoundingRect(93, 90)},
  eyeL {new Eye(8, true)},
  eyeLPos {new BoundingRect(96, 230)},
  eyeblowR {new Eyeblow(90, 67, 32, 0, false)},
  eyeblowRPos {new BoundingRect(67, 96)},
  eyeblowL {new Eyeblow(230, 72, 32, 0, true)},
  eyeblowLPos {new BoundingRect(72, 230)},
  sprite {new TFT_eSprite(&M5.Lcd)},
  boundingRect {new BoundingRect(0, 0, 320, 240)}
{} 

Face::Face(Drawable* mouth, Drawable* eyeR, Drawable* eyeL, EyeblowInterface* eyeblowR, EyeblowInterface* eyeblowL)
: mouth {mouth},
  eyeR {eyeR},
  eyeL {eyeL},
  eyeblowR {eyeblowR},
  eyeblowL {eyeblowL},
  sprite {new TFT_eSprite(&M5.Lcd)},
  boundingRect {new BoundingRect(0, 0, 320, 240)}
{}

Face::Face(Drawable *mouth,
           BoundingRect *mouthPos,
           Drawable *eyeR,
           BoundingRect *eyeRPos,
           Drawable *eyeL,
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

void Face::setMouth(Drawable *mouth)
{
  this->mouth = mouth;
}

void Face::setLeftEye(Drawable *eyeL)
{
  this->eyeL = eyeL;
}

void Face::setRightEye(Drawable *eyeR)
{
  this->eyeR = eyeR;
}

Drawable *Face::getMouth()
{
  return mouth;
}

Drawable *Face::getLeftEye()
{
  return eyeL;
}

Drawable *Face::getRightEye()
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

  BoundingRect rect = *mouthPos;
  rect.setPosition(rect.getTop() + breath * 3, rect.getLeft());
  // copy context to each draw function
  mouth->draw(sprite, rect, ctx);

  rect = *eyeRPos;
  rect.setPosition(rect.getTop() + breath * 3, rect.getLeft());
  eyeR->draw(sprite, rect, ctx);

  rect = *eyeLPos;
  rect.setPosition(rect.getTop() + breath * 3, rect.getLeft());
  eyeL->draw(sprite, rect, ctx);

  eyeblowR->draw(sprite, ctx);
  eyeblowL->draw(sprite, ctx);
  // drawAccessory(sprite, position, ctx);
  sprite->pushSprite(boundingRect->getLeft(), boundingRect->getTop());
  sprite->deleteSprite();
}

} // namespace m5avatar
