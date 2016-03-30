#pragma once
#include <string>
#include "CreatableClassDeclarations.h"

namespace Creation {

class ENGINE_API Registration {
public:
  Registration(const std::string& name, Engine::Entity::Item* (*c)());
  Registration(const std::string& name, Engine::Entity::Actor* (*c)());
  Registration(const std::string& name, Engine::Maps::Node* (*c)());
  Registration(const std::string& name, Engine::Maps::Map* (*c)());
};

}


