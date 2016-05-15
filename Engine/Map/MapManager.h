#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include <Engine.h>
#include <string>
#include "Savable.h"
namespace Engine {
  namespace Maps { class Map; }
}

using namespace Engine;

/**
 * The purpose of this class is to make it easier to manager maps.
 */
class ENGINE_API MapManager
{
  public:
    /** Singleton */
    static MapManager& getInstance() {
      static MapManager instance;
      return instance;
    }
    void closeMap();
    void openMap(const std::string&);
    void play();
    void save(const std::string &fileName = "save1");
    void load(const std::string &fileName = "save1");
  protected:
  private:
    MapManager(MapManager const&) = delete;
    void operator=(MapManager const&) = delete;
    MapManager();
    Maps::Map* map;
    Maps::Map* tempMap;
    void setMap(Maps::Map* map);
};

#endif // MAPMANAGER_H
