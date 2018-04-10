# API

## Live2DのAPIを参考にする

* 表情、感情
* 口、目の開き
  * eyeBlink: boolean
* 顔向き、視線
* 口、目の差し替え
* 物理演算
* setParamFloat("ANGLE_X")

setAutoMotion
  SUCCADE
    update(model, context)
    model.setParam
  LOOK_AROUND
  BLINK

setClock
start
stop
draw(immediate: boolean, clean: boolean)

setConfig
  EYE_R_X
  EYE_R_Y
  EYE_R_R
  EYE_L_X
  EYE_L_Y
  EYE_L_R
  MOUTH_X
  MOUTH_Y
  MOUTH_MIN_W
  MOUTH_MAX_W
  MOUTH_MIN_H
  MOUTH_MAX_H

setParam
  ANGLE_X(radian)
  ANGLE_Y(radian)
  ANGLE_Z(radian)
  GAZE_X(-1...1)
  GAZE_Y(-1...1)
  EYE_R_OPEN(0...1)
  EYE_L_OPEN(0...1)
  MOUTH_OPEN(0...1)
  BREATH(0...1)

setExpression
mouth, eye描画のcontext
  ANGRY
  SAD
  HAPPY

Avator
  目と口の位置を拾ってRendererに投げる
  autoMotion
  draw
  transformを保持