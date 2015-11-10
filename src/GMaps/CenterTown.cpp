#include "CenterTown.h"
#include "Rat.h"
#include "Swordsmen.h"
#include "Player.h"
#include "Item_BasicSword.h"

CenterTown::CenterTown(): Map(CENTER_TOWN_WIDTH)
{
  for (auto &i : grid ) { i = new Maps::Node; }
  buildMoveData();
  populate();
  Actor* player = new Player{};
  player->inventory.addItem(new Item_BasicSword);
  player->inventory.addItem(new Item_BasicSword);
  player->inventory.addItem(new Item_BasicSword);
  player->inventory.addItem(new Item_BasicSword);
  getNode(0,0)->addActor(player);
  getNode(0,1)->addActor(new Rat);
  getNode(0,1)->addActor(new Rat);
  getNode(0, 2)->addActor(new Swordsmen);
}
