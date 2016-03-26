#ifndef CREATE_H
#define CREATE_H
#include <string>

#include "CreatableClassDeclarations.h"

namespace Creation {

class ENGINE_API Create {
public:
  // Creation functions

  // Methods for new saving / loading system
  static Engine::Entity::Item* loadNewItem();
  static Engine::Entity::Actor* loadNewActor();
  static Engine::Maps::Node* loadNewNode();
  static Engine::Maps::Map* loadNewMap();

  // Str map system
  static Engine::Entity::Item* newItem(const std::string&);
  static Engine::Entity::Actor* newActor(const std::string&);
  static Engine::Maps::Node* newNode(const std::string&);
  static Engine::Maps::Map* newMap(const std::string&);
};

}

#endif CREATE_H

