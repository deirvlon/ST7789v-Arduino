# ST7789v-Arduino

I have faced many challenges to up on running display with the ST7789v driver. There is very poor information about this Driver on the Internet. The most information is about the ST7789 Driver. The main difference between ST7789 and ST7789v is the availability of DC pin. On ST7789v DC signal send as 9's bit of data in SPI communication, but DC is a physical pin on  ST7789. 

In this library i collected all the research that i have done about ST7789v driver.

### I have made  following example sketchs:
* **Graphic test sketch** (graphicsTEST.ino)
* **Load .bmp files directly from SD Card** (graphicsSDcrad.ino)
* **Load Image from MEMORY from .h** (graphicsIMG.ino)
* **Display control modes test** (graphicsControllerMods.ino)


### From my tests:
![Kamran Gasimov Smart Watch](https://i.ibb.co/TR8fWPp/kamran-gasimov-smart-watch.jpg)
![Deirvlon OS Mini - Demo](https://user-images.githubusercontent.com/50843190/79635070-b2ded880-817f-11ea-8efb-6513d3524a86.png)

### If you want to connect SD Card then Display pin configuration will be like
```
#define TFT_DC    8
#define TFT_RST   9
#define TFT_CS    10 // only for displays with CS pin
#define TFT_MOSI  7   // for hardware SPI data pin (all of available pins)
#define TFT_SCLK  8   // for hardware SPI sclk pin (all of available pins)
```

![GitHub Logo](https://www.mschoeffler.de/wp-content/uploads/2017/02/fritzing_bb.png)
