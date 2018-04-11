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
#pragma once
#include <M5Stack.h>
#include <SPI.h>
#include "soc/spi_reg.h"
 
#define SPI_NUM 0x3 //VSPI=0x3, HSPI=0x2
 
//****** LCD ILI9341 ディスプレイ初期化 ***********
void ILI9341_Init();
//********* 4wire SPI Data / Command write************
void CommandWrite(uint8_t b);
void DataWrite(uint8_t b);
void DataWrite16(uint16_t b);
void DataWrite32(uint32_t b);
//******** Set Column and Page Address ( X Y range setting )***********
void XY_Range(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
//********* Display All Black Clear ******************************
void Display_Clear(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
//********* Display Color Pixel Block Fast Write *****************
void spiWriteBlock(uint16_t color, uint32_t repeat) ;
//*********** LCD ILE9341 Block Pixel SPI Fast Write *****************
void Block_SPI_Fast_Write(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t red, uint8_t green, uint8_t blue, uint32_t repeat);
//*********** 65k Color Pixel (Dot) Write ****************************
void Draw_Pixel_65k_DotColor(uint16_t x0, uint16_t y0, uint16_t DotColor);
//*********** 65k Pixel RGB color Write ****************************
void Draw_Pixel_65k_3Color(uint16_t x0, uint16_t y0, uint8_t red, uint8_t green, uint8_t blue);
//***************************************
void Draw_Rectangle_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t red, uint8_t green, uint8_t blue);
//***************************************
void Draw_Horizontal_Line(int16_t x0, int16_t x1, int16_t y0, uint8_t red, uint8_t green, uint8_t blue);
//***************************************
void Draw_Vertical_Line(int16_t x0, int16_t y0, int16_t y1, uint8_t red, uint8_t green, uint8_t blue);
//***************************************
void Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t red, uint8_t green, uint8_t blue);
//***************************************
void Draw_Rectangle_Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t red, uint8_t green, uint8_t blue);
//***************************************
void Draw_Circle_Line(uint16_t x0, uint16_t y0, uint16_t r, uint8_t red, uint8_t green, uint8_t blue);
//***************************************
void Draw_Circle_Fill(uint16_t x0, uint16_t y0, uint16_t r, uint8_t red, uint8_t green, uint8_t blue);
//********* LCD Display LED Brightness **************
void Brightness(uint8_t brightness);
