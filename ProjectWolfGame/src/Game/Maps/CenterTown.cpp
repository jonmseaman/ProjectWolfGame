#include <Map/Map.h>
#include <Creation/Create.h>
#include <Entity/Actor.h>

class Engine::Maps::Node;

using namespace Engine::Maps;
using namespace Engine::Entity;
using namespace Creation;

const int CENTER_TOWN_WIDTH{ 5 };

class CenterTown : public Map {
public:
  CREATABLE_MAP(CenterTown)
  CenterTown() : Map(CENTER_TOWN_WIDTH) {
    for (auto &i : grid) { i = new Node; }
    //setNode(1, 0, Create::newNode("House_2Story"));
    //setNode(2, 0, Create::newNode("House_2Story"));
    buildMoveData();
    Actor* player = Create::newActor("Player");
    player->inventory.addItem(Create::newItem("BasicSword"));
    player->inventory.addItem(Create::newItem("HealingWand"));
    getNode(0, 0)->addActor(player);
    getNode(0, 1)->addActor(Create::newActor("Rat"));
    getNode(0, 1)->addActor(Create::newActor("Rat"));
    getNode(0, 2)->addActor(Create::newActor("Rat"));
    getNode(3, 0)->addActor(Create::newActor("Swordsmen"));
  }
};

CREATABLE_REGISTRATION(CenterTown);
