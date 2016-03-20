#include <assert.h>
#include <iostream>
#include "Create.h"
#include "Map.h"
#include "Node.h"
#include "stdlib.h"
#include "UI/Input.h"
namespace Engine {
namespace Maps
{
  Map::Map(): Map(DEFAULT_MAP_SIZE) {
    setID(0);
    for (auto &i: grid) { i = new Node; }
    buildMoveData();
  }

  Map::Map(int mapSize): grid{mapSize*mapSize, nullptr}
  , mapSize{mapSize} {
    setID(0);
  }

  Map::~Map() {
    deleteGrid();
  }

  void Map::activate() {
    for ( auto &node : grid ) {
      node->activate();
    }
  }

  void Map::setNode(int xInd, int yInd, Node* node) {
    // Reference to node ptr being replaced
    Node *&alreadyThere = grid.at(yInd*mapSize + xInd);
    delete alreadyThere; // Deletes the node that might be there
    alreadyThere = node;
   }


  void Map::buildMoveData() {
    for ( int yIndex( 0 ); yIndex < mapSize; yIndex++ ) {
      for ( int xIndex( 0 ); xIndex < mapSize; xIndex++ ) {
        // Add node links to the current node
        Node &currentNode = *getNode(xIndex, yIndex);
        if ( yIndex < mapSize-1 ) { // Build north
          Node *north = getNode(xIndex, yIndex+1);
          currentNode.setNodeLink(Dir::NORTH, north);
        }
        if ( xIndex < mapSize-1 ) { // build east
          Node *east = getNode(xIndex+1, yIndex);
          currentNode.setNodeLink(Dir::EAST, east);
        }
        if ( xIndex > 0 ) { // build west
          Node *west = getNode(xIndex-1, yIndex);
          currentNode.setNodeLink(Dir::WEST, west);
        }
        if ( yIndex > 0 ) { // build south
          Node *south = getNode(xIndex, yIndex-1);
          currentNode.setNodeLink(Dir::SOUTH, south);
        }
      }
    }
  }

  Node* Map::getNode(int xInd, int yInd) {
    assert(xInd < mapSize && yInd < mapSize);
    assert(grid.at(yInd*mapSize + xInd) != nullptr);
    return grid.at(yInd*mapSize + xInd);
  }

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
