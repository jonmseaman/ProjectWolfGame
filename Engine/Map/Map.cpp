#include <assert.h>
#include <iostream>
#include <Creation/Create.h>
#include <UI/Input.h>
#include "Map.h"
#include "Node.h"
#include "stdlib.h"

using std::cout;
using std::endl;

namespace Engine {
namespace Maps {
using namespace Creation;

const int Map::DEFAULT_MAP_SIZE = 5;
/**
* Makes a map of specific size. Does not make any nodes.
* @usage Should be used by derived classes since nodes are not created.
*/
Map::Map() : grid{ DEFAULT_MAP_SIZE * DEFAULT_MAP_SIZE, nullptr }
, mapSize{ DEFAULT_MAP_SIZE } {
  for (Node*& i : grid) { i = new Node; }
  buildMoveData();
}

Map::Map(int mapWidth) : grid{ mapWidth*mapWidth, nullptr }
, mapSize{ mapWidth } {}

Map::~Map() {
  deleteGrid();
}

void Map::clearSavable() {
  for (auto& node : grid) {
    delete node;
    node = nullptr;
  }
  grid.clear();
}

void Map::activate() {
  for (auto &node : grid) {
    node->activate();
  }
}
/**
* Allows the nodes to be replaced.
* Deletes the node being replaced.
* @post The node at xInd, yInd = #node
*/
void Map::setNode(int xInd, int yInd, Node* node) {
  // Reference to node ptr being replaced
  Node *&alreadyThere = grid.at(yInd*mapSize + xInd);
  delete alreadyThere; // Deletes the node that might be there
  alreadyThere = node;
}

/**
* Connects the nodes to each other.
* @pre Elements of grid are not nullptrs
* @post Nodes will be linked together
*/
void Map::buildMoveData() {
  for (int yIndex(0); yIndex < mapSize; yIndex++) {
    for (int xIndex(0); xIndex < mapSize; xIndex++) {
      // Add node links to the current node
      Node &currentNode = *getNode(xIndex, yIndex);
      if (yIndex < mapSize - 1) { // Build north
        Node *north = getNode(xIndex, yIndex + 1);
        currentNode.setNodeLink(Dir::NORTH, north);
      }
      if (xIndex < mapSize - 1) { // build east
        Node *east = getNode(xIndex + 1, yIndex);
        currentNode.setNodeLink(Dir::EAST, east);
      }
      if (xIndex > 0) { // build west
        Node *west = getNode(xIndex - 1, yIndex);
        currentNode.setNodeLink(Dir::WEST, west);
      }
      if (yIndex > 0) { // build south
        Node *south = getNode(xIndex, yIndex - 1);
        currentNode.setNodeLink(Dir::SOUTH, south);
      }
    }
  }
}
/**
* @return number of nodes in this map.
*/
int Map::getMapSize() {
  return this->mapSize;
}
/**
* Allows access to nodes in the map.
* @pre xInd, yInd < mapSize
* @return Pointer to node at xInd, yInd
*/
Node* Map::getNode(int xInd, int yInd) {
  assert(0 <= xInd && 0 <= yInd);
  assert(xInd < mapSize && yInd < mapSize);
  assert(grid.at(yInd*mapSize + xInd) != nullptr);
  return grid.at(yInd*mapSize + xInd);
}
/**
* Deletes all elements of the grid.
* @usage Used by the destructor
*/
void Map::deleteGrid() {
  for (int i(0); i < grid.size(); ++i) {
    delete grid.at(i);
  }
}

void Map::save() {
  startSave("Map");

  // Save the nodes
  SAVE(mapSize);
  for (int i = 0; i < grid.size(); i++) {
    grid.at(i)->save();
  }

  endSave();
}

void Map::load() {
  clearSavable();
  startLoad("Map");

  // Load the nodes
  LOAD(mapSize);
  grid = std::vector<Node*>(mapSize * mapSize, nullptr);
  for (int i = 0; i < grid.size(); i++) {
    grid.at(i) = Create::loadNewNode();
  }
  buildMoveData(); // Get map ready for use.

  endLoad();
}
} // End namespace Maps
}