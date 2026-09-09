module;
#include "EngineMacros.h"

export module Engine:Registration;

import std;
import :Fwd;

export namespace Creation {

class ENGINE_API Registration {
public:
  Registration(const std::string& name, std::function<std::unique_ptr<Engine::Entity::Item>()> c);
  Registration(const std::string& name, std::function<std::unique_ptr<Engine::Entity::Actor>()> c);
  Registration(const std::string& name, std::function<std::unique_ptr<Engine::Maps::Node>()> c);
  Registration(const std::string& name, std::function<std::unique_ptr<Engine::Maps::Map>()> c);
};

}
