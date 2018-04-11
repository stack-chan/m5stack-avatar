/*
 * This sample sketch is LCD ILI9341 display test of M5stack.
 * 
 * The MIT License (MIT)
 * Copyright (c) 2018 Mgo-tec. All rights reserved.
 * 
 * Modify Display.cpp of M5stack library.
 * M5stack library - MIT License
 * Copyright (c) 2017 M5Stack
 * 
 * https://opensource.org/licenses/mit-license.php
 */
#include <SPI.h>
#include "soc/spi_reg.h"
#include "FastLCD.h"
 
#define SPI_NUM 0x3 //VSPI=0x3, HSPI=0x2
 
const int _sck = 18; // SPI clock pin
const int _miso = -1; // MISO(master input slave output) don't using
const int _mosi = 23; // MOSI(master output slave input) pin
const int _cs = 14; // Chip Select pin
const int _dc = 27; // Data/Command pin
const int _rst = 33; // Reset pin
const uint8_t _LCD_LEDpin = 32;
 
//****** LCD ILI9341 ディスプレイ初期化 ***********
void ILI9341_Init(){
  Brightness(0);
 
  pinMode(_rst, OUTPUT); //Set RESET pin
  pinMode(_dc, OUTPUT); //Set Data/Command pin
 
  SPI.begin(_sck, _miso, _mosi, _cs); //VSPI setting
 
  SPI.setBitOrder(MSBFIRST);
  //ILI9341 のSPI Clock Cycle Time (Write) Minimun 100ns=10MHz
  //SPI.setFrequency(10000000);
  SPI.setFrequency(27000000);
  SPI.setDataMode(SPI_MODE0);
  SPI.setHwCs(true); //Set Hardware CS pin
 
  //Hardware Reset------------
  digitalWrite(_rst, HIGH);
  delay(5);
  digitalWrite(_rst, LOW);
  delay(10);
  digitalWrite(_rst, HIGH);
  delay(121);
 
  digitalWrite(_dc, HIGH);
 
  CommandWrite(0x38); //Idle mode OFF
  CommandWrite(0x3A); //COLMOD: Pixel Format Set
    DataWrite(0b01010101); //RGB 16 bits / pixel, MCU 16 bits / pixel
  CommandWrite(0x36); //MADCTL: Memory Access Control
    DataWrite(0b00001000); //D3: BGR(RGB-BGR Order control bit )="1"
  CommandWrite(0x11); //Sleep OUT
  delay(10);
 
  CommandWrite(0x29); //Display ON
 
  Display_Clear(0, 0, 319, 239);
  Brightness(100);
}
//********* 4wire SPI Data / Command write************
void CommandWrite(uint8_t b){
  digitalWrite(_dc, LOW);
  SPI.write(b);
  digitalWrite(_dc, HIGH);
}
 
void DataWrite(uint8_t b){
  SPI.write(b);
}
 
void DataWrite16(uint16_t b){
  SPI.write16(b);
}
 
