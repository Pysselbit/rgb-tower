
#include "Strip.h"
#include "Vec3.h"
#include "Room.h"
#include "Light.h"

//              ____________
//             /\  \_____\  \
//            // \           \
//           //   \           \
//          //     \           \
//         //       \           \
//        //         \           \
//       //           \           \
//      //   [ ][ ]    \           \
//     //    [ ][ ]     \           \
// Y4 //       Zn        \           \
//   //                  |\___________\
//    |  [ ][ ]  [ ][ ]  | [][] [][] |
//    |  [ ][ ]  [ ][ ]  | [][] [][] |
// Y3 |   ZnXn    ZnXp   | XpZn XpZp |
//    |                  |           |
//    |  [ ][ ]  [ ][ ]  | [][] [][] |
//    |  [ ][ ]  [ ][ ]  | [][] [][] |
// Y2 |   ZnXn    ZnXp   | XpZn XpZp |
//    |                  |           |
//    |  [ ][ ]  [ ][ ]  | [][] [][] |
//    |  [ ][ ]  [ ][ ]  | [][] [][] |
// Y1 |   ZnXn    ZnXp   | XpZn XpZp |
//    |                  |           |
//    |  [ ][ ]  [ ][ ]  | [][] [][] |
//    |  [ ][ ]  [ ][ ]  | [][] [][] |
// Y0 |   ZnXn    ZnXp   | XpZn XpZp |
//    |__________________|___________|
//   [____________________]___________]
//   <-Xn             Xp-> <-Zn    Zp->  
//
class Tower {

  static const int ROOM_COUNT = 34;

  // LEDs facing east (positive X):
  const int INDEX_XP_Y0_ZN = 13;//30;
  const int INDEX_XP_Y0_ZP = 31;//44;
  const int INDEX_XP_Y1_ZN = 4;//31;
  const int INDEX_XP_Y1_ZP = 20;//43;
  const int INDEX_XP_Y2_ZN = 5;//32;
  const int INDEX_XP_Y2_ZP = 21;//42;
  const int INDEX_XP_Y3_ZN = 23;//33;
  const int INDEX_XP_Y3_ZP = 29;//41;
  
  // LEDs facing north (positive Z):
  const int INDEX_ZP_Y0_XP = 14;//4;
  const int INDEX_ZP_Y0_XN = 15;//12;
  const int INDEX_ZP_Y1_XP = 32;//5;
  const int INDEX_ZP_Y1_XN = 42;//11;
  const int INDEX_ZP_Y2_XP = 9;//6;
  const int INDEX_ZP_Y2_XN = 44;//10;
  const int INDEX_ZP_Y3_XP = 33;//7;
  const int INDEX_ZP_Y3_XN = 24;//9;
  const int INDEX_ZP_Y4 = 17;//8;

  // LEDs facing west (negative X):
  const int INDEX_XN_Y0_ZP = 22;//13;
  const int INDEX_XN_Y0_ZN = 6;//20;
  const int INDEX_XN_Y1_ZP = 18;//14;
  const int INDEX_XN_Y1_ZN = 11;//19;
  const int INDEX_XN_Y2_ZP = 28;//15;
  const int INDEX_XN_Y2_ZN = 30;//18;
  const int INDEX_XN_Y3_ZP = 25;//16;
  const int INDEX_XN_Y3_ZN = 10;//17;
  
  // LEDs facing south (negative Z):
  const int INDEX_ZN_Y0_XN = 27;//21;
  const int INDEX_ZN_Y0_XP = 41;//29;
  const int INDEX_ZN_Y1_XN = 8;//22;
  const int INDEX_ZN_Y1_XP = 26;//28;
  const int INDEX_ZN_Y2_XN = 43;//23;
  const int INDEX_ZN_Y2_XP = 16;//27;
  const int INDEX_ZN_Y3_XN = 19;//24;
  const int INDEX_ZN_Y3_XP = 7;//26;
  const int INDEX_ZN_Y4 = 12;//25;

  // Cylindrical coordinates used to place LEDs:
  const float RADIUS = 1.0f;
  const float ANGLE_XP_ZN = -TWO_PI / 16.0f;
  const float ANGULAR_STEP = TWO_PI / 8.0f;
  
  Strip _strip;

