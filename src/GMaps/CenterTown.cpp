#include "CenterTown.h"
#include "Rat.h"
#include "Swordsmen.h"

CenterTown::CenterTown(): Map(CENTER_TOWN_WIDTH)
{
  for (auto &i : grid ) { i = new Maps::Node; }
  buildMoveData();
  populate();
  addPlayer(0,0);
  getNode(0,1)->addActor(new Rat);
  getNode(0,1)->addActor(new Rat);
  getNode(1, 0)->addActor(new Swordsmen);
}
