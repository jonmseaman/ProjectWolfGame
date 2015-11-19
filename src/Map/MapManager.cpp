#include <assert.h>
#include "MapManager.h"
#include "utils.h"
#include "Factory.h"
// TODO: Add filesystem support. ie, support opening save files from a
// directory
MapManager::MapManager(): map(nullptr) {}

void MapManager::openMap(int mapNum) {
  using namespace Maps;
  Map* loadMap = Factory::newMap(mapNum);
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
  }
}
