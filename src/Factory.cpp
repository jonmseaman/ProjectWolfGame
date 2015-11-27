#include "Factory.h"
// Including files for use by factory
// Actors
#include "Player.h"
#include "Rat.h"
#include "Swordsmen.h"
// Maps
#include "CenterTown.h"
// Objects
#include "BasicSword.h"
#include "HealingWand.h"
// Tiles
#include "House_2Story.h"

// Static Initialization
Actor *Factory::playerPtr = nullptr;

Factory::Factory()
{
}


Factory::~Factory()
{
}

Item* Factory::newItem(int item) {
  Item* itemCreated = nullptr;
  switch (item) {
    case ITEM_BASIC_SWORD:
      itemCreated = new BasicSword{};
      break;
    case ITEM_HEALING_WAND:
      itemCreated = new HealingWand{};
      break;
    default:
      itemCreated = new Item{};
      break;
  }
  itemCreated->setID(item);
  return itemCreated;
}

Item* Factory::newItem(pairType item) {
  Item* itemCreated = nullptr;
  treeType &tree = item.second;
  // get id
  auto it = tree.find("id");
  int id = 0;
  if (it != tree.not_found()) {
    id = std::stoi(it->second.data());
  }
  itemCreated = newItem(id);
  itemCreated->fromXML(item);
  return itemCreated;
}

Actor* Factory::newActor(int actor) {
  Actor* actorCreated = nullptr;
  switch (actor) {
    case ACTOR_PLAYER:
      // TODO: Proper singleton for player
      actorCreated = getPlayer();
    case ACTOR_RAT:
      actorCreated = new Rat{};
      break;
    case ACTOR_SWORDSMEN:
      actorCreated = new Swordsmen{};
      break;
    default:
      actorCreated = new Actor{};
      break;
  }
  actorCreated->setID(actor);
  return actorCreated;
}

Actor* Factory::newActor(pairType actor) {
  Actor* actorCreated = nullptr;
  // get id
  treeType &tree = actor.second;
  int id = 0;
  auto it = tree.find("id");
  if (it != tree.not_found()) {
    id = std::stoi(it->second.data());
  }
  actorCreated = newActor(id);
  actorCreated->fromXML(actor);
  return actorCreated;
}

Maps::Node* Factory::newNode(int node) {
  Maps::Node* nodeCreated = nullptr;
  switch (node) {
    case NODE_HOUSE_2STORY:
      nodeCreated = new House_2Story();
      break;
    default:
      nodeCreated = new Maps::Node{};
      break;

  }
  nodeCreated->setID(node);
  return nodeCreated;
}

Maps::Node* Factory::newNode(pairType node) {
  return nullptr; // TODO: Loading
}

Maps::Map* Factory::newMap(int map) {
  Maps::Map* mapCreated = nullptr;
  switch (map) {
    case MAP_CENTER_TOWN:
      mapCreated = new CenterTown{};
      break;
  }
  return mapCreated;
}

Maps::Map* Factory::newMap(pairType map) {
  return nullptr; // TODO: Loading
}

Actor* Factory::getPlayer() {
  if (playerPtr == nullptr) {
    playerPtr = new Player{};
    playerPtr->setID(ACTOR_PLAYER);
  }
  return playerPtr;
}
