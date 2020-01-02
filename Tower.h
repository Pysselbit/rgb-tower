
#include "Strip.h"
#include "Vec3.h"
#include "Room.h"
#include "Light.h"

class Tower {

  static const int ROOM_COUNT = 34;

  // LEDs facing east (positive X):
  const int INDEX_XP_0_ZN = 30;
  const int INDEX_XP_0_ZP = 44;
  const int INDEX_XP_1_ZN = 31;
  const int INDEX_XP_1_ZP = 43;
  const int INDEX_XP_2_ZN = 32;
  const int INDEX_XP_2_ZP = 42;
  const int INDEX_XP_3_ZN = 33;
  const int INDEX_XP_3_ZP = 41;
  
  // LEDs facing north (positive Z):
  const int INDEX_ZP_0_XP = 4;
  const int INDEX_ZP_0_XN = 12;
  const int INDEX_ZP_1_XP = 5;
  const int INDEX_ZP_1_XN = 11;
  const int INDEX_ZP_2_XP = 6;
  const int INDEX_ZP_2_XN = 10;
  const int INDEX_ZP_3_XP = 7;
  const int INDEX_ZP_3_XN = 9;
  const int INDEX_ZP_4 = 8;

  // LEDs facing west (negative X):
  const int INDEX_XN_0_ZP = 13;
  const int INDEX_XN_0_ZN = 20;
  const int INDEX_XN_1_ZP = 14;
  const int INDEX_XN_1_ZN = 19;
  const int INDEX_XN_2_ZP = 15;
  const int INDEX_XN_2_ZN = 18;
  const int INDEX_XN_3_ZP = 16;
  const int INDEX_XN_3_ZN = 17;
  
  // LEDs facing south (negative Z):
  const int INDEX_ZN_0_XN = 21;
  const int INDEX_ZN_0_XP = 29;
  const int INDEX_ZN_1_XN = 22;
  const int INDEX_ZN_1_XP = 28;
  const int INDEX_ZN_2_XN = 23;
  const int INDEX_ZN_2_XP = 27;
  const int INDEX_ZN_3_XN = 24;
  const int INDEX_ZN_3_XP = 26;
  const int INDEX_ZN_4 = 25;

  // Cylindrical coordinates used to place LEDs:
  const float RADIUS = 1.0f;
  const float ANGLE_XP_ZN = -TWO_PI / 16.0f;
  const float ANGULAR_STEP = TWO_PI / 8.0f;
  
  Strip _strip;

