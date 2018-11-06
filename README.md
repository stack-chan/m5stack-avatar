# M5Stack-Avatar

[![Powered By PlatformIO](https://img.shields.io/Powered/PlatformIO.png)](https://platformio.org/)
[![Build Status](https://travis-ci.com/meganetaaan/m5stack-avatar.svg?branch=master)](https://travis-ci.com/meganetaaan/m5stack-avatar)

![M5Stack-Avatar](docs/image/avatar.gif)

Video: https://www.youtube.com/watch?v=C1Hj9kfY5qc

[日本語](README_ja.md)

## Features

* :neutral_face:     Draw avatar face
* :smile:            Expression(Happy, Angry, Sad etc.)
* :smiley_cat:       Customize face
* :kiss:             Lip sync
* :art:              Color Palette
* :arrows_clockwise: Move, Zoom and Rotation

## Installation

### Prerequisites

* USB Driver is installed throwgh [Getting Started: Installing the USB Driver](http://www.m5stack.com/assets/docs/)
* Any of IDE is set up
  * This library is confirmed on __Arduino IDE__ and __Platform IO__ for now

### Using Arduino IDE

* On Arduino IDE, Select "Sketch > Include Library > Manage Libraries..."
* Search "m5stack avatar"
* Select "M5Stack_Avatar" from the results then click "Install"
* The library gets installed

### Using Platform IO

* Initialize your Platform IO project
```sh
mkdir my-avatar
cd my-avatar
platformio init -d . -b m5stack-core-esp32
```
* Install the library and its dependency
```sh
platformio lib install M5Stack
platformio lib install M5Stack-Avatar
```
* The library gets downloaded from repository to .piolibdeps directory

## Usage

```cpp

#include <M5Stack.h>
#include <Avatar.h>

using namespace m5avatar;

Avatar avatar;

void setup()
{
  M5.begin();
  avatar.init(); // start drawing
}

void loop()
{
  // avatar's face updates in another thread
  // so no need to loop-by-loop rendering
}
```

### Using LipSync

* setup AquesTalk-ESP32 (http://blog-yama.a-quest.com/?eid=970195).
  * (For parsing Kainji statement) Copy the dictionary file from above link to the microSD card.
  * You don't need to copy AquesTalkTTS files. They are included in this library.

* Write below to open avatar mouth according to the audio output.

```cpp
#include <AquesTalkTTS.h>
#include <M5Stack.h>
#include <Avatar.h>
#include <tasks/LipSync.h>

using namespace m5avatar;

// AquesTalk License Key
// NULL or wrong value is just ignored
const char* AQUESTALK_KEY = "XXXX-XXXX-XXXX-XXXX";
Avatar avatar;

void setup() {
  int iret;
  M5.begin();
  // For Kanji-to-speech mode (requires dictionary file saved on microSD)
  // iret = TTS.createK(AQUESTALK_KEY);
  iret = TTS.create(AQUESTALK_KEY);
  avatar.init();
  avatar.addTask(lipSync, "lipSync");
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    // For Kanji-to-speech mode
    // TTS.play("こんにちは。", 80);
    TTS.play("konnichiwa", 80);
  }
}

```

### Further usage

see `examples` directory.
