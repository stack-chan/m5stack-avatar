#pragma mark - Depend ESP8266Audio and ESP8266_Spiram libraries
/* 
cd ~/Arduino/libraries
git clone https://github.com/earlephilhower/ESP8266Audio
git clone https://github.com/Gianbacchio/ESP8266_Spiram
Use the "Tools->ESP32 Sketch Data Upload" menu to write the MP3 to SPIFFS
Then upload the sketch normally.  
https://github.com/me-no-dev/arduino-esp32fs-plugin
*/

#include <HTTPClient.h>
#include <ESP8266Spiram.h>
#include <M5Stack.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include "AudioFileSourceSPIFFS.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include <Avatar.h>

using namespace m5avatar;

AudioGeneratorMP3 *mp3;
AudioFileSourceSPIFFS *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;

Avatar avatar;

int levels[10];
const int levelsSize = sizeof(levels) / sizeof(int);
int levelsIdx = 0;

int avgLevel() {
  int sum = 0;
  for (int i = 0; i < levelsSize; i++) {
    sum += levels[i];
  }
  return sum / levelsSize;
}

void setup()
{
  M5.begin();
  WiFi.mode(WIFI_OFF); 
  SPIFFS.begin();
  delay(500);
  avatar.init();
}

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed()) {
    Serial.printf("Sample MP3 playback begins...\n");
    file = new AudioFileSourceSPIFFS("/nyaan.mp3");
    id3 = new AudioFileSourceID3(file);
    out = new AudioOutputI2S(0, 1);  // Output to builtInDAC
    out->SetOutputModeMono(true);
    out->SetGain(0.16);
    mp3 = new AudioGeneratorMP3();
    mp3->begin(id3, out);
    while (mp3->isRunning()) {
      levels[levelIdx] = abs(out->getLevel());
      levelIdx = (levelIdx + 1) % levelsSize;
      float f = avgLevel() / 12000.0;
      avatar.setMouthOpenRatio(f);
      if (!mp3->loop()) mp3->stop();
    }
  }
}