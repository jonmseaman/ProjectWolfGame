#ifndef DIR_H
#define DIR_H
#include <string>
#include <Engine.h>
namespace Engine {
namespace Maps {
//static const int NUM_DIRS = 7; // Stopped == 0, and 6 dirs
/**
 * Directions. Used by nodes and maps.
 */
enum Dir {
  STOP = 0,
  NORTH,
  EAST,
  WEST,
  SOUTH,
  UP,
  DOWN,
  NUM_DIRS,
};

// Returns the int value from enum Dir corresponding wasdqe directions. 
ENGINE_API int charToDir(char charDir);
// Returns a string correspond to the value in enum Dir.
ENGINE_API std::string dirName(int dir);
// Returns the direction facing the opposite of the parameter.
ENGINE_API int oppositeDir(int dir);
}
}
#endif // DIR_H
