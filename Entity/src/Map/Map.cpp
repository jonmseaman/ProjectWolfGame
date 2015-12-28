#include <assert.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include "Create.h"
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

  pairType Map::toTree() {
    using namespace boost::property_tree;
    ptree tree;
    tree.push_back(XML_VAR_PAIR(mapSize));
    // Should a location be saved?
    for (Node* node : grid) {
      tree.push_back(node->toTree());
    }

    return ptree::value_type("Map", tree);
  }

  void Map::fromTree(const pairType &p) {
    const treeType &tree = p.second;

    { // Get the mapSize first:
      auto mapSizeIterator = tree.find("mapSize");
      const std::string &data = mapSizeIterator->second.data();
      mapSize = std::stoi(data);
      deleteGrid();
      grid = std::vector<Node*>(mapSize*mapSize, nullptr);
    }

    auto it = tree.begin();
    int nodeNumber = 0;
    while (it != tree.end()) {
      const std::string &key = it->first;
      const std::string &data = it->second.data();
      if (key == "Node") {
        // Sets the next node from xml
        // Note that since x,y is not recorded in the xml,
        // nodes can only be loaded in the order they were saved
        grid.at(nodeNumber) = Factory::newNode(*it);
        nodeNumber++;
      }
      it++;
    }
    // So that the player can move around in the map.
    buildMoveData();
  }
} // End namespace Maps
