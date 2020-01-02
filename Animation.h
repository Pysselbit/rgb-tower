
#include "Color.h"
#include "Tower.h"
#include "Light.h"

class Animation {

  Tower _tower;

  Light _light;

  public:
  
  Animation() {}

  void update(float time, float deltaTime) {
    float r = (1.0f + cos(1.0f * time)) / 2.0f;
    float g = (1.0f + cos(3.0f * time)) / 2.0f;
    float b = (1.0f + cos(5.0f * time)) / 2.0f;

    _light.color = Color(r, g, b);
    
    float x = 1.0f * cos(time);
    float y = 2.5f * (1.0f + sin(0.7f * time));
    float z = 1.0f * sin(time);

    _light.position = Vec3(x, y, z);
    _light.radius = 1.0f;

    _tower.update(_light);
    _tower.refreshLEDs();
  }
};
