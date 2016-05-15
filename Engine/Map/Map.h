#ifndef MAP_H
#define MAP_H
#include <Engine.h>
#include <vector>
#include "Savable.h"

namespace Engine {
namespace Maps {
class Node;
class ENGINE_API Map : public File::Savable {
public:
  Map(); // Default constructor. Creates empty map with blank nodes
  Map(int mapWidth); // Makes a map of specific size. Does not make any nodes
  virtual ~Map(); // Deletes nodes.
  SAVABLE_CLEAR;

  // Data Acess

  int getMapSize();
  Maps::Node* getNode(int xInd, int yInd);
  void setNode(int xInd, int yInd, Node* node);
  /**
   * Activates all nodes in the map.
   */
  void activate();
  /**
  * These are nodes that make up the base layer of the game world.
  * Other nodes may only exist if made by other nodes.
  */
  std::vector<Node*> grid;
protected:
  void buildMoveData();
private:
  void deleteGrid();
  // Vars
  static const int DEFAULT_MAP_SIZE;
  /**
   * The width, height of the map. mapSize^2 = number of nodes in grid
   */
  int mapSize;
};
}
}
#endif
