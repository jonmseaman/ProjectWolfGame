#pragma once
#include <string>
#include "CreatableClassDeclarations.h"

using namespace Engine::Entity;
using namespace Engine::Maps;

namespace Create {

class Registration {
public:
  Registration(const std::string& name, Item* (*c)());
};

}
