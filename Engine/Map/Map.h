#ifndef MAP_H
#define MAP_H
#include <Engine.h>
#include <vector>
#include "Savable.h"

namespace Engine {
namespace Maps
{
  class Node;
  class ENGINE_API Map : public File::Savable
  {
    public:
      Map(); // Default constructor. Creates empty map with blank nodes
      /**
       * Makes a map of specific size. Does not make any nodes.
       * @usage Should be used by derived classes since nodes are not created.
       */
      Map(int mapSize); // Makes a map of specific size. Does not make any nodes
      virtual ~Map(); // Deletes nodes.
      SAVABLE;

      // Data Acess

      /**
       * @return number of nodes in this map.
       */
      int getMapSize();
      /**
       * Allows access to nodes in the map.
       * @pre xInd, yInd < mapSize
       * @return Pointer to node at xInd, yInd
       */
      Maps::Node* getNode(int xInd, int yInd);
      /**
       * Allows the nodes to be replaced.
       * Deletes the node being replaced.
       * @post The node at xInd, yInd = #node
       */
      void setNode(int xInd, int yInd, Node* node);
      /**
       * Activates all nodes in the map.
       */
      void activate();
    protected:
      /**
       * Connects the nodes to each other.
       * @pre Elements of grid are not nullptrs
       * @post Nodes will be linked together
       */
      void buildMoveData();
      /**
       * These are nodes that make up the base layer of the game world.
       * Other nodes may only exist if made by other nodes.
       */
      std::vector<Node*> grid;
    private:
      /**
       * Deletes all elements of the grid.
       * @usage Used by the destructor
       */
      void deleteGrid();
      // Vars
      const int DEFAULT_MAP_SIZE { 5 };
      /**
       * The width, height of the map. mapSize^2 = number of nodes in grid
       */
      int mapSize;
  };
}
}
#endif
