
#ifndef Light_h
#define Light_h

#include "Vec3.h"
#include "Color.h"

struct Light {
  Vec3 position;
  float radius;
  
  Color innerColor;
  Color outerColor;

  bool shiftOuterColor;
};

#endif
