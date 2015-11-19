#include <assert.h>
#include "MapManager.h"
#include "utils.h"
#include "Factory.h"
// TODO: Add filesystem support. ie, support opening save files from a
// directory
MapManager::MapManager(): map(nullptr) {}

void MapManager::openMap(int map) {
  using namespace Maps;
  Map* loadMap{ nullptr };
  loadMap = Factory::newMap(map);
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
  }
}
