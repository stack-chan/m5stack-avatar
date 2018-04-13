// Copyright (c) 2018 AQUEST
//	AquesTalk-ESP + I2S + internal-DAC

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/i2s.h>
#include <aquestalk.h>
#include "AquesTalkTTS.h"

#define LEN_FRAME 32
#define	TASK_PRIORITY		10
#define	SAMPLING_FREQ   24000	// 8KHz x 3
#define	DMA_BUF_COUNT 3
#define	DMA_BUF_LEN	(LEN_FRAME*3)	// one buffer size(one channnel samples)
#define DMA_BUF_SIZE (DMA_BUF_COUNT*DMA_BUF_LEN)
#define I2S_FIFO_LEN  (64/2)
#define	TICKS_TO_WAIT	(2*LEN_FRAME/8/portTICK_PERIOD_MS)

static uint32_t *workbuf = 0;
static TaskHandle_t taskAquesTalk=0;
static SemaphoreHandle_t muxAquesTalk=0;
static int level = 0;


static void task_TTS_synthe(void *arg);
static void DAC_create();
static void DAC_release();
static void DAC_start();
static void DAC_stop();
static int DAC_write(int len, int16_t *wav);
static int DAC_write_val(uint16_t val);

AquesTalkTTS	TTS;		// the only instance of AquesTalkTTS class

int AquesTalkTTS::create(const char *licencekey)
{
	int iret;
	
	// Initialize	AquesTalk-ESP
	if(!workbuf){
	  workbuf = (uint32_t*)malloc(AQ_SIZE_WORKBUF*sizeof(uint32_t));
	  if(workbuf==0) return 401;  // no heap memory
	}
  iret = CAqTkPicoF_Init(workbuf, LEN_FRAME, licencekey);
  if(iret)		return iret;	// AquesTalk Init error
  
  if(!muxAquesTalk)  muxAquesTalk = xSemaphoreCreateMutex();

  return 0;
}

void AquesTalkTTS::release()
{
	stop();
	if(taskAquesTalk)	vTaskDelete(taskAquesTalk);
  if(muxAquesTalk)	vSemaphoreDelete(muxAquesTalk);
  if(workbuf)	free(workbuf);
  workbuf = 0; taskAquesTalk = 0; muxAquesTalk = 0;
}

int AquesTalkTTS::play(const char *koe, int speed)
{
	int iret;
	if(!muxAquesTalk) return 402;	// not TTS_create

  xSemaphoreTake(muxAquesTalk, (portTickType)portMAX_DELAY);
  iret = CAqTkPicoF_SetKoe((const uint8_t*)koe, speed, 256);
	xSemaphoreGive(muxAquesTalk);
  if(iret)   return iret;

  if(taskAquesTalk==0){
     xTaskCreate(task_TTS_synthe, "task_TTS_synthe", 4096, NULL, TASK_PRIORITY, &taskAquesTalk);
  }
  else {
		vTaskResume(taskAquesTalk);
	}
  return 0;
}

int16_t gain(int16_t wav[])
{
  int32_t sum = 0;
  for(int i = 0; i < LEN_FRAME; i++) {
    sum += abs(wav[i]);
  }
  return sum / LEN_FRAME;
}

int AquesTalkTTS::getLevel()
{
	return level;
}

void AquesTalkTTS::stop()
{
	if(taskAquesTalk==0) return;	// not playing
	if(eTaskGetState(taskAquesTalk)==eSuspended) return;	// already suspended.
	
  xSemaphoreTake(muxAquesTalk, (portTickType)portMAX_DELAY);
  CAqTkPicoF_SetKoe((const uint8_t*)"#", 100, 256);	// generate error
	xSemaphoreGive(muxAquesTalk);
	// wait until the task suspend
	for(;;){
		if(eTaskGetState(taskAquesTalk)==eSuspended) break;
	}
}

void task_TTS_synthe(void *arg)
{
	for(;;){
	  DAC_create();
	  DAC_start();
		for(;;){
			int iret;
			uint16_t len;
			int16_t wav[LEN_FRAME];
			
	    xSemaphoreTake(muxAquesTalk, (portTickType)portMAX_DELAY);
			iret = CAqTkPicoF_SyntheFrame(wav, &len);
			xSemaphoreGive(muxAquesTalk);
			
			if(iret) break;	 // EOD or ERROR
			DAC_write((int)len, wav);

			level = gain(wav);
		}
		DAC_stop();
		DAC_release();
		level = 0;
		vTaskSuspend(NULL);	// suspend this task
	}
}

////////////////////////////////
//i2s configuration 
static const int i2s_num = 0; // i2s port number
static i2s_config_t i2s_config = {
     .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
     .sample_rate = SAMPLING_FREQ,
     .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
     .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
     .communication_format = (i2s_comm_format_t)I2S_COMM_FORMAT_I2S_MSB,
     .intr_alloc_flags = 0,
     .dma_buf_count = DMA_BUF_COUNT,
     .dma_buf_len = DMA_BUF_LEN,
     .use_apll = 0
};

static void DAC_create()
{

  i2s_driver_install((i2s_port_t)i2s_num, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)i2s_num, NULL);
  i2s_stop((i2s_port_t)i2s_num);  // Create時はstop状態
}

static void DAC_release()
{
  i2s_driver_uninstall((i2s_port_t)i2s_num); //stop & destroy i2s driver 
}

static void DAC_start()
{
	int k;
  i2s_start((i2s_port_t)i2s_num);
  
  for(k=0;k<DMA_BUF_LEN;k++){
		DAC_write_val(0);
	}
  for(k=0;k<=32768;k+=256) {
    DAC_write_val((uint16_t)k);
  }
	AqResample_Reset();
}

static void DAC_stop()
{
  int k;
  for(k=32768;k>=0;k-=256) {
    DAC_write_val((uint16_t)k);
  }
  for(k=0;k<DMA_BUF_SIZE+I2S_FIFO_LEN;k++){
		DAC_write_val(0);
	}
  i2s_stop((i2s_port_t)i2s_num);  
}

// upsampling & write to I2S
static int DAC_write(int len, int16_t *wav)
{
  int i;
  for(i=0;i<len;i++){
    // upsampling x3
    int16_t wav3[3];
    AqResample_Conv(wav[i], wav3);

    for(int k=0;k<3; k++){
			int iret = DAC_write_val(((uint16_t)wav3[k])^0x8000U);
      if(iret<0) return 404; // -1:parameter error
      if(iret==0) break;  //  0:TIMEOUT
    }
  }
  return i;
}

// write to I2S DMA buffer
static int DAC_write_val(uint16_t val)
{
	uint16_t sample[2];
  sample[0]=sample[1]=val; // mono -> stereo
  return i2s_push_sample((i2s_port_t)i2s_num, (const char *)sample, TICKS_TO_WAIT);
}