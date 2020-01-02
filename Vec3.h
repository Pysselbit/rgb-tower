
#ifndef Vec3_h
#define Vec3_h

struct Vec3 {
  
  float x;
  float y;
  float z;
  
  Vec3() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }
  
  Vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Vec3 operator +(const Vec3& v) {
    float x = this->x + v.x;
    float y = this->y + v.y;
    float z = this->z + v.z;
    
    return Vec3(x, y, z);
  }

  Vec3 operator -(const Vec3& v) {
    float x = this->x - v.x;
    float y = this->y - v.y;
    float z = this->z - v.z;
    
    return Vec3(x, y, z);
  }

  float magnitude() {
    return sqrt(x * x + y * y + z * z);
  }
};

#endif
