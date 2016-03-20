#include "GObjects\CenterTown.h"
#include "Create.h"
#include "Create_Enums.h"
#include "Actor.h"
class Engine::Maps::Node;
using namespace Engine::Maps;

CenterTown::CenterTown(): Map(CENTER_TOWN_WIDTH) {
  for (auto &i : grid ) { i = new Node; }
  setNode(1, 0, Create::newNode(NODE_HOUSE_2STORY));
  setNode(2, 0, Create::newNode(NODE_HOUSE_2STORY));
  buildMoveData();
  Actor* player = Create::newActor(ACTOR_PLAYER);
  player->inventory.addItem(Create::newItem(ITEM_BASIC_SWORD));
  player->inventory.addItem(Create::newItem(ITEM_HEALING_WAND));
  getNode(0,0)->addActor(player);
  getNode(0,1)->addActor(Create::newActor(ACTOR_RAT));
  getNode(0,1)->addActor(Create::newActor(ACTOR_RAT));
  getNode(0, 2)->addActor(Create::newActor(ACTOR_RAT));
  getNode(3,0)->addActor(Create::newActor(ACTOR_SWORDSMEN));
}
