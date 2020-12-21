
#include "Vec3.h"
#include "Color.h"
#include "Light.h"

class Room {

  byte _stripIndices[3];

  Vec3 _position;
  Color _color;

  int _colorShift;

  public:
  
  Room(byte stripIndices[], float radius, float angle, int floor) {
    for (byte i = 0; i < 3; i++)
      _stripIndices[i] = stripIndices[i];
    
    float x = radius * cos(angle);
    float y = (float)floor + 0.5f;
    float z = radius * sin(angle);

    _position = Vec3(x, y, z);

    _colorShift = random(3);
  }

  void updateLights(Light lights[], int lightCount, float globalIntensity) {
    _color = Color(0.0f);
    
    for (int i = 0; i < lightCount; i++) {
      Light light = lights[i];
      
      Color innerColor = light.innerColor;
      Color outerColor = light.outerColor;
      
      if (light.shiftOuterColor) {
        if (_colorShift == 1)
          outerColor = Color(outerColor.g, outerColor.b, outerColor.r);
        else if (_colorShift == 2)
          outerColor = Color(outerColor.b, outerColor.r, outerColor.g);
      }
      
      float distance = (light.position - _position).magnitude();
      float intensity = max(0.0f, (light.radius - distance) / light.radius);

      float t = pow(1.0f - intensity, 2.0f);
      Color color = globalIntensity * intensity * Color::interpolate(innerColor, outerColor, t);

      _color = _color + color;
    }
  }

  void setLED(Strip* strip, byte ledOrder) {
    strip->setRGB(_stripIndices[ledOrder], _color.r, _color.g, _color.b);
  }
};