  // Set up rooms for each floor:
  Room _rooms[ROOM_COUNT] = {
    Room(INDEX_XP_Y0_ZN, RADIUS, ANGLE_XP_ZN + 0.0f * ANGULAR_STEP, 0),
    Room(INDEX_XP_Y0_ZP, RADIUS, ANGLE_XP_ZN + 1.0f * ANGULAR_STEP, 0),
    Room(INDEX_ZP_Y0_XP, RADIUS, ANGLE_XP_ZN + 2.0f * ANGULAR_STEP, 0),
    Room(INDEX_ZP_Y0_XN, RADIUS, ANGLE_XP_ZN + 3.0f * ANGULAR_STEP, 0),
    Room(INDEX_XN_Y0_ZP, RADIUS, ANGLE_XP_ZN + 4.0f * ANGULAR_STEP, 0),
    Room(INDEX_XN_Y0_ZN, RADIUS, ANGLE_XP_ZN + 5.0f * ANGULAR_STEP, 0),
    Room(INDEX_ZN_Y0_XN, RADIUS, ANGLE_XP_ZN + 6.0f * ANGULAR_STEP, 0),
    Room(INDEX_ZN_Y0_XP, RADIUS, ANGLE_XP_ZN + 7.0f * ANGULAR_STEP, 0),
    
    Room(INDEX_XP_Y1_ZN, RADIUS, ANGLE_XP_ZN + 0.0f * ANGULAR_STEP, 1),
    Room(INDEX_XP_Y1_ZP, RADIUS, ANGLE_XP_ZN + 1.0f * ANGULAR_STEP, 1),
    Room(INDEX_ZP_Y1_XP, RADIUS, ANGLE_XP_ZN + 2.0f * ANGULAR_STEP, 1),
    Room(INDEX_ZP_Y1_XN, RADIUS, ANGLE_XP_ZN + 3.0f * ANGULAR_STEP, 1),
    Room(INDEX_XN_Y1_ZP, RADIUS, ANGLE_XP_ZN + 4.0f * ANGULAR_STEP, 1),
    Room(INDEX_XN_Y1_ZN, RADIUS, ANGLE_XP_ZN + 5.0f * ANGULAR_STEP, 1),
    Room(INDEX_ZN_Y1_XN, RADIUS, ANGLE_XP_ZN + 6.0f * ANGULAR_STEP, 1),
    Room(INDEX_ZN_Y1_XP, RADIUS, ANGLE_XP_ZN + 7.0f * ANGULAR_STEP, 1),
    
    Room(INDEX_XP_Y2_ZN, RADIUS, ANGLE_XP_ZN + 0.0f * ANGULAR_STEP, 2),
    Room(INDEX_XP_Y2_ZP, RADIUS, ANGLE_XP_ZN + 1.0f * ANGULAR_STEP, 2),
    Room(INDEX_ZP_Y2_XP, RADIUS, ANGLE_XP_ZN + 2.0f * ANGULAR_STEP, 2),
    Room(INDEX_ZP_Y2_XN, RADIUS, ANGLE_XP_ZN + 3.0f * ANGULAR_STEP, 2),
    Room(INDEX_XN_Y2_ZP, RADIUS, ANGLE_XP_ZN + 4.0f * ANGULAR_STEP, 2),
    Room(INDEX_XN_Y2_ZN, RADIUS, ANGLE_XP_ZN + 5.0f * ANGULAR_STEP, 2),
    Room(INDEX_ZN_Y2_XN, RADIUS, ANGLE_XP_ZN + 6.0f * ANGULAR_STEP, 2),
    Room(INDEX_ZN_Y2_XP, RADIUS, ANGLE_XP_ZN + 7.0f * ANGULAR_STEP, 2),
    
    Room(INDEX_XP_Y3_ZN, RADIUS, ANGLE_XP_ZN + 0.0f * ANGULAR_STEP, 3),
    Room(INDEX_XP_Y3_ZP, RADIUS, ANGLE_XP_ZN + 1.0f * ANGULAR_STEP, 3),
    Room(INDEX_ZP_Y3_XP, RADIUS, ANGLE_XP_ZN + 2.0f * ANGULAR_STEP, 3),
    Room(INDEX_ZP_Y3_XN, RADIUS, ANGLE_XP_ZN + 3.0f * ANGULAR_STEP, 3),
    Room(INDEX_XN_Y3_ZP, RADIUS, ANGLE_XP_ZN + 4.0f * ANGULAR_STEP, 3),
    Room(INDEX_XN_Y3_ZN, RADIUS, ANGLE_XP_ZN + 5.0f * ANGULAR_STEP, 3),
    Room(INDEX_ZN_Y3_XN, RADIUS, ANGLE_XP_ZN + 6.0f * ANGULAR_STEP, 3),
    Room(INDEX_ZN_Y3_XP, RADIUS, ANGLE_XP_ZN + 7.0f * ANGULAR_STEP, 3),

    Room(INDEX_ZP_Y4, RADIUS, 1.0f * PI / 2.0f, 4),
    Room(INDEX_ZN_Y4, RADIUS, 3.0f * PI / 2.0f, 4),
  };

  public:

  Tower() {}

  void updateLights(Light lights[], int lightCount) {
    for (int i = 0; i < ROOM_COUNT; i++)
      _rooms[i].updateLights(lights, lightCount);
  }

  void refreshLEDs() {
    for (int i = 0; i < ROOM_COUNT; i++)
      _rooms[i].setLED(&_strip);

    _strip.refresh();
  }
};
