#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include <string>
#include "Savable.h"
namespace Engine {
  namespace Maps { class Map; }
}

using namespace Engine;

/**
 * The purpose of this class is to make it easier to manager maps.
 * Eventually, MapManager will be able to handle multiple open maps and
 * connect them together to make a seamless larger map.
 */
class MapManager
{
  public:
    /** Singleton */
    static MapManager& getInstance() {
      static MapManager instance;
      return instance;
    }
    /**
     * Deletes the map. Sets map to nullptr.
     */
    void closeMap();
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
    void save(const std::string &fileName = "save1");
    /**
     * Loads from file fileName
     * @pre fileName exists in File::savePath
     */
    void load(const std::string &fileName = "save1");
  protected:
  private:
    MapManager(MapManager const&);     // Don't Implement
    void operator=(MapManager const&); // Don't implement
    MapManager();
    Maps::Map* map;
    Maps::Map* tempMap;
    void setMap(Maps::Map* map);
};

#endif // MAPMANAGER_H
