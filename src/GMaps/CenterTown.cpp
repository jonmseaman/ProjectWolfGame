#include "CenterTown.h"
#include "Factory.h"
#include "Item.h"
#include "Inventory.h"
#include "Actor.h"
#include "Node.h"

CenterTown::CenterTown(): Map(CENTER_TOWN_WIDTH) {
  for (auto &i : grid ) { i = new Maps::Node; }
  setNode(1, 0, Factory::newNode(NODE_HOUSE_2STORY));
  setNode(2, 0, Factory::newNode(NODE_HOUSE_2STORY));
  buildMoveData();
  Actor* player = Factory::newActor(ACTOR_PLAYER);
  player->inventory.addItem(Factory::newItem(ITEM_BASIC_SWORD));
  player->inventory.addItem(Factory::newItem(ITEM_HEALING_WAND));
  getNode(0,0)->addActor(player);
  getNode(0,1)->addActor(Factory::newActor(ACTOR_RAT));
  getNode(0,1)->addActor(Factory::newActor(ACTOR_RAT));
  getNode(0, 2)->addActor(Factory::newActor(ACTOR_RAT));
  getNode(3,0)->addActor(Factory::newActor(ACTOR_SWORDSMEN));
}
