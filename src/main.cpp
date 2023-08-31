#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <TimeLib.h>
#define GFX_BL DF_GFX_BL
Arduino_DataBus *bus = new Arduino_ESP32SPI(2 /* DC */, 10 /* CS */, 6 /* SCK */, 7 /* MOSI */, GFX_NOT_DEFINED /* MISO */);
Arduino_GFX *output_display = new Arduino_GC9A01(bus, GFX_NOT_DEFINED /* RST */, 0 /* rotation */, true /* IPS */);
Arduino_GFX *gfx = new Arduino_Canvas_3bit(240 /* width */, 240 /* height */, output_display, 0 /* output_x */, 0 /* output_y */);

unsigned long last_millis = 0;
time_t muh = 0;

// static const tmElements_t Ende = { 
//   0, 
//   0, 
//   12, 
//   6,   // day of week, sunday is day 1
//   31,
//   7,
//   56, //2026 - 1970
// };

static const tmElements_t Ende = { 
  0, 
  0, 
  12, 
  6,   // day of week, sunday is day 1
  28,
  2,
  78, //2026 - 1970
};

static const tmElements_t Now = { 
  0, 
  30, 
  7, 
  5,   // day of week, sunday is day 1
  31,
  8,
  53,  //2023 - 1970
};

union Color
{
    struct Colors
    {
        uint16_t    red:5;
        uint16_t    green:6;
        uint16_t    blue:5;
    };
    uint16_t value;
};


void setup() {
  // put your setup code here, to run once:
  muh = makeTime(Now);
  setTime(muh);
  last_millis = millis();

  //gfx->fillScreen(BLACK);
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
  gfx->begin();
  gfx->fillScreen(BLACK);
  gfx->fillRoundRect(80,80,80,80,15,RED);
  delay(2000);
  gfx->setTextSize(3);  
}

void loop() {
  // put your main code here, to run repeatedly:
  setTime(muh + (millis()-last_millis) / 1000);
  time_t noch = elapsedDays(makeTime(Ende) - now());
  gfx->fillScreen(BLUE);
  gfx->setCursor(50, 60);
  gfx->printf("%02d:%02d:%02d\n\n     noch\n     %d\n     Tage\n", hour(), minute(), second(), noch);
  gfx->flush();
  delay(500);
}
