#include <map>
#include <utility>
#include "Registration.h"
#include "CreateData.h"

namespace Creation {

extern CreateData createData;

Registration::Registration(const std::string& name, std::function<std::unique_ptr<Engine::Entity::Item>()> c) {
  createData.items.insert(std::make_pair(name, std::move(c)));
}

Registration::Registration(const std::string& name, std::function<std::unique_ptr<Engine::Entity::Actor>()> c) {
  createData.actors.insert(std::make_pair(name, std::move(c)));
}

Registration::Registration(const std::string& name, std::function<std::unique_ptr<Engine::Maps::Node>()> c) {
  createData.nodes.insert(std::make_pair(name, std::move(c)));
}

Registration::Registration(const std::string& name, std::function<std::unique_ptr<Engine::Maps::Map>()> c) {
  createData.maps.insert(std::make_pair(name, std::move(c)));
}



}
