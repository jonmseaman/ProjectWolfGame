#include <algorithm>
#include <assert.h>
#include <exception>
#include <iostream>
#include <Creation/Create.h>
#include "Map.h"
#include "MapManager.h"

MapManager::MapManager() {}

void MapManager::closeMap() {
  map.reset();
}

void MapManager::openMap(const std::string& mapName) {
  setMap(Creation::Create::newMap(mapName));
}

void MapManager::setMap(std::unique_ptr<Maps::Map> newMap) {
  map = std::move(newMap);
}

void MapManager::play() {
  assert( map != nullptr );
  while ( true ) // TODO: Make variable for this
  {
    map->activate();

    if (tempMap != nullptr) {
      std::cout << "Switching maps... ";
      map = std::move(tempMap);  // old map destroyed, tempMap becomes null
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
    tempMap = Creation::Create::loadNewMap();
}
