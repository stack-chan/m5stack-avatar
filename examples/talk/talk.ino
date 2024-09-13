#include <Avatar.h>
#include <M5Unified.h>
#include <aquestalk.h>

using namespace m5avatar;
Avatar avatar;

// AquesTalk License Key
// NULL or wrong value is just ignored
const char* AQUESTALK_KEY = "XXXX-XXXX-XXXX-XXXX";
/// need AquesTalk library. ( URL : https://www.a-quest.com/ )
#include <aquestalk.h>

/// set M5Speaker virtual channel (0-7)
static constexpr uint8_t m5spk_virtual_channel = 0;

static constexpr uint8_t LEN_FRAME = 32;

static uint32_t workbuf[AQ_SIZE_WORKBUF];
static TaskHandle_t task_handle = nullptr;
volatile bool is_talking = false;

static void talk_task(void*)
{
  int16_t wav[3][LEN_FRAME];
  int tri_index = 0;
  for (;;)
  {
    ulTaskNotifyTake( pdTRUE, portMAX_DELAY ); // wait notify
    while (is_talking)
    {
      uint16_t len;
      if (CAqTkPicoF_SyntheFrame(wav[tri_index], &len)) { is_talking = false; break; }
      M5.Speaker.playRaw(wav[tri_index], len, 8000, false, 1, m5spk_virtual_channel, false);

      float ratio = (float)(abs(wav[tri_index][0]) / 12000.0f);
      if (ratio > 1.0f) {
        ratio = 1.0f;
      }
      avatar.setMouthOpenRatio(ratio);
      tri_index = tri_index < 2 ? tri_index + 1 : 0;
    }
  }
}

/// 音声再生の終了を待機する;
static void waitAquesTalk(void)
{
  while (is_talking) { vTaskDelay(1); }
}

/// 音声再生を停止する;
static void stopAquesTalk(void)
{
  if (is_talking) { is_talking = false; vTaskDelay(1); }
}

/// 音声再生を開始する。(再生中の場合は中断して新たな音声再生を開始する) ;
static void playAquesTalk(const char *koe)
{
  stopAquesTalk();

  //M5.Display.printf("Play:%s\n", koe);

  int iret = CAqTkPicoF_SetKoe((const uint8_t*)koe, 100, 0xFFu);
  if (iret) { Serial.println("ERR:CAqTkPicoF_SetKoe"); }

  is_talking = true;
  xTaskNotifyGive(task_handle);
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  // If you want to use kana-kanji, you should modify AquesTalkTTS.h/AquesTalkTTS.cpp. 
  M5.Lcd.setBrightness(30);
  M5.Lcd.clear();

  { /// custom setting
    auto spk_cfg = M5.Speaker.config();
    /// Increasing the sample_rate will improve the sound quality instead of increasing the CPU load.
    spk_cfg.sample_rate = 96000; // default:64000 (64kHz)  e.g. 48000 , 50000 , 80000 , 96000 , 100000 , 128000 , 144000 , 192000 , 200000
    M5.Speaker.config(spk_cfg);
  }
  M5.Speaker.begin();

  
  int iret = CAqTkPicoF_Init(workbuf, LEN_FRAME, AQUESTALK_KEY);
  if (iret) {
    M5.Display.println("ERR:CAqTkPicoF_Init");
  }
  avatar.init();
  xTaskCreateUniversal(talk_task, "talk_task", 4096, nullptr, 1, &task_handle, APP_CPU_NUM);

  playAquesTalk("akue_suto'-_ku/kido-shima'_shita.");
  waitAquesTalk();
  playAquesTalk("botanno/o_shitekudasa'i.");

}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    playAquesTalk("konnichiwa");
    avatar.setSpeechText("Hello");
    delay(1000);
    avatar.setSpeechText("");
  }
}
