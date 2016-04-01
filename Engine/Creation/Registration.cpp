#include <map>
#include <utility>
#include "Registration.h"
#include "CreateData.h"

namespace Creation {

extern CreateData createData;

Registration::Registration(const std::string & name, Engine::Entity::Item *(*c)()) {
  createData.items.insert(std::make_pair(name, c));
}

Registration::Registration(const std::string & name, Engine::Entity::Actor *(*c)()) {
  createData.actors.insert(std::make_pair(name, c));
}

Registration::Registration(const std::string & name, Engine::Maps::Node *(*c)()) {
  createData.nodes.insert(std::make_pair(name, c));
}

Registration::Registration(const std::string & name, Engine::Maps::Map *(*c)()) {
  createData.maps.insert(std::make_pair(name, c));
}



}
