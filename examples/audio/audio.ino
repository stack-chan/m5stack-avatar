#include <Arduino.h>
/* 
cd ~/Arduino/libraries
git clone https://github.com/earlephilhower/ESP8266Audio
Use the "Tools->ESP32 Sketch Data Upload" menu to write the MP3 to SPIFFS
Then upload the sketch normally.  
https://github.com/me-no-dev/arduino-esp32fs-plugin
*/

#include <HTTPClient.h>
#include <M5Unified.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include "AudioFileSourceSPIFFS.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputM5Speaker.hpp"
#include <Avatar.h>

using namespace m5avatar;

static constexpr uint8_t m5spk_virtual_channel = 0;

AudioGeneratorMP3 mp3;
AudioFileSourceSPIFFS file;
AudioFileSourceID3 *id3;
AudioOutputM5Speaker out(&M5.Speaker, m5spk_virtual_channel);

static fft_t fft;
static constexpr size_t WAVE_SIZE = 320;
static int16_t raw_data[WAVE_SIZE * 2];

#define LIPSYNC_LEVEL_MAX 10.0f
static float lipsync_level_max = LIPSYNC_LEVEL_MAX;
float mouth_ratio = 0.0f;

Avatar avatar;

void lipsync(void *args) {
  DriveContext * ctx = reinterpret_cast<DriveContext *>(args);
  Avatar *avatar = ctx->getAvatar();
  for(;;) {
     uint64_t level = 0;
    auto buf = out.getBuffer();
    if (buf) {
      memcpy(raw_data, buf, WAVE_SIZE * 2 * sizeof(int16_t));
      fft.exec(raw_data);
      // Specify the range of tones to be extracted by lipsync.(low))0〜63（high）
      for (size_t bx = 0; bx <= 63; ++bx) { 
        int32_t f = fft.get(bx);
        level += abs(f);
      }
    }

    mouth_ratio = (float)(level >> 16)/lipsync_level_max;
    if (mouth_ratio > 1.2f) {
      if (mouth_ratio > 1.5f) {
        lipsync_level_max += 10.0f; // If the lipsync limit is updated significantly, the limit will be increased.
      }
      mouth_ratio = 1.2f;
    }
    avatar->setMouthOpenRatio(mouth_ratio);
    vTaskDelay(1/portTICK_PERIOD_MS);
  }   
}

void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);
{
  auto spk_cfg = M5.Speaker.config();
  spk_cfg.sample_rate = 96000;
  spk_cfg.task_pinned_core = APP_CPU_NUM;
  // If the sound is choppy, change the following spk_cfg parameters.
  //spk_cfg.task_priority = 1;
  //spk_cfg.dma_buf_count = 8;
  //spk_cfg.dma_buf_len = 512;

  M5.Speaker.config(spk_cfg);
}
  M5.Speaker.begin();
  M5.Speaker.setVolume(128);

  WiFi.mode(WIFI_OFF); 
  SPIFFS.begin();
  delay(500);
  avatar.init();
  avatar.addTask(lipsync, "lipsync");
}

void playMusic(const char* filename) {
    file.open(filename);
    id3 = new AudioFileSourceID3(&file);
    id3->open(filename);
    mp3.begin(id3, &out);
}

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed()) {
    Serial.printf("Sample MP3 playback begins...\n");
    playMusic("/nyaan.mp3"); 
    static int lastms = 0;

    while (mp3.isRunning()) {
      if (millis()-lastms > 1000) {
        lastms = millis();
        Serial.printf("Running for %d ms...\n", lastms);
        Serial.flush();
      }
      if (!mp3.loop()) {
        Serial.printf("MP3 done\n");
        mp3.stop();
        delay(100);
        mp3.~AudioGeneratorMP3();
        id3->~AudioFileSourceID3();
        file.~AudioFileSourceSPIFFS();
        lipsync_level_max = LIPSYNC_LEVEL_MAX;
      }
    }
  }
}