// AquesTalkTTS - AquesTalk ESP32のラッパークラス
//	AquesTalk-ESP32 + I2S + internal-DAC
// Copyright (c) 2018 AQUEST (本ソースコードは改変自由)
/*
        * 本ソースは、M5Staclkのハードウェア用に記述されています。
          お使いのハードウェア環境に応じて変更してください。

        *
   DAC_XXX()関数は、D/A部分の関数です。このソースはI2S経由で内蔵DACから音声を出力するものです。
        *
   I2S-内蔵DACの場合、符号無しのデータを与える必要があるため、DAC_write()で変換しています。
          外付けのI2S-DACを使う場合は注意してください。

        * aqdic_open()/aqdic_close()/aqdic_read()関数は
   辞書データ(aqdic_m.bin)にアクセスする関数で、
          libaquestalk.aから呼び出されます。このソースはM5StackのSDにファイルとして辞書データが配置
          されている場合のコードです。

        *
   ワークバッファをヒープ上に確保しています。create()は400B、createK()は20.4KBを使います。
*/

#include "AquesTalkTTS.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <aquestalk.h>
#include <driver/i2s.h>

#define LEN_FRAME 32
#define TASK_PRIORITY 10
#define SAMPLING_FREQ 24000  // 8KHz x 3
#define DMA_BUF_COUNT 3
#define DMA_BUF_LEN (LEN_FRAME * 3)  // one buffer size(one channnel samples)
#define DMA_BUF_SIZE (DMA_BUF_COUNT * DMA_BUF_LEN)
#define I2S_FIFO_LEN (64 / 2)
#define TICKS_TO_WAIT (2 * LEN_FRAME / 8 / portTICK_PERIOD_MS)
#define N_BUF_ROMAN 1024

static uint32_t *workbuf = 0;  // work buffer for AquesTalk pico
static uint8_t *workbufK = 0;  // work buffer for AqKanji2Roman
static TaskHandle_t taskAquesTalk = 0;
static SemaphoreHandle_t muxAquesTalk = 0;
static int level = 0;

static void task_TTS_synthe(void *arg);
static void DAC_create();
static void DAC_release();
static void DAC_start();
static void DAC_stop();
static int DAC_write(int len, int16_t *wav);
static int DAC_write_val(uint16_t val);

AquesTalkTTS TTS;  // the only instance of AquesTalkTTS class

// 音声記号からの音声合成のみの場合の初期化
int AquesTalkTTS::create(const char *licencekey) {
  int iret;

  // Initialize	AquesTalk-ESP
  if (!workbuf) {
    workbuf = (uint32_t *)malloc(AQ_SIZE_WORKBUF * sizeof(uint32_t));
    if (workbuf == 0) return 401;  // no heap memory
  }
  iret = CAqTkPicoF_Init(workbuf, LEN_FRAME, licencekey);
  if (iret) return iret;  // AquesTalk Init error

  if (!muxAquesTalk) muxAquesTalk = xSemaphoreCreateMutex();

  return 0;
}

// 漢字仮名混じり文からの音声合成の場合の初期化
int AquesTalkTTS::createK(const char *licencekey) {
  int iret;

  if (!workbufK) {
    workbufK = (uint8_t *)malloc(SIZE_AQK2R_MIN_WORK_BUF);
    if (workbufK == 0) return 401;  // no heap memory
  }
  iret = CAqK2R_Create(workbufK, SIZE_AQK2R_MIN_WORK_BUF);
  if (iret) {
    free(workbufK);
    workbufK = 0;
    return iret;  // AqKanji2Roman Init error
  }

  return create(licencekey);
}

void AquesTalkTTS::release() {
  stop();
  if (taskAquesTalk) vTaskDelete(taskAquesTalk);
  if (muxAquesTalk) vSemaphoreDelete(muxAquesTalk);
  if (workbuf) free(workbuf);
  if (workbufK) {
    CAqK2R_Release();
    free(workbufK);
  }
  workbuf = 0;
  workbufK = 0;
  taskAquesTalk = 0;
  muxAquesTalk = 0;
}

