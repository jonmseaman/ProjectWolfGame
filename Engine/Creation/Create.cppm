export module Engine:Create;

import std;
import :Fwd;

export namespace Creation {

class Create {
public:
  // Methods for the loading / saving system
  static std::unique_ptr<Engine::Entity::Item> loadNewItem();
  static std::unique_ptr<Engine::Entity::Actor> loadNewActor();
  static std::unique_ptr<Engine::Maps::Node> loadNewNode();
  static std::unique_ptr<Engine::Maps::Map> loadNewMap();

  // Creation by registered id
  static std::unique_ptr<Engine::Entity::Item> newItem(const std::string&);
  static std::unique_ptr<Engine::Entity::Actor> newActor(const std::string&);
  static std::unique_ptr<Engine::Maps::Node> newNode(const std::string&);
  static std::unique_ptr<Engine::Maps::Map> newMap(const std::string&);
};

}
