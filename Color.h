
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

  static Color add(Color a, Color b) {
    return Color(a.r + b.r, a.g + b.g, a.b + b.b);
  }

  static Color multiply(Color c, float f) {
    return Color(f * c.r, f * c.g, f * c.b);
  }

  static Color interpolate(Color a, Color b, float t){
    
    if (t <= 0)
      return a;
    else if (t >= 1.0f)
      return b;

    return add(multiply(a, 1.0f - t), multiply(b, t));
  }
};

Color operator +(const Color& a, const Color& b) {
  return Color::add(a, b);
}

Color operator *(float f, const Color& c) {
  return Color::multiply(c, f);
}

Color operator *(const Color& c, float f) {
  return Color::multiply(c, f);
}

#endif
