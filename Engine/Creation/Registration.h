#pragma once
#include <string>
#include "CreatableClassDeclarations.h"

namespace Creation {

class Registration {
public:
  Registration(const std::string& name, Engine::Entity::Item* (*c)());
};

}


