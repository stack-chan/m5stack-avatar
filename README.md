# M5Stack-Avatar

[![Powered By PlatformIO](https://img.shields.io/Powered/PlatformIO.png)](https://platformio.org/)
[![Build Status](https://travis-ci.com/meganetaaan/m5stack-avatar.svg?branch=master)](https://travis-ci.com/meganetaaan/m5stack-avatar)

![M5Stack-Avatar](docs/image/avatar.gif)

Video: https://www.youtube.com/watch?v=C1Hj9kfY5qc

[日本語](README_ja.md)

## Features

* :neutral_face: Draw avatar face
* :smile:        Expression(Happy, Angry, Sad etc.)
* :smiley_cat:   Customize face
* :kiss:         Lip sync
* :art:          Color Palette

## Installation

### Prerequisites

* USB Driver is installed throwgh [Getting Started: Installing the USB Driver](http://www.m5stack.com/assets/docs/)
* Any of IDE is set up
  * This library is confirmed on __Arduino IDE__ and __Platform IO__ for now

### Using Arduino IDE

* Download [M5Stack-Avatar ZIP](https://github.com/meganetaaan/m5stack-avatar/archive/master.zip)
* On Arduino IDE, Select "Sketch > Include Library > Add ZIP Library..."
* Choose the ZIP
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

see `examples` directory for further usage
