
#include "Color.h"
#include "Tower.h"
#include "Light.h"

class Animation {

  const float TOWER_RADIUS = 1.0f;
  
  const float Y_MIN = 0.5f;
  const float Y_MAX = 3.5f;
  
  const float RADIUS_MIN = 1.2f;
  const float RADIUS_MAX = 2.0f;

  const long FADE_TIME = 1.0f;
  const long SWITCH_TIME_MIN_MILLIS = 120000l; // 2 min: 2 * 60 * 1000;
  const long SWITCH_TIME_MAX_MILLIS = 600000l; // 10 min: 10 * 60 * 1000;

  const unsigned long RESET_MILLIS = 86400000ul; // 24 h: 24 * 60 * 60 * 1000.

  Tower _tower;

  public:
  
  Animation() {}

  void update() {
    long timeMillis = millis() % RESET_MILLIS;

    if (timeMillis > nextLedOrderSwitch) {
      ledOrder = (ledOrder + 1) % 4;

      previousLedOrderSwitch = nextLedOrderSwitch;
      nextLedOrderSwitch = timeMillis + random(SWITCH_TIME_MIN_MILLIS, SWITCH_TIME_MAX_MILLIS);
    }

    if (nextLedOrderSwitch - timeMillis > 2 * SWITCH_TIME_MAX_MILLIS)
      nextLedOrderSwitch = 0l; // On reset.
    
    float time = (float)timeMillis / 1000.0f;
    
    float globalIntensity = min(1.0f, min(nextLedOrderSwitch / 1000.0f - time, time - previousLedOrderSwitch / 1000.0f) / FADE_TIME);

    bool isRandomOrder = ledOrder % 2 == 1;

    if (isRandomOrder)
      time /= 3.0f;
  
    Light lightA, lightB;

    // Color components:
    float a = 1.0f * ((1.0f + cos(time)) / 2.0f);
    float b = 0.5f * ((1.0f + cos(0.8f * time)) / 2.0f);
    float c = 0.5f * ((1.0f + cos(0.6f * time)) / 2.0f);

    Color innerColor = Color(1.0f, 0.6f, 0.1f); // Inner color stays yellow.
    Color outerColor = getWarmestColor(a, b, c);
    if (isRandomOrder)
      outerColor = Color(1.0f, 0.2f, 0.1f); // Outer color stays red.

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

    _tower.updateLights(lights, 2, globalIntensity);
    _tower.refreshLEDs(ledOrder == 3 ? 1 : ledOrder);
  }

  private:

  byte ledOrder;
  long nextLedOrderSwitch;
  long previousLedOrderSwitch;

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
