# M5Stack-Avatar

[![Build Status](https://travis-ci.com/meganetaaan/m5stack-avatar.svg?branch=master)](https://travis-ci.com/meganetaaan/m5stack-avatar)

![M5Stack-Avatar](docs/image/avatar.gif)

動画: https://www.youtube.com/watch?v=C1Hj9kfY5qc

[ENGLISH](README.md)

## 機能

* :neutral_face: アバターの顔を表示します。
* :smile:        表情を変えられます(喜び, 怒り, 悲しみ など)。
* :smiley_cat:   アバターの顔を独自にカスタマイズできます。
* :kiss:         リップシンク（音声に合わせて口を動かす）できます。
* :art:          色を変更できます。

## 使い方

```cpp

#include <Avatar.h>
Avatar avatar;

void setup()
{
  M5.begin();
  avatar.init(); // 描画を開始します。
}

void loop()
{
  // アバターの描画は別のスレッドで行われるので、
  // loopループの中で毎回描画をする必要はありません。
}
```

その他の使い方は `examples` ディレクトリを参照ください。
