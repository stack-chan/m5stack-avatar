# M5Stack-Avatar

[![Powered By PlatformIO](https://img.shields.io/Powered/PlatformIO.png)](https://platformio.org/)
[![Build Status](https://travis-ci.com/meganetaaan/m5stack-avatar.svg?branch=master)](https://travis-ci.com/meganetaaan/m5stack-avatar)

![M5Stack-Avatar](docs/image/avatar.gif)

動画: https://www.youtube.com/watch?v=C1Hj9kfY5qc

[ENGLISH](README.md)

## 機能

* :neutral_face:     アバターの顔を表示します。
* :smile:            表情を変えられます(喜び, 怒り, 悲しみ など)。
* :smiley_cat:       アバターの顔を独自にカスタマイズできます。
* :kiss:             リップシンク（音声に合わせて口を動かす）できます。
* :art:              色を変更できます。
* :arrows_clockwise: 顔を移動、拡大、回転できます。

## インストール

### 前提

* [Getting Started: Installing the USB Driver](http://www.m5stack.com/assets/docs/)にしたがって、USBドライバがインストールされている
* 何らかの開発環境がセットアップされている
  * このライブラリはArduino IDE, Platform IOで動作確認しています。

### Arduino IDEを使う場合

* Arduino IDEのメニューから"Sketch > Include Library > Manage Libraries..."を選択します
* 検索窓（"Filter your search..."）に"m5stack avatar" と入力します
* 検索結果から"M5Stack_Avatar"を選択し、"Install"ボタンをクリックします。
* M5Stack-Avatarライブラリがインストールされ、使用可能になります。

### Platform IOを使う場合

* cliからPlatform IOプロジェクトを初期化します。
```sh
mkdir my-avatar
cd my-avatar
platformio init -d . -b m5stack-core-esp32
```
* cliからライブラリをインストールします。
```sh
platformio lib install M5Stack
platformio lib install M5Stack-Avatar
```
* ライブラリがプロジェクトの.piolibdeps配下にダウンロードされ、使用可能になります。

## 使い方

```cpp

#include <M5Stack.h>
#include <Avatar.h>

using namespace m5avatar;

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

### リップシンク機能を使う場合

* AquesTalk-ESP32 をセットアップします（http://blog-yama.a-quest.com/?eid=970195）
  * （漢字かな混じり文から音声出力する場合）辞書データをあらかじめmicroSDカードにコピーしてください
  * 記事中にあるAquesTalkTTSのソースは本ライブラリに同梱されているため不要です

* 下記コード例のように記述すると、出力に合わせてアバターの口が動きます

```cpp
#include <AquesTalkTTS.h>
#include <M5Stack.h>
#include <Avatar.h>
#include <tasks/LipSync.h>

using namespace m5avatar;

// AquesTalk のライセンスキー
// NULLや誤った値を指定すると単に無視されます
const char* AQUESTALK_KEY = "XXXX-XXXX-XXXX-XXXX";
Avatar avatar;

void setup() {
  int iret;
  M5.begin();
  // 漢字かな混じり文から音声出力する場合(辞書ファイルが必要)
  // iret = TTS.createK(AQUESTALK_KEY);
  iret = TTS.create(AQUESTALK_KEY);
  avatar.init();
  avatar.addTask(lipSync, "lipSync");
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    // 漢字かな混じり文から音声出力する場合
    // TTS.play("こんにちは。", 80);
    TTS.play("konnichiwa", 80);
  }
}

```

### その他の使い方

`examples` ディレクトリを参照ください。
