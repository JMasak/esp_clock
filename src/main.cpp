#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <TimeLib.h>

#define LCD_WIDTH   240
#define LCD_HEIGHT  240
#define GFX_BL      DF_GFX_BL
Arduino_DataBus *bus = new Arduino_ESP32SPI(2 /* DC */, 10 /* CS */, 6 /* SCK */, 7 /* MOSI */, GFX_NOT_DEFINED /* MISO */);
Arduino_GFX *output_display = new Arduino_GC9A01(bus, GFX_NOT_DEFINED /* RST */, 0 /* rotation */, true /* IPS */);
Arduino_GFX *gfx = new Arduino_Canvas_3bit(LCD_WIDTH, LCD_HEIGHT, output_display, 0 /* output_x */, 0 /* output_y */);

unsigned long last_millis = 0;
time_t last_time = 0;

static const tmElements_t Ende = { 
  0, 
  0, 
  12, 
  6,   // day of week, sunday is day 1
  31,
  7,
  56, //2026 - 1970
};

// static const tmElements_t Ende = { 
//   0, 
//   0, 
//   12, 
//   6,   // day of week, sunday is day 1
//   28,
//   2,
//   78, //2026 - 1970
// };

static const tmElements_t Now = { 
  0, 
  26, 
  10, 
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
  last_time = makeTime(Now);
  setTime(last_time);
  last_millis = millis();

  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
  gfx->begin();
  gfx->fillScreen(BLACK);
  gfx->setTextSize(3);  
}

void loop() {
  // put your main code here, to run repeatedly:
  setTime(last_time + (millis()-last_millis) / 1000);
  time_t noch = elapsedDays(makeTime(Ende) - now());
  gfx->fillScreen(BLACK);
  double x = sin(PI / 30.0 * (minute() + second() / 60.0)) * LCD_WIDTH / 2.0 + LCD_WIDTH / 2.0;
  double y = (cos(PI / 30.0 * (minute() + second() / 60.0)) * LCD_HEIGHT / 2.0) * -1.0 + LCD_HEIGHT / 2.0;
  gfx->drawLine(LCD_WIDTH/2, LCD_HEIGHT/2, x, y, YELLOW);
  x = sin(PI / 6.0 * (hour() + minute() / 60.0)) * LCD_WIDTH / 3.0 + LCD_WIDTH / 2.0;
  y = (cos(PI / 6.0 * (hour()  + minute() / 60.0)) * LCD_HEIGHT / 3.0) * -1.0 + LCD_HEIGHT / 2.0;
  gfx->drawLine(LCD_WIDTH/2, LCD_HEIGHT/2, x, y, YELLOW);
  gfx->fillRoundRect(75, 99, 90, 42, 5, BLUE);
  gfx->setCursor(86, 109);
  gfx->printf("%d", noch);
  gfx->flush();
  delay(10000);
}
