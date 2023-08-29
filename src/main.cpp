#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#define GFX_BL DF_GFX_BL
Arduino_DataBus *bus = new Arduino_ESP32SPI(2 /* DC */, 10 /* CS */, 6 /* SCK */, 7 /* MOSI */, GFX_NOT_DEFINED /* MISO */);
Arduino_GFX *gfx = new Arduino_GC9A01(bus, GFX_NOT_DEFINED /* RST */, 0 /* rotation */, true /* IPS */);


void setup() {
  // put your setup code here, to run once:



  //gfx->fillScreen(BLACK);
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
  gfx->begin();
  gfx->fillScreen(BLACK);
  gfx->fillRoundRect(80,80,40,40,5,RED);
  delay(5000);
  gfx->fillScreen(BLUE);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  gfx->fillScreen(RED);
  delay(1000);
  gfx->fillScreen(GREEN);
}
