#ifndef DIR_H
#define DIR_H
namespace Maps
{
  static const int numDirs = 7; // Stopped == 0, and 6 dirs
// Possible directions for movement
  enum Dir
  {
    // Possible directions for movement.
    Stop = 0, /* For use with maps and nodes */
    North,
    East,
    West,
    South,
    Up,
    Down
  };
}
#endif // DIR_H
