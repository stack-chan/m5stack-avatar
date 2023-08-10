// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "Face.h"

namespace m5avatar {
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
      sprite{new M5Canvas(&M5.Lcd)},
      tmpSprite{new M5Canvas(&M5.Lcd)} {}

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
  delete b;
  delete h;
  delete battery;
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
  } else {
    sprite->fillSprite(0);
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
  b->draw(sprite, br, ctx);
  h->draw(sprite, br, ctx);
  battery->draw(sprite, br, ctx);
  // drawAccessory(sprite, position, ctx);

  // TODO(meganetaaan): rethink responsibility for transform function
  float scale = ctx->getScale();
  float rotation = ctx->getRotation();

// ▼▼▼▼ここから▼▼▼▼
  static constexpr uint8_t y_step = 8;

  if (tmpSprite->getBuffer() == nullptr) {
    // 出力先と同じcolorDepthを指定することで、DMA転送が可能になる。
    // Display自体は16bit or 24bitしか指定できないが、細長なので1bitではなくても大丈夫。
    tmpSprite->setColorDepth(M5.Display.getColorDepth());

    // 確保するメモリは高さ8ピクセルの横長の細長い短冊状とする。
    tmpSprite->createSprite(boundingRect->getWidth(), y_step);
  }

  // 背景クリア用の色を設定
  tmpSprite->setBaseColor(ctx->getColorPalette()->get(COLOR_BACKGROUND));
  int y = 0;
  do {
    // 背景色で塗り潰し
    tmpSprite->clear();

    // 傾きとズームを反映してspriteからtmpSpriteに転写
    sprite->pushRotateZoom(tmpSprite, boundingRect->getWidth()>>1, (boundingRect->getHeight()>>1) - y, rotation, scale, scale);

    // tmpSpriteから画面に転写
    M5.Display.startWrite();

    // 事前にstartWriteしておくことで、pushSprite はDMA転送を開始するとすぐに処理を終えて戻ってくる。
    tmpSprite->pushSprite(&M5.Display, boundingRect->getLeft(), boundingRect->getTop() + y);

    // DMA転送中にdelay処理を設けることにより、DMA転送中に他のタスクへCPU処理時間を譲ることができる。
    delay(1);

    // endWriteによってDMA転送の終了を待つ。
    M5.Display.endWrite();

  } while ((y += y_step) < boundingRect->getHeight());

// 削除するのが良いかどうか要検討 (次回メモリ確保できない場合は描画できなくなるので、維持しておいても良いかも？)
// tmpSprite->deleteSprite();
// ▲▲▲▲ここまで▲▲▲▲

  sprite->deleteSprite();
}
}  // namespace m5avatar