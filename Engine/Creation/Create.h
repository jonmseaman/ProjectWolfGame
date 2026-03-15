#ifndef CREATE_H
#define CREATE_H
#include <Engine.h>
#include <memory>
#include <string>

#include "CreatableClassDeclarations.h"

namespace Creation {

class ENGINE_API Create {
public:
  // Creation functions

  // Methods for new saving / loading system
  static std::unique_ptr<Engine::Entity::Item> loadNewItem();
  static std::unique_ptr<Engine::Entity::Actor> loadNewActor();
  static std::unique_ptr<Engine::Maps::Node> loadNewNode();
  static std::unique_ptr<Engine::Maps::Map> loadNewMap();

  // Str map system
  static std::unique_ptr<Engine::Entity::Item> newItem(const std::string&);
  static std::unique_ptr<Engine::Entity::Actor> newActor(const std::string&);
  static std::unique_ptr<Engine::Maps::Node> newNode(const std::string&);
  static std::unique_ptr<Engine::Maps::Map> newMap(const std::string&);
};

}

#endif CREATE_H

