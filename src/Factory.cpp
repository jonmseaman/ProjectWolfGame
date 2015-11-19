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
// Tiles
#include "House_2Story.h"


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
    default:
      itemCreated = new Item{};
  }
  return itemCreated;
}

Actor* Factory::newActor(int actor) {
  Actor* actorCreated = nullptr;
  switch (actor) {
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
  return actorCreated;
}

Maps::Node* Factory::newNode(int node) {
  Maps::Node* nodeCreated = nullptr;
  switch (node) {
    //case ENodes::Default:
    //  break;
    default:
      nodeCreated = new Maps::Node{};
      break;

  }
  return nodeCreated;
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
