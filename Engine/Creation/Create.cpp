#include "Create.h"
#include "CreateData.h"
#include "Savable.h"

#include <Entity/Item.h>
#include <Entity/Player.h>
#include <Entity/Actor.h>
#include <Map/Node.h>
#include <Map/Map.h>


#pragma region Create

using namespace File;
using namespace Engine::Entity;
using namespace Engine::Maps;

namespace Creation {

// Methods for new loading / saving system

Item* Create::loadNewItem() {
  using namespace ::Engine::Entity;
  // get id and create object with appropriate dynamic type
  Savable::idType id = File::Savable::nextID("Item");
  Item* item = Create::newItem(id);

  // load data from save
  item->load();

  return item;
}

Actor* Create::loadNewActor() {
  Savable::idType id = File::Savable::nextID("Actor");
  Actor* actor = Create::newActor(id);

  actor->load();

  return actor;
}

Node* Create::loadNewNode() {
  Savable::idType id = Savable::nextID("Node");
  Node* node = Create::newNode(id);

  node->load();

  return node;
}


Map* Create::loadNewMap() {
  Savable::idType id = Savable::nextID("Map");
  Map* map = Create::newMap(id);

  map->load();
  return map;
}

Engine::Entity::Item * Create::newItem(const std::string &id) {
  return CreateData::items.at(id)();
}

Engine::Entity::Actor * Create::newActor(const std::string &id) {
  return CreateData::actors.at(id)();
}

Engine::Maps::Node * Create::newNode(const std::string &id) {
  return CreateData::nodes.at(id)();
}

Engine::Maps::Map * Create::newMap(const std::string &id) {
  return CreateData::maps.at(id)();
}

} // End namespace Creation

#pragma endregion