void DataWrite32(uint32_t b){
  SPI.write32(b);
}
//******** Set Column and Page Address ( X Y range setting )***********
void XY_Range(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
  uint32_t X = (uint32_t)x0<<16 | x1;
  uint32_t Y = (uint32_t)y0<<16 | y1;
   
  CommandWrite( 0x2A ); //Set Column Address
    DataWrite32(X);
  CommandWrite( 0x2B ); //Set Page Address
    DataWrite32(Y);
}
//********* Display All Black Clear ******************************
void Display_Clear(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
  uint16_t Width_x = x1 - x0 + 1;
  uint16_t Width_y = y1 - y0 + 1;
  uint32_t Total = Width_x * Width_y ;
 
  Block_SPI_Fast_Write(x0, y0, x1, y1, 0, 0, 0, Total);
}
//*********** LCD ILE9341 Block Pixel SPI Fast Write *****************
void Block_SPI_Fast_Write(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t red, uint8_t green, uint8_t blue, uint32_t repeat){
  uint16_t ColorDot = (red << 11) | (green << 5) | blue;
  XY_Range(x0, y0, x1, y1);
  CommandWrite( 0x2C ); //LCD RAM write
  spiWriteBlock(ColorDot, repeat);
}
//*********** 65k Color Pixel (Dot) Write ****************************
void Draw_Pixel_65k_DotColor(uint16_t x0, uint16_t y0, uint16_t DotColor){
  XY_Range(x0, y0, x0, y0);
  CommandWrite( 0x2C ); //RAM write
  DataWrite16( DotColor );
}
//*********** 65k Pixel RGB color Write ****************************
void Draw_Pixel_65k_3Color(uint16_t x0, uint16_t y0, uint8_t red, uint8_t green, uint8_t blue){
  //red (0-31), green (0-63), blue (0-31)
  XY_Range(x0, y0, x0, y0);
 
  uint16_t Dot = ((uint16_t)red << 11) | ((uint16_t)green << 5) | (uint16_t)blue;
 
  CommandWrite( 0x2C ); //RAM write
  DataWrite16( Dot );
}
//***************************************
void Draw_Rectangle_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t red, uint8_t green, uint8_t blue){
  Draw_Horizontal_Line(x0, x1, y0, red, green, blue);
  Draw_Horizontal_Line(x0, x1, y1, red, green, blue);
  Draw_Vertical_Line(x0, y0, y1, red, green, blue);
  Draw_Vertical_Line(x1, y0, y1, red, green, blue);
}
//***************************************
void Draw_Horizontal_Line(int16_t x0, int16_t x1, int16_t y0, uint8_t red, uint8_t green, uint8_t blue){
  if(x0 > 319) x0 = 319;
  if(x1 > 319) x1 = 319;
  if(y0 > 239) y0 = 239;
  if(x1 < x0){
    uint16_t dummy = x1;
    x1 = x0;
    x0 = dummy;
  }
 
  uint32_t Width_x = x1 - x0 + 1;
  Block_SPI_Fast_Write(x0, y0, x1, y0, red, green, blue, Width_x);
}
//***************************************
void Draw_Vertical_Line(int16_t x0, int16_t y0, int16_t y1, uint8_t red, uint8_t green, uint8_t blue){
  if(x0 > 319) x0 = 319;
  if(y0 > 239) y0 = 239;
  if(y1 > 239) y1 = 239;
  if(y1 < y0){
    uint16_t dummy = y1;
    y1 = y0;
    y0 = dummy;
  }
 
  uint16_t Width_y = y1 - y0 + 1;
  Block_SPI_Fast_Write(x0, y0, x0, y1, red, green, blue, Width_y);
}
//***************************************
void Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t red, uint8_t green, uint8_t blue){
  if(x0 > 319) x0 = 319;
  if(x1 > 319) x1 = 319;
  if(y0 > 239) y0 = 239;
  if(y1 > 239) y1 = 239;
  if(x0 == x1 && y0 == y1) return;
 
  int i;
  int16_t X0 = x0, X1 = x1;
  int16_t Y0 = y0, Y1 = y1;
 
  int16_t Y = 0, X = 0;
  int16_t length_x = X1 - X0;
  int16_t length_y = Y1 - Y0;
 
  uint16_t Dot = (red << 11) | (green << 5) | blue;
 
  if(abs(length_x) > abs(length_y)){
    float degY = ((float)length_y) / ((float)length_x);
    if(X0<X1){
      for(i=X0; i<(X1+1); i++){
        Y = Y0 + round((i-X0) * degY);
        Draw_Pixel_65k_DotColor(i, Y, Dot);
      }
    }else{
      for(i=X0; i>=X1; i--){
        Y = Y0 + round((i-X0) * degY);
        Draw_Pixel_65k_DotColor(i, Y, Dot);
      }
    }
  }else{
    float degX = ((float)length_x) / ((float)length_y);
 
    if(Y0<Y1){
      for(i=Y0; i<(Y1+1); i++){
        X = X0 + round((i-Y0) * degX);
        Draw_Pixel_65k_DotColor(X, i, Dot);
      }
    }else{
      for(i=Y0; i>=Y1; i--){
        X = X0 + round((i-Y0) * degX);
        Draw_Pixel_65k_DotColor(X, i, Dot);
      }
    }
  }
}
//***************************************
void Draw_Rectangle_Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t red, uint8_t green, uint8_t blue){
  uint16_t Width_x = x1 - x0 + 1;
  uint16_t Width_y = y1 - y0 + 1;
  uint32_t Total = Width_x * Width_y ;
  Block_SPI_Fast_Write(x0, y0, x1, y1, red, green, blue, Total);
}
//***************************************
void Draw_Circle_Line(uint16_t x0, uint16_t y0, uint16_t r, uint8_t red, uint8_t green, uint8_t blue){
  uint16_t x1, y1;
  float i;
  float deg = 1.0;
  if( r > 50 ) deg = 0.5;
  if( r > 110) deg = 0.25;
 
  uint16_t Dot = ((uint16_t)red << 11) | ((uint16_t)green << 5) | (uint16_t)blue;
 
  for(i=0; i<360; i=i+deg){
    x1 = round( (float)(x0 + (r * cos(radians(i)))) );
    y1 = round( (float)(y0 + (r * sin(radians(i)))) );
    Draw_Pixel_65k_DotColor(x1, y1, Dot);
  }
}
//***************************************
void Draw_Circle_Fill(uint16_t x0, uint16_t y0, uint16_t r, uint8_t red, uint8_t green, uint8_t blue){
  //red (0-31), green (0-63), blue (0-31)
  uint16_t x1, y1;
  float i;
  float deg = 1.0;
  //半径が大きくなると、角度の刻み方を細かくしないと、完全に塗りつぶせないので注意。
  if( r > 50 ) deg = 0.5;
  if( r > 110) deg = 0.25;
 
  for( i = 0; i < 360; i = i + deg ){
    x1 = round( (float)(x0 + (r * cos(radians(i)))) );
    y1 = round( (float)(y0 + (r * sin(radians(i)))) );
    Draw_Vertical_Line(x1, y0, y1, red, green, blue);
  }
}
//********* LCD Display LED Brightness **************
void Brightness(uint8_t brightness){
  uint8_t ledc_ch = 0;
  uint32_t valueMax = 255;
  uint32_t duty = (8191 / valueMax) * min(brightness, valueMax);
  ledcSetup(ledc_ch, 5000, 13);
  ledcAttachPin(_LCD_LEDpin, 0);
  ledcWrite(ledc_ch, duty);
}
