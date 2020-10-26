/***************************************************
  This is a library for the ST7789 IPS SPI display.

  Modified by Kamran Gasimov
 ****************************************************/

//#include <Adafruit_GFX.h>    // Core graphics library by Adafruit
#include <ST7789v_arduino.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <SPI.h>
#include "bitmap.h"

#define TFT_DC    8
#define TFT_RST   9
#define TFT_CS    10 // only for displays with CS pin
#define TFT_MOSI  11   // for hardware SPI data pin (all of available pins)
#define TFT_SCLK  13   // for hardware SPI sclk pin (all of available pins)

//You can use different type of hardware initialization
//using hardware SPI (11, 13 on UNO; 51, 52 on MEGA; ICSP-4, ICSP-3 on DUE and etc)
//ST7789v_arduino tft = ST7789v_arduino(TFT_DC, TFT_RST); //for display without CS pin
//ST7789v_arduino tft = ST7789v_arduino(TFT_DC, TFT_RST, TFT_CS); //for display with CS pin
//or you can use software SPI on all available pins (slow)
//ST7789v_arduino tft = ST7789v_arduino(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK); //for display without CS pin
//ST7789v_arduino tft = ST7789v_arduino(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_CS); //for display with CS pin
ST7789v_arduino tft = ST7789v_arduino(-1, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_CS); //for display with CS pin and DC via 9bit SPI


float p = 3.1415926;
uint16_t colorBar[50];
void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! ST7789 TFT Test");

  tft.init(240, 240);   // initialize a ST7789 chip, 240x240 pixels
  //
  Serial.println("Initialized");
  tft.fillScreen(BLACK);


  for (int i = 0; i < 256; i += 16) {
    uint8_t r, g, b;
    tft.rgbWheel(i * 512L / 256, &r, &g, &b);
    tft.fillRect(0, i, 240, 16, RGBto565(r, g, b));
  }
}
int bgCols[] = {6, 8, 10, 12, 14, 12, 10, 8};
char *scrollTxt[] = {"", "This", "is", "an example", "of", "super-smooth", "scrolling", "with regular",
                     "AVR Arduino,", "ST7789", "240x240 IPS tft", "library", "and", "RRE Fonts", ""
                    };

int c = 0, t = 0;
int maxy = 320; // internal ST7789 fb is 240x320
unsigned long ms;

void loop() {

  tft.fillScreen(RGBto565(120, 60, 30));
  Serial.println( 95, "ST7789 modes");
  delay(2000);

  tft.powerSave(7);
  /*
    rainbow(); delay(2000);
    tft.setBrightness(0);    delay(2000);
    tft.setBrightness(128);  delay(2000);
    tft.setBrightness(255);  delay(2000);
  */
  rainbow();
  Serial.println( "Idle mode OFF");
  tft.idleDisplay(false); delay(2000);
  rainbow();
  Serial.println( "Idle mode ON");
  tft.idleDisplay(true); delay(4000);
  rainbow();
  Serial.println( "Idle mode OFF");
  tft.idleDisplay(false); delay(2000);

  rainbow();
  tft.fillRect(30, 87, 240 - 60, 60, BLACK);
  Serial.println( "Invert OFF");
  tft.invertDisplay(false); delay(2000);
  Serial.println( " Invert ON ");
  tft.invertDisplay(true); delay(4000);
  Serial.println( "Invert OFF");
  tft.invertDisplay(false); delay(2000);

  tft.fillScreen(RGBto565(180, 0, 180));
  Serial.println( "Sleep mode in 2s");
  delay(2000);
  //tft.enableDisplay(false);
  tft.sleepDisplay(true); delay(4000);
  tft.sleepDisplay(false);
  //tft.enableDisplay(true);

  tft.fillScreen(RGBto565(180, 0, 180));
  Serial.println( "Display on/off");
  delay(2000);
  tft.enableDisplay(false);  delay(4000);
  tft.enableDisplay(true);  delay(1000);

  tft.fillScreen(RGBto565(180, 0, 180));
  Serial.println( "Partial display");

  delay(2000);
  tft.setPartArea(60 * 1, 60 * 3); tft.partialDisplay(true); delay(4000);
  tft.setPartArea(60 * 3, 60 * 1); tft.partialDisplay(true); delay(4000);
  tft.partialDisplay(false);
  delay(1000);

  tft.fillScreen(RGBto565(180, 0, 0));
  Serial.println( "Sw reset ...");
  delay(2000);
  tft.resetDisplay();  delay(2000);
  //  tft.init(SCR_WD, SCR_HT);
  tft.fillScreen(RGBto565(0, 0, 180));
  Serial.println( "After reset"); delay(2000);
}

void rainbow()
{
  for (int i = 0; i < 240; i += 4) {
    uint8_t r, g, b;
    tft.rgbWheel(i * 512L / 240, &r, &g, &b);
    tft.fillRect(0, i, 240, 4, RGBto565(r, g, b));
  }
}

void testlines(uint16_t color) {
  tft.fillScreen(BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, 0, x, tft.height() - 1, color);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, 0, tft.width() - 1, y, color);
  }

  tft.fillScreen(BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(tft.width() - 1, 0, 0, y, color);
  }

  tft.fillScreen(BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, tft.height() - 1, x, 0, color);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
  }

  tft.fillScreen(BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(BLACK);
  for (int16_t y = 0; y < tft.height(); y += 5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x = 0; x < tft.width(); x += 5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(BLACK);
  for (int16_t x = tft.width() - 1; x > 6; x -= 6) {
    tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color1);
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = radius; x < tft.width(); x += radius * 2) {
    for (int16_t y = radius; y < tft.height(); y += radius * 2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = 0; x < tft.width() + radius; x += radius * 2) {
    for (int16_t y = 0; y < tft.height() + radius; y += radius * 2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width() / 2;
  int x = tft.height() - 1;
  int y = 0;
  int z = tft.width();
  for (t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects() {
  tft.fillScreen(BLACK);
  int color = 100;
  int i;
  int t;
  for (t = 0 ; t <= 4; t += 1) {
    int x = 0;
    int y = 0;
    int w = tft.width() - 2;
    int h = tft.height() - 2;
    for (i = 0 ; i <= 16; i += 1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, GREEN);
}