int AquesTalkTTS::play(const char *koe, int speed) {
  int iret;
  if (!muxAquesTalk) return 402;  // not initialized. use TTS.create()

  xSemaphoreTake(muxAquesTalk, (portTickType)portMAX_DELAY);
  iret = CAqTkPicoF_SetKoe((const uint8_t *)koe, speed, 256);
  xSemaphoreGive(muxAquesTalk);
  if (iret) return iret;

  if (taskAquesTalk == 0) {
    xTaskCreate(task_TTS_synthe, "task_TTS_synthe", 4096, NULL, TASK_PRIORITY,
                &taskAquesTalk);
  } else {
    vTaskResume(taskAquesTalk);
  }
  return 0;
}

int AquesTalkTTS::playK(const char *kanji, int speed) {
  int iret;
  if (workbufK == 0)
    return 403;  // not initialized ( use TTS.createK() before. )
  if (!muxAquesTalk) return 402;  // not initialized use TTS.create()

  char roman[N_BUF_ROMAN];
  iret = CAqK2R_Convert(kanji, roman, N_BUF_ROMAN);
  if (iret == 0) {
    xSemaphoreTake(muxAquesTalk, (portTickType)portMAX_DELAY);
    iret = CAqTkPicoF_SetKoe((const uint8_t *)roman, speed, 256);
    xSemaphoreGive(muxAquesTalk);
  } else {
    iret += 1000;
  }
  if (iret) return iret;

  if (taskAquesTalk == 0) {
    xTaskCreate(task_TTS_synthe, "task_TTS_synthe", 4096, NULL, TASK_PRIORITY,
                &taskAquesTalk);
  } else {
    vTaskResume(taskAquesTalk);
  }
  return 0;
}

void AquesTalkTTS::stop() {
  if (taskAquesTalk == 0) return;                          // not playing
  if (eTaskGetState(taskAquesTalk) == eSuspended) return;  // already suspended.

  xSemaphoreTake(muxAquesTalk, (portTickType)portMAX_DELAY);
  CAqTkPicoF_SetKoe((const uint8_t *)"#", 100, 256);  // generate error
  xSemaphoreGive(muxAquesTalk);
  // wait until the task suspend
  for (;;) {
    if (eTaskGetState(taskAquesTalk) == eSuspended) break;
  }
}

bool AquesTalkTTS::isPlay() {
  if (taskAquesTalk == 0) return false;  // not playing
  if (eTaskGetState(taskAquesTalk) == eSuspended)
    return false;  // already suspended.
  return true;
}

int AquesTalkTTS::getLevel() { return level; }

void task_TTS_synthe(void *arg) {
  for (;;) {
    DAC_create();
    DAC_start();
    for (;;) {
      int iret;
      uint16_t len;
      int16_t wav[LEN_FRAME];

      xSemaphoreTake(muxAquesTalk, (portTickType)portMAX_DELAY);
      iret = CAqTkPicoF_SyntheFrame(wav, &len);
      xSemaphoreGive(muxAquesTalk);

      if (iret) break;  // EOD or ERROR
      DAC_write((int)len, wav);

      {  // calc gain for Avatar(lip-sync);
        int32_t sum = 0;
        for (int i = 0; i < LEN_FRAME; i++) {
          sum += abs(wav[i]);
        }
        level = sum / LEN_FRAME;
      }
    }
    DAC_stop();
    DAC_release();
    level = 0;
    vTaskSuspend(NULL);  // suspend this task
  }
}

////////////////////////////////
// I2S DAC
////////////////////////////////

// i2s configuration
static const int i2s_num = 0;  // i2s port number
static i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
    .sample_rate = SAMPLING_FREQ,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = 0,
    .dma_buf_count = DMA_BUF_COUNT,
    .dma_buf_len = DMA_BUF_LEN,
    .use_apll = 0};

static void DAC_create() {
  i2s_driver_install((i2s_port_t)i2s_num, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)i2s_num, NULL);
  i2s_stop((i2s_port_t)i2s_num);  // Create時はstop状態
}

static void DAC_release() {
  i2s_driver_uninstall((i2s_port_t)i2s_num);  // stop & destroy i2s driver
}

static void DAC_start() {
  int k;
  i2s_start((i2s_port_t)i2s_num);

  for (k = 0; k < DMA_BUF_LEN; k++) {
    DAC_write_val(0);
  }
  for (k = 0; k <= 32768; k += 256) {
    DAC_write_val((uint16_t)k);
  }
  AqResample_Reset();
}

