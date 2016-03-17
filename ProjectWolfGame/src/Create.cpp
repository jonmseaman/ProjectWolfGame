#include "Create.h"
#include "Create_Enums.h"
#include "Savable.h"

// Including files for use by factory
// Actors
#include "Objects\Player.h"
#include "GObjects\Rat.h"
#include "GObjects\Swordsmen.h"
// Maps
#include "GObjects\CenterTown.h"
// Objects
#include "GObjects\BasicSword.h"
#include "GObjects\HealingWand.h"
// Tiles
#include "GObjects\House_2Story.h"

Create::Create()
{
}


Create::~Create()
{
}

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

Maps::Node* Create::loadNewNode() {
  using namespace File;
  using namespace Maps;

  Savable::idType id = Savable::nextID("Node");
  Node* node = Create::newNode(id);

  node->load();

  return node;
}


Maps::Map* Create::loadNewMap() {
  using namespace File;
  using namespace Maps;

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

Maps::Node* Create::newNode(int node) {
  Maps::Node* nodeCreated = nullptr;
  switch (node) {
    case NODE_HOUSE_2STORY:
      nodeCreated = new House_2Story();
      break;
    case NODE_DEFAULT:
    default:
      nodeCreated = new Maps::Node{};
      break;
  }
  nodeCreated->setID(node);
  return nodeCreated;
}

Maps::Map* Create::newMap(int map) {
  Maps::Map* mapCreated = nullptr;
  switch (map) {
    case MAP_CENTER_TOWN:
      mapCreated = new CenterTown{};
      break;
    default:
      mapCreated = new Maps::Map{};
  }
  mapCreated->setID(map);
  return mapCreated;
}
