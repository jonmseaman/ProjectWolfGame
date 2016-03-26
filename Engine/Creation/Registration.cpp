#include <utility>
#include "Registration.h"
#include "CreateData.h"

namespace Creation {

Registration::Registration(const std::string & name, Engine::Entity::Item *(*c)()) {
  CreateData::items.insert(std::make_pair(name, c));
}

}
