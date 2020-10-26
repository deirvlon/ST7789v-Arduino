/***************************************************
  This is a library for the ST7789 IPS SPI display.

  Modified by Kamran Gasimov
 ****************************************************/

//#include <Adafruit_GFX.h>    // Core graphics library by Adafruit
#include <ST7789v_test.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <SPI.h>
#include "bitmap.h" //Deirvlon Logo bitmap

#define TFT_DC    8
#define TFT_RST   9 
#define TFT_CS    10 // only for displays with CS pin
#define TFT_MOSI  11   // for hardware SPI data pin (all of available pins)
#define TFT_SCLK  13   // for hardware SPI sclk pin (all of available pins)

//You can use different type of hardware initialization
//using hardware SPI (11, 13 on UNO; 51, 52 on MEGA; ICSP-4, ICSP-3 on DUE and etc)
//Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST); //for display without CS pin
//Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_CS); //for display with CS pin
//or you can use software SPI on all available pins (slow)
//Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK); //for display without CS pin
//Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_CS); //for display with CS pin
ST7789v_test tft = ST7789v_test(-1, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_CS); //for display with CS pin and DC via 9bit SPI


float p = 3.1415926;
uint16_t colorBar[50];
void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! ST7789 TFT Test");

  tft.init(240, 240);   // initialize a ST7789 chip, 240x240 pixels
  //
  tft.idleDisplay(false);
  Serial.println("Initialized");
  tft.fillScreen(BLACK); //Empty the screen

  //Draw Single Logo sprite
  tft.drawImageF(70, 70, 100, 100, logo);
}

void loop() {
  //Draw random Logo sprites around display
  tft.drawImageF(random(0, 240 - 100), random(0, 240 - 100), 100, 100, logo);
}
