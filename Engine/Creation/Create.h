#ifndef CREATE_H
#define CREATE_H
#include <string>
#include "CreatableClassDeclarations.h"

using namespace Engine::Entity;
using namespace Engine::Maps;

namespace Creation {

class Create {
public:
  Create();
  ~Create();

  // Creation functions

  // Methods for new saving / loading system
  static Engine::Entity::Item* loadNewItem();
  static Engine::Entity::Actor* loadNewActor();
  static Node* loadNewNode();
  static Map* loadNewMap();

  // Int id system
  static Engine::Entity::Item* newItem(int item);
  static Engine::Entity::Actor* newActor(int actor);
  static Node* newNode(int node);
  static Map* newMap(int map);

  // Str map system

  static Engine::Entity::Item* Item(const std::string&);
  static Engine::Entity::Actor* Actor(const std::string&);
  static Node* Node(const std::string&);
  static Map* Map(const std::string&);
};

}

#endif CREATE_H
