#ifndef DIR_H
#define DIR_H
namespace Maps
{
  static const int numDirs = 7; // Stopped == 0, and 6 dirs
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
    Down
  };
}
#endif // DIR_H
