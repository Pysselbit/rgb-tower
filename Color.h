
#ifndef Color_h
#define Color_h

typedef struct Color {
  float r, g, b;

  Color() {
    r = g = b = 0.0f;
  }

  Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
  }
};

#endif
