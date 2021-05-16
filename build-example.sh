#!/bin/bash

if [ $# -lt 1 ]; then
  echo "usage: build-example.sh example-name [options]" 1>&2
  exit 1
fi
rm ./src/*.ino
cp ./examples/$1/$1.ino ./src/
shift
platformio run --target upload $@