#pragma once
#include <map>
#include "CreatableClassDeclarations.h"

class CreateData {
public:
  // Map of Item names to item creation functions.
  static std::map<std::string, Engine::Entity::Item* (*)()> items;
  // Map of Actor names to actor creation functions.
  static std::map<std::string, Engine::Entity::Actor*> actors;
  // Map of Node names to node creation functions.
  static std::map<std::string, Engine::Maps::Node* (*)()> nodes;
  // Map of Map names to maps creation functions.
  static std::map<std::string, Engine::Maps::Map* (*)()> maps;
};
