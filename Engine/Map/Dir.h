#ifndef DIR_H
#define DIR_H
#include <string>
#include <Engine.h>
namespace Engine {
namespace Maps
{
  //static const int NUM_DIRS = 7; // Stopped == 0, and 6 dirs
  /**
   * Directions. Used by nodes and maps.
   */
  enum class Dir
  {
    STOP = 0,
    NORTH,
    EAST,
    WEST,
    SOUTH,
    UP,
    DOWN,
  };

  /// Number of direction values (including STOP).
  inline constexpr int NUM_DIRS = 7;

  /// Converts a Dir to an array index.
  inline constexpr std::size_t dir_idx(Dir d) noexcept {
    return static_cast<std::size_t>(d);
  }

  /**
   * Converts a char of wasdqe to the corresponding travel direction
   * @param The char being converted to an int
   * @post charToDir in enum Dir
   * @return An int corresponding to charDir
   */
  ENGINE_API Dir charToDir(char charDir);
  /**
   * Converts a Dir to its name.
   */
  ENGINE_API std::string dirName(Dir dir);
  /**
   * Converts a direction to its reverse direction (ie: N-->S)
   */
  ENGINE_API Dir oppositeDir(Dir dir);
}
}
#endif // DIR_H
