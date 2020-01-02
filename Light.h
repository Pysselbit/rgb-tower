
#ifndef Light_h
#define Light_h

#include "Vec3.h"
#include "Color.h"

struct Light {
  Color color;
  Vec3 position;
  float radius;
};

#endif
