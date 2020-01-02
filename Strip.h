
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
    _strip.setPixelColor(index, 255.0f * r, 255.0f * g, 255.0f * b);
  }
};
