
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

  static const byte ROOM_COUNT = 34;

  // LEDs facing east (positive X):
  const byte INDEX_XP_Y0_ZN[3] = {30, 13, 44};
  const byte INDEX_XP_Y0_ZP[3] = {44, 31, 30};
  const byte INDEX_XP_Y1_ZN[3] = {31, 4, 31};
  const byte INDEX_XP_Y1_ZP[3] = {43, 20, 43};
  const byte INDEX_XP_Y2_ZN[3] = {32, 5, 42};
  const byte INDEX_XP_Y2_ZP[3] = {42, 21, 32};
  const byte INDEX_XP_Y3_ZN[3] = {33, 23, 33};
  const byte INDEX_XP_Y3_ZP[3] = {41, 29, 41};
  
  // LEDs facing north (positive Z):
  const byte INDEX_ZP_Y0_XP[3] = {4, 14, 29};
  const byte INDEX_ZP_Y0_XN[3] = {12, 15, 21};
  const byte INDEX_ZP_Y1_XP[3] = {5, 32, 5};
  const byte INDEX_ZP_Y1_XN[3] = {11, 42, 11};
  const byte INDEX_ZP_Y2_XP[3] = {6, 9, 27};
  const byte INDEX_ZP_Y2_XN[3] = {10, 44, 23};
  const byte INDEX_ZP_Y3_XP[3] = {7, 33, 7};
  const byte INDEX_ZP_Y3_XN[3] = {9, 24, 9};
  const byte INDEX_ZP_Y4[3] = {8, 17, 8};

  // LEDs facing west (negative X):
  const byte INDEX_XN_Y0_ZP[3] = {13, 22, 20};
  const byte INDEX_XN_Y0_ZN[3] = {20, 6, 13};
  const byte INDEX_XN_Y1_ZP[3] = {14, 18, 14};
  const byte INDEX_XN_Y1_ZN[3] = {19, 11, 19};
  const byte INDEX_XN_Y2_ZP[3] = {15, 28, 18};
  const byte INDEX_XN_Y2_ZN[3] = {18, 30, 15};
  const byte INDEX_XN_Y3_ZP[3] = {16, 25, 16};
  const byte INDEX_XN_Y3_ZN[3] = {17, 10, 17};
  
  // LEDs facing south (negative Z):
  const byte INDEX_ZN_Y0_XN[3] = {21, 27, 12};
  const byte INDEX_ZN_Y0_XP[3] = {29, 41, 4};
  const byte INDEX_ZN_Y1_XN[3] = {22, 8, 22};
  const byte INDEX_ZN_Y1_XP[3] = {28, 26, 28};
  const byte INDEX_ZN_Y2_XN[3] = {23, 43, 10};
  const byte INDEX_ZN_Y2_XP[3] = {27, 16, 6};
  const byte INDEX_ZN_Y3_XN[3] = {24, 19, 24};
  const byte INDEX_ZN_Y3_XP[3] = {26, 7, 26};
  const byte INDEX_ZN_Y4[3] = {25, 12, 25};

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

  void updateLights(Light lights[], int lightCount, float globalIntensity) {
    for (int i = 0; i < ROOM_COUNT; i++)
      _rooms[i].updateLights(lights, lightCount, globalIntensity);
  }

  void refreshLEDs(byte ledOrder) {
    for (int i = 0; i < ROOM_COUNT; i++)
      _rooms[i].setLED(&_strip, ledOrder);

    _strip.refresh();
  }
};
