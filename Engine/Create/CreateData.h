#pragma once
#include <map>
#include "CreatableClassDeclarations.h"

class CreateData {
public:
  // Map of item names to items.
  static std::map<std::string, Entity::Item* (*)()> items;
  // Map of item names to items.
  static std::map<std::string, Node*> nodes;
  // Map of item names to items.
  static std::map<std::string, Entity::Actor*> actors;
  // TODO: Add maps
};
