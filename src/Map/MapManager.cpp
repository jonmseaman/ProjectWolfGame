#include <assert.h>
#include "MapManager.h"
#include "MapEnum.h"
#include "utils.h"
#include "GameFiles.h"
// TODO: Add filesystem support. ie, support opening save files from a
// directory
MapManager::MapManager(): map(nullptr)
{}

void MapManager::openMap(MapType mapType)
{
  using namespace Maps;
  Map* loadMap{ nullptr };
  switch (mapType)
  {
    case DEFAULT :
      loadMap = new Map{};
      break;
    case CENTER_TOWN :
      loadMap = new CenterTown{};
      break;


  }
  setMap( loadMap );
}

void MapManager::setMap(Maps::Map* _map)
{
  if (map != nullptr)
  {
    delete map;
  }
  map = _map;
}

void MapManager::play()
{
  assert( map != nullptr );
  while ( true ) // TODO: Make variable for this
  {
    map->activate();
  }
}