  // Set up rooms for each floor:
  Room _rooms[ROOM_COUNT] = {
    Room(INDEX_XP_0_ZN, RADIUS, ANGLE_XP_ZN + 0.0f * ANGULAR_STEP, 0),
    Room(INDEX_XP_0_ZP, RADIUS, ANGLE_XP_ZN + 1.0f * ANGULAR_STEP, 0),
    Room(INDEX_ZP_0_XP, RADIUS, ANGLE_XP_ZN + 2.0f * ANGULAR_STEP, 0),
    Room(INDEX_ZP_0_XN, RADIUS, ANGLE_XP_ZN + 3.0f * ANGULAR_STEP, 0),
    Room(INDEX_XN_0_ZP, RADIUS, ANGLE_XP_ZN + 4.0f * ANGULAR_STEP, 0),
    Room(INDEX_XN_0_ZN, RADIUS, ANGLE_XP_ZN + 5.0f * ANGULAR_STEP, 0),
    Room(INDEX_ZN_0_XN, RADIUS, ANGLE_XP_ZN + 6.0f * ANGULAR_STEP, 0),
    Room(INDEX_ZN_0_XP, RADIUS, ANGLE_XP_ZN + 7.0f * ANGULAR_STEP, 0),
    
    Room(INDEX_XP_1_ZN, RADIUS, ANGLE_XP_ZN + 0.0f * ANGULAR_STEP, 1),
    Room(INDEX_XP_1_ZP, RADIUS, ANGLE_XP_ZN + 1.0f * ANGULAR_STEP, 1),
    Room(INDEX_ZP_1_XP, RADIUS, ANGLE_XP_ZN + 2.0f * ANGULAR_STEP, 1),
    Room(INDEX_ZP_1_XN, RADIUS, ANGLE_XP_ZN + 3.0f * ANGULAR_STEP, 1),
    Room(INDEX_XN_1_ZP, RADIUS, ANGLE_XP_ZN + 4.0f * ANGULAR_STEP, 1),
    Room(INDEX_XN_1_ZN, RADIUS, ANGLE_XP_ZN + 5.0f * ANGULAR_STEP, 1),
    Room(INDEX_ZN_1_XN, RADIUS, ANGLE_XP_ZN + 6.0f * ANGULAR_STEP, 1),
    Room(INDEX_ZN_1_XP, RADIUS, ANGLE_XP_ZN + 7.0f * ANGULAR_STEP, 1),
    
    Room(INDEX_XP_2_ZN, RADIUS, ANGLE_XP_ZN + 0.0f * ANGULAR_STEP, 2),
    Room(INDEX_XP_2_ZP, RADIUS, ANGLE_XP_ZN + 1.0f * ANGULAR_STEP, 2),
    Room(INDEX_ZP_2_XP, RADIUS, ANGLE_XP_ZN + 2.0f * ANGULAR_STEP, 2),
    Room(INDEX_ZP_2_XN, RADIUS, ANGLE_XP_ZN + 3.0f * ANGULAR_STEP, 2),
    Room(INDEX_XN_2_ZP, RADIUS, ANGLE_XP_ZN + 4.0f * ANGULAR_STEP, 2),
    Room(INDEX_XN_2_ZN, RADIUS, ANGLE_XP_ZN + 5.0f * ANGULAR_STEP, 2),
    Room(INDEX_ZN_2_XN, RADIUS, ANGLE_XP_ZN + 6.0f * ANGULAR_STEP, 2),
    Room(INDEX_ZN_2_XP, RADIUS, ANGLE_XP_ZN + 7.0f * ANGULAR_STEP, 2),
    
    Room(INDEX_XP_3_ZN, RADIUS, ANGLE_XP_ZN + 0.0f * ANGULAR_STEP, 3),
    Room(INDEX_XP_3_ZP, RADIUS, ANGLE_XP_ZN + 1.0f * ANGULAR_STEP, 3),
    Room(INDEX_ZP_3_XP, RADIUS, ANGLE_XP_ZN + 2.0f * ANGULAR_STEP, 3),
    Room(INDEX_ZP_3_XN, RADIUS, ANGLE_XP_ZN + 3.0f * ANGULAR_STEP, 3),
    Room(INDEX_XN_3_ZP, RADIUS, ANGLE_XP_ZN + 4.0f * ANGULAR_STEP, 3),
    Room(INDEX_XN_3_ZN, RADIUS, ANGLE_XP_ZN + 5.0f * ANGULAR_STEP, 3),
    Room(INDEX_ZN_3_XN, RADIUS, ANGLE_XP_ZN + 6.0f * ANGULAR_STEP, 3),
    Room(INDEX_ZN_3_XP, RADIUS, ANGLE_XP_ZN + 7.0f * ANGULAR_STEP, 3),

    Room(INDEX_ZP_4, RADIUS, 1.0f * PI / 2.0f, 4),
    Room(INDEX_ZN_4, RADIUS, 3.0f * PI / 2.0f, 4),
  };

  public:

  Tower() {}

  void update(Light light) {
    for (int i = 0; i < ROOM_COUNT; i++)
      _rooms[i].update(light);
  }

  void refreshLEDs() {
    for (int i = 0; i < ROOM_COUNT; i++)
      _rooms[i].setLED(&_strip);

    _strip.refresh();
  }
};
