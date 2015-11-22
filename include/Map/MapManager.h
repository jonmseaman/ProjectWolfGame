#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include <string>
#include "Map.h"
#include "Factory.h"
#include "Factory_Enums.h"

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
    void openMap(int mapNum);
    /**
     * Starts the game loop for the opened map.
     * @pre There is a map open. (map != nullptr)
     * @post The game loop will be started.
     */
    void play();
  protected:
  private:
    Maps::Map* map;
    void setMap(Maps::Map* map);
};

#endif // MAPMANAGER_H
