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

      /**
       * Creates a map with size mapSize
       * Nodes are initialized to nullptrs
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
      std::vector<Node*> grid; // The array of nodes that the player sees [y*size + x]
    private:
      /**
       * Deletes all elements of the grid.
       * For use by the dtor
       */
      void deleteGrid();
      // Vars
      const int DEFAULT_MAP_SIZE { 5 };
      int mapSize; // The width & height of the square grid of nodes
  };
}

#endif
