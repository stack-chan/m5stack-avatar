// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "Face.h"

namespace m5avatar {
Balloon b;
Effect h;
BoundingRect br;

Face::Face()
    : Face(new Mouth(50, 90, 4, 60), new BoundingRect(148, 163),
           new Eye(8, false), new BoundingRect(93, 90), new Eye(8, true),
           new BoundingRect(96, 230), new Eyeblow(32, 0, false),
           new BoundingRect(67, 96), new Eyeblow(32, 0, true),
           new BoundingRect(72, 230)) {}

Face::Face(Drawable *mouth, Drawable *eyeR, Drawable *eyeL, Drawable *eyeblowR,
           Drawable *eyeblowL)
    : Face(mouth, new BoundingRect(148, 163), eyeR, new BoundingRect(93, 90),
           eyeL, new BoundingRect(96, 230), eyeblowR, new BoundingRect(67, 96),
           eyeblowL, new BoundingRect(72, 230)) {}

Face::Face(Drawable *mouth, BoundingRect *mouthPos, Drawable *eyeR,
           BoundingRect *eyeRPos, Drawable *eyeL, BoundingRect *eyeLPos,
           Drawable *eyeblowR, BoundingRect *eyeblowRPos, Drawable *eyeblowL,
           BoundingRect *eyeblowLPos)
    : mouth{mouth},
      eyeR{eyeR},
      eyeL{eyeL},
      eyeblowR{eyeblowR},
      eyeblowL{eyeblowL},
      mouthPos{mouthPos},
      eyeRPos{eyeRPos},
      eyeLPos{eyeLPos},
      eyeblowRPos{eyeblowRPos},
      eyeblowLPos{eyeblowLPos},
      boundingRect{new BoundingRect(0, 0, 320, 240)},
      sprite{new M5Canvas(&M5.Lcd)} {}

Face::~Face() {
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

void Face::setMouth(Drawable *mouth) { this->mouth = mouth; }

void Face::setLeftEye(Drawable *eyeL) { this->eyeL = eyeL; }

void Face::setRightEye(Drawable *eyeR) { this->eyeR = eyeR; }

Drawable *Face::getMouth() { return mouth; }

Drawable *Face::getLeftEye() { return eyeL; }

Drawable *Face::getRightEye() { return eyeR; }

BoundingRect *Face::getBoundingRect() { return boundingRect; }

void Face::draw(DrawContext *ctx) {
  sprite->createSprite(boundingRect->getWidth(), boundingRect->getHeight());
  sprite->setColorDepth(ctx->getColorDepth());
  // NOTE: setting below for 1-bit color depth
  sprite->setBitmapColor(ctx->getColorPalette()->get(COLOR_PRIMARY),
    ctx->getColorPalette()->get(COLOR_BACKGROUND));
  if (ctx->getColorDepth() != 1) {
    sprite->fillSprite(ctx->getColorPalette()->get(COLOR_BACKGROUND));
  }
  float breath = _min(1.0f, ctx->getBreath());

  // TODO(meganetaaan): unify drawing process of each parts
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

  rect = *eyeblowRPos;
  rect.setPosition(rect.getTop() + breath * 3, rect.getLeft());
  eyeblowR->draw(sprite, rect, ctx);

  rect = *eyeblowLPos;
  rect.setPosition(rect.getTop() + breath * 3, rect.getLeft());
  eyeblowL->draw(sprite, rect, ctx);

  // TODO(meganetaaan): make balloons and effects selectable
  b.draw(sprite, br, ctx);
  h.draw(sprite, br, ctx);
  // drawAccessory(sprite, position, ctx);

  // TODO(meganetaaan): rethink responsibility for transform function
  float scale = ctx->getScale();
  float rotation = ctx->getRotation();

  if (scale != 1.0 || rotation != 0) {
    sprite->pushRotateZoom(rotation, scale, scale);
  } else {
    sprite->pushSprite(boundingRect->getLeft(), boundingRect->getTop());
  }
  sprite->deleteSprite();
}
}  // namespace m5avatar
