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
    friend std::ostream &operator<<(std::ostream &os, const Maps::Map &map);
    friend std::istream &operator>>(std::istream &is, Maps::Map &map);
    public:
      Map(); // Default constructor. Creates empty map with blank nodes
      Map(int mapSize); // Makes a map of specific size. Does not make any nodes
      // TODO: implement Map(int mapSize)
      virtual ~Map(); // Deletes nodes.
      bool activate(); // Activates each node in the map once.
      void initializeGrid(); // Sets all elements of grid to nullptrs
      void deleteGrid(); // Deletes all elements of the grid.
      void getPlayerNodeIndex( int &x, int &y );
      int getMapSize();
      Maps::Node* getNode(int xInd, int yInd);
    protected:
      void buildMoveData(); // Fills node's moveData
      bool populate(); // Puts actors/ entities in
      std::vector<Node*> grid; // The array of nodes that the player sees [y*size + x]
    private:
      const int DEFAULT_MAP_SIZE { 5 };
      int mapSize; // The width & height of the square grid of nodes
  };
}

// Operators
std::ostream &operator<<(std::ostream &os, const Maps::Map &map);
std::istream &operator>>(std::istream &is, Maps::Map &map);

#endif
