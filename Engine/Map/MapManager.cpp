#include <algorithm>
#include <assert.h>
#include <exception>
#include <iostream>
#include <Creation/Create.h>
#include "Map.h"
#include "MapManager.h"

MapManager::MapManager(): map(nullptr) {}
/**
* Deletes the map. Sets map to nullptr.
*/
void MapManager::closeMap() {
  delete map;
  map = nullptr;
}
/**
* Creates a new map using Create.
*/
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
/**
* Starts the game loop for the opened map.
* @pre There is a map open. (map != nullptr)
* @post The game loop will be started.
*/
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
/**
* Saves your game in file fileName
* @pre map != nullptr
*/
void MapManager::save(const std::string &fileName) {
  assert(map != nullptr);
  map->save();
  File::save(fileName);
}
/**
* Loads from file fileName
* @pre fileName exists in File::savePath
*/
void MapManager::load(const std::string &fileName) {
    File::load(fileName);

    // tempMap and map are swapped automatically later.
    delete tempMap;
    tempMap = Creation::Create::loadNewMap();
}
