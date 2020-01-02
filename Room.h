
#include "Vec3.h"
#include "Color.h"

class Room {

  int _stripIndex;

  Vec3 _position;
  Color _color;

  public:
  
  Room(int stripIndex, float radius, float angle, int floor) {
    _stripIndex = stripIndex;
    
    float x = radius * cos(angle);
    float y = (float)floor + 0.5f;
    float z = radius * sin(angle);

    _position = Vec3(x, y, z);
  }

  void update(Vec3 lightPosition, float lightRadius) {
    if ((lightPosition - _position).magnitude() <= lightRadius)
      _color = Color(1.0f, 1.0f, 1.0f);
    else
      _color = Color();
  }

  void setLED(Strip strip) {
    strip.setRGB(_stripIndex, _color.r, _color.g, _color.b);
  }
};
