#pragma once
#include <memory>
#include <string>
#include "CreatableClassDeclarations.h"
#include <Engine.h>
#include <Savable.h>

namespace Creation {

class ENGINE_API Registration {
public:
  Registration(const std::string& name, std::unique_ptr<Engine::Entity::Item> (*c)());
  Registration(const std::string& name, std::unique_ptr<Engine::Entity::Actor> (*c)());
  Registration(const std::string& name, std::unique_ptr<Engine::Maps::Node> (*c)());
  Registration(const std::string& name, std::unique_ptr<Engine::Maps::Map> (*c)());
};

}


