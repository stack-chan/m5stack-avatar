# 実行時に指定された引数の数、つまり変数 $# の値が 3 でなければエラー終了。
if [ $# -ne 1 ]; then
  echo "usage: build-example.sh example-name" 1>&2
  exit 1
fi
rm ./src/*.ino
cp ./examples/$1/$1.ino ./src/
platformio run --target upload