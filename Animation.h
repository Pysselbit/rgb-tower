
#include "Color.h"
#include "Tower.h"
#include "Light.h"

class Animation {

  const float TOWER_RADIUS = 1.0f;
  
  const float Y_MIN = 0.5f;
  const float Y_MAX = 3.5f;
  
  const float RADIUS_MIN = 1.2f;
  const float RADIUS_MAX = 2.0f;

  const unsigned long RESET_MILLIS = 86400000ul; // 24 h: 24 * 60 * 60 * 1000.

  Tower _tower;

  public:
  
  Animation() {}

  void update() {
    float time = (float)(millis() % RESET_MILLIS) / 1000.0f;
    time /= 5.0f;
  
    Light lightA, lightB;

    // Color components:
    float a = 1.0f * ((1.0f + cos(time)) / 2.0f);
    float b = 0.5f * ((1.0f + cos(0.8f * time)) / 2.0f);
    float c = 0.5f * ((1.0f + cos(0.6f * time)) / 2.0f);

    Color innerColor = Color(1.0f, 0.6f, 0.1f); // Inner color stays yellow.
    Color outerColor = Color(1.0f, 0.2f, 0.1f); // Outer color stays red.

    lightA.innerColor = lightB.innerColor = innerColor;
    lightA.outerColor = lightB.outerColor = outerColor;

    // Positions:
    float x = TOWER_RADIUS * cos(0.65f * time);
    float y = (1.0f + sin(0.25f * time)) / 2.0f;
    float z = TOWER_RADIUS * sin(0.65f * time);
    
    float yA = Y_MIN + (Y_MAX - Y_MIN) * y;
    float yB = Y_MIN + (Y_MAX - Y_MIN) * (1.0f - y);

    lightA.position = Vec3(x, yA, z);
    lightB.position = Vec3(-x, yB, -z);

    // Radii of light spheres (bigger when further apart):
    float yDifference = abs(yA - yB) / (Y_MAX - Y_MIN);
    float radiusFactor = RADIUS_MIN + yDifference * (RADIUS_MAX - RADIUS_MIN);
    lightA.radius = radiusFactor * (0.7f + 0.3f * sin(0.25f * time));
    lightB.radius = radiusFactor * (0.7f - 0.3f * sin(0.25f * time));

    lightA.shiftOuterColor = false;
    lightB.shiftOuterColor = false;

    Light lights[] = {lightA, lightB};

    _tower.updateLights(lights, 1);
    _tower.refreshLEDs();
  }

  private:

  // Rearrange components and makes the biggest component r, and smallest g:
  Color getWarmestColor(float a, float b, float c) {
    if (a > b && a > c) {
      if (b > c)
        return Color(a, c, b);
      else
        return Color(a, b, c);
    }
    else if (b > a && b > c) {
      if (a > c)
        return Color(b, c, a);
      else
        return Color(b, a, c);
    }
    else {
      if (a > b)
        return Color(c, b, a);
      else
        return Color(c, a, b);
    }
  }
};
