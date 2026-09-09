module;
#include "EngineMacros.h"

export module Engine:Dir;

import std;

export namespace Engine {
namespace Maps
{
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
   * @param charDir The char being converted
   * @return The Dir corresponding to charDir, or Dir::STOP
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
