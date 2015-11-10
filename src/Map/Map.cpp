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
    dLog << "Maps::Map::buildMoveData() called" << std::endl;
    for ( int yIndex( 0 ); yIndex < mapSize; yIndex++ ) {
      for ( int xIndex( 0 ); xIndex < mapSize; xIndex++ ) {
        dLog << "\tTrying to build moveData for x: " << xIndex
                  << " y: " << yIndex << std::endl;
        if ( yIndex < mapSize-1 ) { // Build north
          getNode(xIndex, yIndex)->setMoveData(Dir::North, getNode(xIndex, yIndex+1)->getName(), getNode(xIndex, yIndex+1) );
          getNode(xIndex, yIndex)->setNodeLink(Dir::North, getNode(xIndex, yIndex+1) );
          // TODO: Make the second line here not necessary.
          // setNodeLink is giving the node a pointer to the node it connects to.
          // MoveData has the same pointers, but the node can't really use them because the node needs access to more
          // of the nodes than MoveData allows access to.
        }
        if ( xIndex < mapSize-1 ) { // build east
          getNode(xIndex, yIndex)->setMoveData(Dir::East, getNode(xIndex+1, yIndex)->getName(), getNode(xIndex+1, yIndex) );
          getNode(xIndex, yIndex)->setNodeLink(Dir::East, getNode(xIndex+1, yIndex) );
        }
        if ( xIndex > 0 ) { // build west
          getNode(xIndex, yIndex)->setMoveData(Dir::West, getNode(xIndex-1, yIndex)->getName(), getNode(xIndex-1, yIndex) );
          getNode(xIndex, yIndex)->setNodeLink(Dir::West, getNode(xIndex-1, yIndex) );
        }
        if ( yIndex > 0 ) { // build south
          getNode(xIndex, yIndex)->setMoveData(Dir::South, getNode(xIndex, yIndex-1)->getName(), getNode(xIndex, yIndex-1) );
          getNode(xIndex, yIndex)->setNodeLink(Dir::South, getNode(xIndex, yIndex-1) );
        }
      }
    }
  }

  Node* Map::getNode(int xInd, int yInd) {
    assert(grid.at(yInd*mapSize + xInd)!=nullptr);
    return grid.at(yInd*mapSize + xInd);
  }

  bool Map::populate() {
    for ( int yIndex( 0 ); yIndex < mapSize; yIndex++ ) {
      for ( int xIndex( 0 ); xIndex < mapSize; xIndex++ ) {
        // TODO: fill the node
        dLog << "Trying to fill node y: " << yIndex
                  << " x: " << xIndex << std::endl;
      }
    }
    return false;
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
