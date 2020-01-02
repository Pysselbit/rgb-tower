
#ifndef Color_h
#define Color_h

typedef struct Color {
  float r, g, b;

  Color() {
    r = g = b = 0.0f;
  }

  Color(float rgb) {
    r = g = b = rgb;
  }

  Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
  }
};

Color operator *(float f, const Color& c) {
  return Color(f * c.r, f * c.g, f * c.b);
}

Color operator* (const Color& c, float f) {
  return Color(f * c.r, f * c.g, f * c.b);
}

#endif
