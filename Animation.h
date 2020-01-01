#include "Strip.h"

class Animation {

  Strip _strip;

  int _index;
  
  float _lastIncrement;
  
  public:
  
  Animation() {
    _index = 0;
  }

  void update(float time, float deltaTime) {
    if (time - _lastIncrement > 0.2f) {
      increment();
      _lastIncrement = time;
    }
  }

  private:

  void increment() {
    float r = _index % 3 == 0 ? 1.0f : 0.0f;
    float g = _index % 3 == 1 ? 1.0f : 0.0f;
    float b = _index % 3 == 2 ? 1.0f : 0.0f;
    
    _strip.setRGB(_index, 0.0f, 0.0f, 0.0f);
    _index = (_index + 1) % _strip.LED_COUNT;
    _strip.setRGB(_index, r, g, b);

    _strip.refresh();
  }
};
