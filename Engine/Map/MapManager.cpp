#include <iostream>
#include <stdexcept>
#include <Creation/Create.h>
#include "Map.h"
#include "MapManager.h"

using namespace Engine;

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
  if (map == nullptr) {
    throw std::logic_error("play: no map is open");
  }
  while (true) {
    map->activate();

    if (tempMap != nullptr) {
      std::cout << "Switching maps... ";
      map = std::move(tempMap);
      std::cout << "Done.\n";
    }
  }
}

void MapManager::save(const std::string &fileName) {
  if (map == nullptr) {
    throw std::logic_error("save: no map is open");
  }
  map->save();
  File::save(fileName);
}

void MapManager::load(const std::string &fileName) {
    File::load(fileName);

    // tempMap and map are swapped automatically later.
    tempMap = Creation::Create::loadNewMap();
}
