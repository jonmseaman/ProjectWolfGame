#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include <string>
#include "Map.h"
#include "Factory.h"
#include "Factory_Enums.h"
/**
 * The purpose of this class is to make it easier to manager maps.
 * Eventually, MapManager will be able to handle multiple open maps and
 * connect them together to make a seamless larger map.
 */
class MapManager
{
  public:
    static MapManager& getInstance() {
      static MapManager instance;
      return instance;
    }
    /**
     * Deletes the map. Sets map to nullptr.
     */
    void closeMap();
    /**
     * Loads a map from the saves folder with name mapName
     */
    void openMap(std::string mapName);
    /**
     * Creates a new map corresponding to mapNum
     */
    void openMap(int mapNum);
    /**
     * Starts the game loop for the opened map.
     * @pre There is a map open. (map != nullptr)
     * @post The game loop will be started.
     */
    void play();
    /**
     * Saves your game in file fileName
     * @pre map != nullptr
     */
    void save(std::string fileName = "save1");
  protected:
  private:
    MapManager(MapManager const&);              // Don't Implement
    void operator=(MapManager const&); // Don't implement
    MapManager();
    Maps::Map* map;
    void setMap(Maps::Map* map);
};

#endif // MAPMANAGER_H
