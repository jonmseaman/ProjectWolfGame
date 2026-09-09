module;
#include "EngineMacros.h"

export module Engine:CreateData;

import std;
import :Fwd;

export class ENGINE_API CreateData {
public:
  // Map of Item names to item creation functions.
  static std::map<std::string, std::function<std::unique_ptr<Engine::Entity::Item>()>> items;
  // Map of Actor names to actor creation functions.
  static std::map<std::string, std::function<std::unique_ptr<Engine::Entity::Actor>()>> actors;
  // Map of Node names to node creation functions.
  static std::map<std::string, std::function<std::unique_ptr<Engine::Maps::Node>()>> nodes;
  // Map of Map names to maps creation functions.
  static std::map<std::string, std::function<std::unique_ptr<Engine::Maps::Map>()>> maps;
};
