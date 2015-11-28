#include "Factory.h"
#include "Item.h"
#include "Inventory.h"
#include "Actor.h"
#include "Node.h"
#include "Map.h"
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
    case ITEM_DEFAULT:
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
    case NODE_DEFAULT:
    default:
      nodeCreated = new Maps::Node{};
      break;
  }
  nodeCreated->setID(node);
  return nodeCreated;
}

Maps::Node* Factory::newNode(pairType node) {
  Maps::Node* nodeCreated = nullptr;

  treeType &tree = node.second;
  // get id
  auto it = tree.find("id");
  int id = 0;
  if (it != tree.not_found()) {
    id = std::stoi(it->second.data());
  }
  nodeCreated = newNode(id);
  nodeCreated->fromXML(node);
  return nodeCreated;
}

Maps::Map* Factory::newMap(int map) {
  Maps::Map* mapCreated = nullptr;
  switch (map) {
    case MAP_CENTER_TOWN:
      mapCreated = new CenterTown{};
      break;
  }
  mapCreated->setID(map);
  return mapCreated;
}

Maps::Map* Factory::newMap(pairType map) {
  Maps::Map* mapCreated = nullptr;

  treeType &tree = map.second;
  // get id
  auto it = tree.find("id");
  int id = 0;
  if (it != tree.not_found()) {
    id = std::stoi(it->second.data());
  }
  mapCreated = newMap(id);
  mapCreated->fromXML(map);
  return mapCreated;
}

Actor* Factory::getPlayer() {
  if (playerPtr == nullptr) {
    playerPtr = new Player{};
    playerPtr->setID(ACTOR_PLAYER);
  }
  return playerPtr;
}
