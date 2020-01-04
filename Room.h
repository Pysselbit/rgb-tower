
#include "Vec3.h"
#include "Color.h"
#include "Light.h"

class Room {

  int _stripIndex;

  Vec3 _position;
  Color _color;

  int _colorShift;

  public:
  
  Room(int stripIndex, float radius, float angle, int floor) {
    _stripIndex = stripIndex;
    
    float x = radius * cos(angle);
    float y = (float)floor + 0.5f;
    float z = radius * sin(angle);

    _position = Vec3(x, y, z);

    _colorShift = random(3);
  }

  void updateLights(Light lights[], int lightCount) {
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
      Color color = intensity * Color::interpolate(innerColor, outerColor, t);

      _color = _color + color;
    }
  }

  void setLED(Strip* strip) {
    strip->setRGB(_stripIndex, _color.r, _color.g, _color.b);
  }
};
