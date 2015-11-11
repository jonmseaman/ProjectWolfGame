#include "CenterTown.h"
#include "Rat.h"
#include "Swordsmen.h"
#include "Player.h"
#include "BasicSword.h"
#include "House_2Story.h"

CenterTown::CenterTown(): Map(CENTER_TOWN_WIDTH) {
  for (auto &i : grid ) { i = new Maps::Node; }
  setNode(1, 0, new House_2Story{});
  buildMoveData();
  Actor* player = new Player{};
  player->inventory.addItem(new BasicSword);
  player->inventory.addItem(new BasicSword);
  player->inventory.addItem(new BasicSword);
  player->inventory.addItem(new BasicSword);
  getNode(0,0)->addActor(player);
  getNode(0,1)->addActor(new Rat);
  getNode(0,1)->addActor(new Rat);
  getNode(0, 2)->addActor(new Swordsmen);
}
