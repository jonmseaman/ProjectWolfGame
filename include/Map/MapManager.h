#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include <string>
#include "Map.h"
#include "MapEnum.h"

/* The purpose of this class is to make it easier to manager maps.
 * Eventually, MapManager will be able to handle multiple open maps and
 * connect them together to make a seamless larger map.
 */

class MapManager
{
  public:
    MapManager();
    void closeMap();
    void openMap(std::string mapName);
    void openMap(MapType mapType);
    void play(); // Starts game loop
  protected:
  private:
    Maps::Map* map;
    void setMap(Maps::Map* _map);
};

#endif // MAPMANAGER_H