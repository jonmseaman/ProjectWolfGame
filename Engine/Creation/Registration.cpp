import std;
#include "Registration.h"
#include "CreateData.h"

namespace Creation {

Registration::Registration(const std::string& name, std::function<std::unique_ptr<Engine::Entity::Item>()> c) {
  CreateData::items.insert(std::make_pair(name, std::move(c)));
}

Registration::Registration(const std::string& name, std::function<std::unique_ptr<Engine::Entity::Actor>()> c) {
  CreateData::actors.insert(std::make_pair(name, std::move(c)));
}

Registration::Registration(const std::string& name, std::function<std::unique_ptr<Engine::Maps::Node>()> c) {
  CreateData::nodes.insert(std::make_pair(name, std::move(c)));
}

Registration::Registration(const std::string& name, std::function<std::unique_ptr<Engine::Maps::Map>()> c) {
  CreateData::maps.insert(std::make_pair(name, std::move(c)));
}



}
