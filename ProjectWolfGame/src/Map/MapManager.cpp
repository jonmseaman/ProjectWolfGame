#include <algorithm>
#include <assert.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <exception>
#include <iostream>
#include "Map.h"
#include "MapManager.h"
#include "utils.h"
#include "Create.h"
#include "Create_Enums.h"
#include "File.h"

MapManager::MapManager(): map(nullptr) {}

void MapManager::closeMap() {
  delete map;
  map = nullptr;
}

void MapManager::openMap(int mapNum) {
  using namespace Maps;
  Map* loadMap = Create::newMap(mapNum);
  setMap( loadMap );
}

void MapManager::setMap(Maps::Map* map) {
  if (this->map != nullptr) {
    delete map;
  }
  this->map = map;
}

void MapManager::play() {
  assert( map != nullptr );
  while ( true ) // TODO: Make variable for this
  {
    map->activate();

    if (tempMap != nullptr) {
      std::swap(tempMap, map);
      delete tempMap;
      tempMap = nullptr;
    }
  }

}

void MapManager::save(const std::string &fileName) {
  assert(map != nullptr);
  map->save();
  File::save(fileName);
}

void MapManager::load(const std::string &fileName) {
  using namespace File;
  using namespace boost::property_tree;

  fs::fstream file;
  fs::path filePath = savePath;
  filePath /= fs::path{fileName};

  if (file.is_open()) { file.close(); }
  // make tree and load from file
  treeType loadTree;
  try {
    file.open( filePath, std::fstream::in );
    xml_parser::read_xml(file, loadTree, xml_parser::trim_whitespace);
  } catch (std::exception &e) {
    std::cerr << e.what();
  }

  auto it = loadTree.begin();
  while (it != loadTree.end()) {
    const std::string &key = it->first;
    const std::string &data = it->second.data();
    if (key == "Map") {
      delete tempMap; // just in case
      tempMap = Create::newMap(*it);
    }
    it++;
  }
  // tempMap and map are swapped automatically later.
}
