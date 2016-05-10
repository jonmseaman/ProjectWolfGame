#include <algorithm>
#include <assert.h>
#include <exception>
#include <iostream>
#include <Creation/Create.h>
#include "Map.h"
#include "MapManager.h"

MapManager::MapManager(): map(nullptr) {}

void MapManager::closeMap() {
  delete map;
  map = nullptr;
}

void MapManager::openMap(const std::string& map) {
  using namespace Maps;
  Map* loadMap = Creation::Create::newMap(map);
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
      std::cout << "Switching maps... ";
      std::swap(tempMap, map);
      delete tempMap;
      tempMap = nullptr;
      std::cout << "Done.\n";
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
    tempMap = Creation::Create::loadNewMap();
}
