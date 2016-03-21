#include "Create.h"
#include "Create_Enums.h"
#include "Savable.h"

#include <Entity/Actor.h>
#include <Entity/Player.h>
#include <Map/Node.h>
#include <Map/Map.h>

#pragma region CreateData
#include <map>

class CreateData {
public:
  // Map of item names to items.
  static std::map<std::string, Item*> items;
  // Map of item names to items.
  static std::map<std::string, Node*> nodes;
  // Map of item names to items.
  static std::map<std::string, Actor*> actors;
  // Maps not include due to size.
};

#pragma endregion



using namespace File;
using namespace Engine::Maps;

Create::Create() {}


Create::~Create() {}

// Methods for new loading / saving system

Item* Create::loadNewItem() {
  // get id and create object with appropriate dynamic type
  File::Savable::idType id = File::Savable::nextID("Item");
  Item* item = Create::newItem(id);

  // load data from save
  item->load();

  return item;
}

Actor* Create::loadNewActor() {
  File::Savable::idType id = File::Savable::nextID("Actor");
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

Item* Create::newItem(int item) {
  Item* itemCreated = nullptr;
  switch (item) {
    case ITEM_BASIC_SWORD:
      itemCreated = new BasicSword{};
      break;
    case ITEM_HEALING_WAND:
      itemCreated = new HealingWand{};
      break;
    case ITEM_DEFAULT:
    default:
      itemCreated = new Item{};
      break;
  }
  itemCreated->setID(item);
  return itemCreated;
}

Actor* Create::newActor(int actor) {
  Actor* actorCreated = nullptr;
  switch (actor) {
    case ACTOR_PLAYER:
      // TODO: Proper singleton for player
      actorCreated = new Player{};
      break;
    case ACTOR_RAT:
      actorCreated = new Rat{};
      break;
    case ACTOR_SWORDSMEN:
      actorCreated = new Swordsmen{};
      break;
    case ACTOR_DEFAULT:
    default:
      actorCreated = new Actor{};
      break;
  }
  actorCreated->setID(actor);
  return actorCreated;
}

Node* Create::newNode(int node) {
  Node* nodeCreated = nullptr;
  switch (node) {
    case NODE_HOUSE_2STORY:
      nodeCreated = new House_2Story();
      break;
    case NODE_DEFAULT:
    default:
      nodeCreated = new Node{};
      break;
  }
  nodeCreated->setID(node);
  return nodeCreated;
}

Map* Create::newMap(int map) {
  Map* mapCreated = nullptr;
  switch (map) {
    case MAP_CENTER_TOWN:
      mapCreated = new CenterTown{};
      break;
    default:
      mapCreated = new Map{};
  }
  mapCreated->setID(map);
  return mapCreated;
}

Item * Create::Item(std::string name) {
  // Find the item in the map.
  auto it = CreateData::items.find(name);
  Item* item = nullptr;
  if (it != CreateData::items.end()) {
    item = it->second;
  }
  // Return a copy of the item.

  return &(*item);
}

Actor * Create::Actor(std::string name) {
  return nullptr;
}

Node * Create::Node(std::string name) {
  return nullptr;
}

Map * Create::Map(std::string name) {
  return nullptr;
}
