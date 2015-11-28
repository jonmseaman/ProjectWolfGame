#include <assert.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "dLog.h"
#include "File.h"
#include "Map.h"
#include "Node.h"
#include "stdlib.h"
#include "utils.h"
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
    dLog << "Map activated." << std::endl;
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
    assert(xInd < mapSize && yInd < mapSize);
    assert(grid.at(yInd*mapSize + xInd) != nullptr);
    return grid.at(yInd*mapSize + xInd);
  }

  void Map::deleteGrid() {
    for (int i(0); i < grid.size(); ++i) {
      delete grid.at(i);
    }
  }

  pairType Map::toXML() {
    using namespace boost::property_tree;
    ptree tree;
    tree.push_back(XML_VAR_PAIR(mapSize));
    // Should a location be saved?
    for (Node* node : grid) {
      tree.push_back(node->toXML());
    }

    return ptree::value_type("Map", tree);
  }

  void Map::fromXML(const pairType &p) {

  }
} // End namespace Maps
