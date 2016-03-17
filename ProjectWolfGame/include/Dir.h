#ifndef DIR_H
#define DIR_H
#include <string>

namespace Maps
{
  static const int NUM_DIRS = 7; // Stopped == 0, and 6 dirs
  /**
   * Directions. Used by nodes and maps.
   */
  enum Dir
  {
    Stop = 0,
    North,
    East,
    West,
    South,
    Up,
    Down,
  };

  /**
   * Converts a char of wasdqe to the corresponding travel direction
   * @param The char being converted to an int
   * @post charToDir in enum Dir
   * @return An int corresponding to charDir
   */
  int charToDir(char charDir);
  /**
   * Converts an int in enum Dir to its name
   * @param dir The int being converted to a string
   * @pre dir is a valid element of enum Dir
   * @return The name of the direction corresponding to dir
   */
  std::string dirName(int dir);
  /**
   * Converts a direction to its reverse direction (ie: N-->S)
   * @param dir The dir being converted
   * @pre 0 <= dir <= NUM_DIRS
   * @return An int corresponding to the opposite direction
   */
  int oppositeDir(int dir);
}
#endif // DIR_H
