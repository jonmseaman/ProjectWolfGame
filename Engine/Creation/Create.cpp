#include "Create.h"
#include "CreateData.h"
#include "Savable.h"

#include <Entity/Item.h>
#include <Entity/Actor.h>
#include <Map/Node.h>
#include <Map/Map.h>

#pragma region Create

using namespace File;
using namespace Engine::Entity;
using namespace Engine::Maps;

namespace Creation {

// Methods for new loading / saving system

std::unique_ptr<Item> Create::loadNewItem() {
  using namespace ::Engine::Entity;
  // get id and create object with appropriate dynamic type
  Savable::idType id = File::Savable::nextID("Item");
  auto item = Create::newItem(id);

  // load data from save
  item->load();

  return item;
}

std::unique_ptr<Actor> Create::loadNewActor() {
  Savable::idType id = File::Savable::nextID("Actor");
  auto actor = Create::newActor(id);

  actor->load();

  return actor;
}

std::unique_ptr<Node> Create::loadNewNode() {
  Savable::idType id = Savable::nextID("Node");
  auto node = Create::newNode(id);

  node->load();

  return node;
}

std::unique_ptr<Map> Create::loadNewMap() {
  Savable::idType id = Savable::nextID("Map");
  auto map = Create::newMap(id);

  map->load();
  return map;
}

std::unique_ptr<Engine::Entity::Item> Create::newItem(const std::string &id) {
  auto i = CreateData::items.at(id)();
  i->setID(id);
  return i;
}

std::unique_ptr<Engine::Entity::Actor> Create::newActor(const std::string &id) {
  auto a = CreateData::actors.at(id)();
  a->setID(id);
  return a;
}

std::unique_ptr<Engine::Maps::Node> Create::newNode(const std::string &id) {
  auto n = CreateData::nodes.at(id)();
  n->setID(id);
  return n;
}

std::unique_ptr<Engine::Maps::Map> Create::newMap(const std::string &id) {
  auto m = CreateData::maps.at(id)();
  m->setID(id);
  return m;
}

} // End namespace Creation

#pragma endregion
