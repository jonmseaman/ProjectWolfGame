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
  }

  /**
   * Creates a map with size mapSize
   * Nodes are initialized to nullptrs
   */
  Map::Map(int mapSize): grid{mapSize*mapSize, nullptr}
  , mapSize{mapSize} {
  }

  Map::~Map() {
    deleteGrid();
  }

  /**
   * Activates all nodes in the map.
   */
  void Map::activate() {
    dLog << "Map activated." << std::endl;
    for ( auto &node : grid ) {
      node->activate();
    }
  }

  /**
   * Allows the nodes to be replaced.
   * @post The node at xInd, yInd = #node
   */
  void Map::setNode(int xInd, int yInd, Node* node) {
    Node *&alreadyThere = grid.at(yInd*mapSize + xInd);
    if (alreadyThere != nullptr) {
      delete alreadyThere;
    }
    alreadyThere = node;
   }

  /**
   * Connects the nodes to each other.
   * @pre Elements of grid are not nullptrs
   * @post Nodes will know
   */
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

  /**
   * Allows access to nodes in the map.
   * @pre xInd, yInd < mapSize
   * @return Pointer to node at xInd, yInd
   */
  Node* Map::getNode(int xInd, int yInd) {
    assert(xInd < mapSize && yInd < mapSize);
    assert(grid.at(yInd*mapSize + xInd) != nullptr);
    return grid.at(yInd*mapSize + xInd);
  }

  /**
   * Deletes all elements of the grid.
   * For use by the dtor
   */
  void Map::deleteGrid() {
    for (int i(0); i < grid.size(); ++i) {
      delete grid.at(i);
    }
  }
} // End namespace Maps
