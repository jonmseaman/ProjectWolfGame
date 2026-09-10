export module Engine:MapManager;

import std;
import :Map;

/**
 * The purpose of this class is to make it easier to manage maps.
 * Eventually, MapManager will be able to handle multiple open maps and
 * connect them together to make a seamless larger map.
 */
export class MapManager {
public:
    /** Singleton */
    static MapManager &getInstance() {
        static MapManager instance;
        return instance;
    }

    /** Deletes the map. Sets map to nullptr. */
    void closeMap();

    /** Creates a new map corresponding to the given name. */
    void openMap(const std::string &);

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

private:
    MapManager(MapManager const &) = delete;

    void operator=(MapManager const &) = delete;

    MapManager();

    std::unique_ptr<Engine::Maps::Map> map;
    std::unique_ptr<Engine::Maps::Map> tempMap;

    void setMap(std::unique_ptr<Engine::Maps::Map> map);
};
