# M5Stack-Avatar

![M5Stack-Avatar](docs/image/avatar.gif)

Video: https://www.youtube.com/watch?v=C1Hj9kfY5qc

## Features

* :neutral_face: Draw avatar face
* :smile:        Expression(Happy, Angry, Sad etc.)
* :smiley_cat:   Customize face
* :kiss:         Lip sync
* :art:          Color Palette

## Usage

```cpp
void setup()
{
  M5.begin();
  Avatar *avatar = new Avatar();
  avatar->init(); // start drawing
}

void loop()
{
  // avatar's face updates in another thread
  // so no need to loop-by-loop rendering
}
```

see `examples` directory for further usage
