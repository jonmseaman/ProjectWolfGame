#include "Map.h"
#include "utils.h"
#include "dLog.h"
#include "stdlib.h"
#include <assert.h>
namespace Maps
{ //TODO: Allow for rectangular maps
  Map::Map(): Map(DEFAULT_MAP_SIZE) {
    for (auto &i: grid) { i = new Node; }
    buildMoveData();
    populate();
  }

  Map::Map(int mapSize): grid{mapSize*mapSize, nullptr}
  , mapSize{mapSize}
  {
    // Map ctor
  }

  Map::~Map() {
    deleteGrid();
  }

  bool Map::activate() {
    dLog << "Map activated." << std::endl;
    for ( auto &node : grid ) {
      node->activate();
    }
    return 0;
  }

  void Map::buildMoveData() { // TODO: Have buildMoveData() ignore nullptrs in the grid.
    for ( int yIndex( 0 ); yIndex < mapSize; yIndex++ ) {
      for ( int xIndex( 0 ); xIndex < mapSize; xIndex++ ) {
        dLog << "\tsetNodeLinks: " << xIndex << ", " << yIndex << std::endl;
        // Add node links to the current node
        Node &currentNode = *getNode(xIndex, yIndex);
        if ( yIndex < mapSize-1 ) { // Build north
          Node *north = getNode(xIndex, yIndex+1);
          currentNode.setNodeLink(Dir::North, north);
        }
        if ( xIndex < mapSize-1 ) { // build east
          Node *east = getNode(xIndex+1, yIndex);
          currentNode.setNodeLink(Dir::East, east);
        }
        if ( xIndex > 0 ) { // build west
          Node *west = getNode(xIndex-1, yIndex);
          currentNode.setNodeLink(Dir::West, west);
        }
        if ( yIndex > 0 ) { // build south
          Node *south = getNode(xIndex, yIndex-1);
          currentNode.setNodeLink(Dir::South, south);
        }
      }
    }
  }

  Node* Map::getNode(int xInd, int yInd) {
    assert(grid.at(yInd*mapSize + xInd)!=nullptr);
    return grid.at(yInd*mapSize + xInd);
  }

  void Map::populate() {
    for ( int yIndex( 0 ); yIndex < mapSize; yIndex++ ) {
      for ( int xIndex( 0 ); xIndex < mapSize; xIndex++ ) {
        // TODO: fill the node
        dLog << "Trying to fill node y: " << yIndex
                  << " x: " << xIndex << std::endl;
      }
    }
  }

  void Map::initializeGrid() {
    for (auto &i : grid ) {
      i = nullptr;
    }
  }

  void Map::deleteGrid() {
    for (int i(0); i<grid.size(); ++i) {
      delete grid.at(i);
    }
  }
} // End namespace Maps
