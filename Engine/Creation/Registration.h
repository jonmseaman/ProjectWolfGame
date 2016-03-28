#pragma once
#include <string>
#include "CreatableClassDeclarations.h"

namespace Creation {

class ENGINE_API Registration {
public:
  Registration(const std::string& name, Engine::Entity::Item* (*c)());
};

}


