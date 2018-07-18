#include <M5Stack.h>
#include <Avatar.h>

using namespace m5avatar;

Avatar avatar;
const char* lyrics[] = {"Hey,",     "diddle,",     "diddle,",        "The cat",
                         "and",      "the fiddle,", "The cow",        "jumped",
                         "over",     "the moon.",   "The little dog", "laughed",
                         "to",       "see",         "such sport,",    "And",
                         "the dish", "ran away",    "with the spoon."};
const int lyricsSize = sizeof(lyrics) / sizeof(char*);
int lyricsIdx = 0;

void setup()
{
  M5.begin();
  avatar.init();
}

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed())
  {
    const char* l = lyrics[lyricsIdx++ % lyricsSize];
    avatar.setSpeechText(l);
    avatar.setMouthOpenRatio(0.7);
    delay(200);
    avatar.setMouthOpenRatio(0);
  }
}
