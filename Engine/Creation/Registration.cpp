#include <map>
#include <utility>
#include "Registration.h"
#include "CreateData.h"

namespace Creation {

extern CreateData createData;

Registration::Registration(const std::string & name, Engine::Entity::Item *(*c)()) {
  //CreateData::items.insert(std::make_pair(name, c));
  createData.items.insert(std::make_pair(name, c));
}

}
