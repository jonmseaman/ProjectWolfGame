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
    File::load(fileName);

    // tempMap and map are swapped automatically later.
    delete tempMap;
    tempMap = Create::loadNewMap();
}
