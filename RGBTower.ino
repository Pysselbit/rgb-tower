#include "Animation.h"

float _time;

Animation _animation;

void setup() {
  Serial.begin(9600);

  _time = 0.0f;
}

void loop() {
  float time = (float)millis() / 1000.0f;
  float deltaTime = time - _time;

  _animation.update(time, deltaTime);
  
  _time = time;
}
