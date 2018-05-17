#include <M5Stack.h>
#include "avatar.h"
#include "const.h"
#include <AquesTalkTTS.h>

Avatar *avatar;
int count = 0;
float f = 0;
float last = 0;
double duration = 0;
double distance = 0;

void breath(void *args)
{
  int c = 0;
  for(;;)
  {
    c = c + 1 % 100;
    float f = sin(c * 2 * PI / 100.0);
    avatar->setBreath(f);
    delay(33);
  }
}
void drawLoop(void *args)
{
  for(;;)
  {
    int level = TTS.getLevel();
    float f = level / 12000.0;
    float open = min(1.0, last + f / 2.0);
    last = f;
    avatar->setMouthOpen(open);
    avatar->draw();
    delay(33);
  }
}

void saccade(void *args)
{
  for(;;)
  {
    float vertical = (float)rand()/(float)(RAND_MAX / 2) - 1;
    float horizontal = (float)rand()/(float)(RAND_MAX / 2) - 1;
    avatar->setGaze(vertical, horizontal);
    delay(500 + 100 * random(20));
  }
}

void blink(void *args)
{
  for(;;)
  {
    avatar->setEyeOpen(1);
    delay(2500 + 100 * random(20));
    avatar->setEyeOpen(0);
    delay(300 + 10 * random(20));
  }
}

#define echoPin 22
#define trigPin 21

void measureDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  if (duration > 0)
  {
    duration = duration / 2;
    distance = duration * 340 * 100 / 1000000;
    Serial.printf("Distance: %lf cm\n", distance);
  }
}

void setup()
{
  int iret;
  iret = TTS.create(AQUESTALK_KEY);
  M5.begin();
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  M5.Lcd.setBrightness(30);
  M5.Lcd.setTextSize(2);
  avatar = new Avatar();
  xTaskCreatePinnedToCore(
                    drawLoop,     /* Function to implement the task */
                    "drawLoop",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    1,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    1);        /* Core where the task should run */
  xTaskCreatePinnedToCore(
                    saccade,     /* Function to implement the task */
                    "saccade",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    3,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    1);        /* Core where the task should run */
  xTaskCreatePinnedToCore(
                    breath,     /* Function to implement the task */
                    "breath",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    2,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    1);        /* Core where the task should run */
  xTaskCreatePinnedToCore(
                    blink,     /* Function to implement the task */
                    "blink",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    2,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    1);        /* Core where the task should run */
}

void loop()
{
  M5.update();
  if (M5.BtnA.isPressed() || M5.BtnA.wasPressed())
  {
    // 200 -> 50
    // 10 -> 200
    measureDistance();
    int speed = max(50, 200 - distance);
    Serial.printf("Speed: %d", speed);
    M5.Lcd.fillRect(0, 209, 200, 30, BLACK);
    M5.Lcd.setCursor(0, 219);
    M5.Lcd.printf("%lf cm", distance);
    if (distance > 100)
    {
      TTS.play("to-i", speed);
    }
    else
    {
      TTS.play("chikai", speed);
    }
    delay(distance * 3);
  }
  delay(200);
}
