
#include "Animation.h"

Animation _animation;

void setup() {
  Serial.begin(9600);
}

void loop() {
  _animation.update();
}
