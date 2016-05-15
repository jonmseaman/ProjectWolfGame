#include <assert.h>
#include <string>
#include "Dir.h"

namespace Engine {
namespace Maps {

/**
* Converts a char of wasdqe to the corresponding travel direction
* @param The char being converted to an int
* @post charToDir in enum Dir
* @return An int corresponding to charDir
*/
int charToDir(char dir) {
  int intDir = 0;
  if (dir == 'w') {
    intDir = Maps::NORTH;
  } else if (dir == 'a') {
    intDir = Maps::WEST;
  } else if (dir == 's') {
    intDir = Maps::SOUTH;
  } else if (dir == 'd') {
    intDir = Maps::EAST;
  } else if (dir == 'q') {
    intDir = Maps::DOWN;
  } else if (dir == 'e') {
    intDir = Maps::UP;
  }
  return intDir;
}

/**
* Converts an int in enum Dir to its name
* @param dir The int being converted to a string
* @pre dir is a valid element of enum Dir
* @return The name of the direction corresponding to dir
*/
std::string dirName(int dir) {
  assert(0 <= dir && dir < NUM_DIRS);

  std::string dirName;
  switch (dir) {
    case Dir::STOP:
      dirName = "Stop";
      break;
    case Dir::NORTH:
      dirName = "North";
      break;
    case Dir::EAST:
      dirName = "East";
      break;
    case Dir::WEST:
      dirName = "West";
      break;
    case Dir::SOUTH:
      dirName = "South";
      break;
    case Dir::UP:
      dirName = "Up";
    case Dir::DOWN:
      dirName = "DOWN";
      break;
  }
  return dirName;
}

/**
* Converts a direction to its reverse direction (ie: N-->S)
* @param dir The dir being converted
* @pre 0 <= dir <= NUM_DIRS
* @return An int corresponding to the opposite direction
*/
int oppositeDir(int dir) {
  assert(0 <= dir && dir < NUM_DIRS);

  int revDir; // The reverse directoin
  if (dir == Dir::STOP) {
    revDir = Dir::STOP;
  } else if (dir == Dir::NORTH) {
    revDir = Dir::SOUTH;
  } else if (dir == Dir::EAST) {
    revDir = Dir::WEST;
  } else if (dir == Dir::WEST) {
    revDir = Dir::EAST;
  } else if (dir == Dir::SOUTH) {
    revDir = Dir::NORTH;
  } else if (dir == Dir::UP) {
    revDir = Dir::DOWN;
  } else if (dir == Dir::DOWN) {
    revDir = Dir::UP;
  }
  return revDir;
}


} // End Maps
} // End Engine