static void DAC_stop() {
  int k;
  for (k = 32768; k >= 0; k -= 256) {
    DAC_write_val((uint16_t)k);
  }
  for (k = 0; k < DMA_BUF_SIZE + I2S_FIFO_LEN; k++) {
    DAC_write_val(0);
  }
  i2s_stop((i2s_port_t)i2s_num);
}

// upsampling & write to I2S
static int DAC_write(int len, int16_t *wav) {
  int i;
  for (i = 0; i < len; i++) {
    // upsampling x3
    int16_t wav3[3];
    AqResample_Conv(wav[i], wav3);

    for (int k = 0; k < 3; k++) {
      int iret =
          DAC_write_val(((uint16_t)wav3[k]) ^
                        0x8000U);  // for Internal-DAC (signed -> unsigned data)
      //		int iret = DAC_write_val((uint16_t)wav3[k]);// for
      //External SPI-DAC
      if (iret < 0) return 404;  // -1:parameter error
      if (iret == 0) break;      //	0:TIMEOUT
    }
  }
  return i;
}

// write to I2S DMA buffer
static int DAC_write_val(uint16_t val) {
  uint16_t sample[2];
  sample[0] = sample[1] = val;  // mono -> stereo
  size_t bytes_written;
  esp_err_t iret = i2s_write((i2s_port_t)i2s_num, sample, sizeof(uint16_t) * 2,
                             &bytes_written, TICKS_TO_WAIT);
  if (iret != ESP_OK) return -1;
  if (bytes_written < sizeof(uint16_t) * 2) return 0;  // timeout
  return 1;
}

/*****************************************************************************

        辞書データ(aqdic_m.bin)のアクセス関数

        ここで定義する関数は、AquesTalk ESP32ライブラリから呼び出されます。
        辞書データを読み込む機能を、使用するハードウェア構成に応じて実装します。

        漢字仮名混じり文からの音声合成を行う場合に記述が必須で、
        さもなければリンク時にエラーとなります。
        音声記号列からの音声合成だけを使用する場合はこれら関数の記述は不要です。

        辞書データの配置場所は以下などが考えられます。
        ・SDカード上のファイル
        ・SPIシリアルフラッシュメモリ
        ・メモリマップドされたシリアルフラッシュ
        ・マイコン内蔵フラッシュメモリ

        辞書データは大量かつランダムにアクセスされるので、
        この関数の処理量が音声合成のパフォーマンスに与える影響は大きいです。

******************************************************************************/

/*---------------------------------------------------------------------
        以下のコードはM5StackのSDカードに辞書データファイルを書き込んで使用する場合。
        メインプログラムでM5.begin()を呼び出してSD.begin()しておくことを忘れずに
------------------------------------------------------------------------*/
#include <SD.h>  // ArduinoIDE

// SDのaq_dicフォルダの下に辞書データファイル(aqdic_m.bin)を配置
#define FILE_DIC "/aq_dic/aqdic_m.bin"

// 仮想的な辞書データの先頭アドレス
// （NULL以外なら任意で良い。但し4byteアライメント）
#define ADDR_ORG (0x10001000)

static File fp;

//-----------------------------------------------------------------
// 辞書データアクセスの初期化
// CAqK2R_Create()内から一度だけ呼び出される
// 戻り値
//    仮想的な辞書データの先頭アドレスを返す（0以外。4byteアライメント)。
//    エラーのときは0を返す
extern "C" size_t aqdic_open() {
  fp = SD.open(FILE_DIC);
  if (!fp) return 0;  // err
  return ADDR_ORG;    // ok
}

//-----------------------------------------------------------------
// 辞書データアクセスの終了
// CAqK2R_Release()内から一度だけ呼び出される
extern "C" void aqdic_close() {
  if (fp) fp.close();
}

//-----------------------------------------------------------------
// 辞書データの読み込み
// pos: 先頭アドレス[byte]
// size: 読み込むサイズ[byte]
// buf:  読み込むデータ配列 uint8_t(size)
// 戻り値：	読みこんだバイト数
// CAqK2R_Convert()/CAqK2R_ConvertW()から複数回呼び出される
extern "C" size_t aqdic_read(size_t pos, size_t size, void *buf) {
  fp.seek(pos - ADDR_ORG);
  return fp.read((uint8_t *)buf, size);
}
