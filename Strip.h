
#include "Adafruit_WS2801.h"

class Strip {

  const uint8_t DATA_PIN = 2;
  const uint8_t CLOCK_PIN = 3;

  Adafruit_WS2801 _strip;

  public:
  
  const uint16_t LED_COUNT = 50;
  
  Strip() {
    _strip = Adafruit_WS2801(LED_COUNT, DATA_PIN, CLOCK_PIN);
    _strip.begin();
  }
  
  void refresh() {
    _strip.show();
  }

  void setRGB(int index, float r, float g, float b) {
    uint32_t color;

    color = (byte)(255.0f * r);
    color <<= 8;
    color |= (byte)(255.0f * g);
    color <<= 8;
    color |= (byte)(255.0f * b);
    
    _strip.setPixelColor(index, color);
  }
};
