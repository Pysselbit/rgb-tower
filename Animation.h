
#include "Color.h"
#include "Tower.h"

class Animation {

  Tower _tower;

  public:
  
  Animation() {}

  void update(float time, float deltaTime) {
    float x = 1.0f * cos(time);
    float y = 2.5f * (1.0 + sin(time));
    float z = 1.0f * sin(time);

    Vec3 lightPosition = Vec3(x, y, z);
    float lightRadius = 1.0f;

    _tower.update(lightPosition, lightRadius);
    _tower.refreshLEDs();
  }
};
