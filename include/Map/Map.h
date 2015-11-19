#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <vector>
#include "Node.h"

// TODO: Add actor (Actor, x , y)
namespace Maps
{
  class Map
  {
    public:
      Map(); // Default constructor. Creates empty map with blank nodes
      Map(int mapSize); // Makes a map of specific size. Does not make any nodes
      virtual ~Map(); // Deletes nodes.

      // Data Acess
      int getMapSize();
      Maps::Node* getNode(int xInd, int yInd);
      void setNode(int xInd, int yInd, Node* node);
      // Use
      void activate(); // Activates each node in the map once.
    protected:
      void buildMoveData(); // Fills node's moveData
      std::vector<Node*> grid; // The array of nodes that the player sees [y*size + x]
    private:
      void deleteGrid(); // Deletes all elements of the grid.
      // Vars
      const int DEFAULT_MAP_SIZE { 5 };
      int mapSize; // The width & height of the square grid of nodes
  };
}

#endif
