#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <TimeLib.h>
#define GFX_BL DF_GFX_BL
Arduino_DataBus *bus = new Arduino_ESP32SPI(2 /* DC */, 10 /* CS */, 6 /* SCK */, 7 /* MOSI */, GFX_NOT_DEFINED /* MISO */);
Arduino_GFX *gfx = new Arduino_GC9A01(bus, GFX_NOT_DEFINED /* RST */, 0 /* rotation */, true /* IPS */);

static const tmElements_t Ende = { 
  0, 
  0, 
  12, 
  6,   // day of week, sunday is day 1
  31,
  7,
  56, //2026 - 1970
};

static const tmElements_t Now = { 
  0, 
  5, 
  10, 
  4,   // day of week, sunday is day 1
  30,
  8,
  53,  //2023 - 1970
};

void setup() {
  // put your setup code here, to run once:
  setTime(makeTime(Now));
  time_t noch = elapsedDays(makeTime(Ende) - makeTime(Now));

  //gfx->fillScreen(BLACK);
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
  gfx->begin();
  gfx->fillScreen(BLACK);
  gfx->fillRoundRect(80,80,80,80,15,RED);
  delay(5000);
  gfx->fillScreen(BLUE);
  gfx->setTextSize(3);
  gfx->printf("\n\n\n     noch\n     %d\n     Tage\n", noch);  
}

void loop() {
  // put your main code here, to run repeatedly:
  gfx->invertDisplay(false);
  delay(5000);
  gfx->invertDisplay(true);
  delay(5000);
}
