# M5Stack-Avatar

[![Powered By PlatformIO](https://img.shields.io/Powered/PlatformIO.png)](https://platformio.org/)
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

## インストール

### 前提

* [Getting Started: Installing the USB Driver](http://www.m5stack.com/assets/docs/)にしたがって、USBドライバがインストールされている
* 何らかの開発環境がセットアップされている
  * このライブラリはArduino IDE, Platform IOで動作確認しています。

### Arduino IDEを使う場合

* [ダウンロードリンク](https://github.com/meganetaaan/m5stack-avatar/archive/master.zip)からM5Stack-AvatarのZIPをダウンロードします
* Arduino IDEのメニューから"Sketch > Include Library > Add ZIP Library..."を選択します
* ダウンロードしたZIPを指定します
* M5Stack-Avatarライブラリが登録され、使用可能になります。

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

その他の使い方は `examples` ディレクトリを参照ください。
