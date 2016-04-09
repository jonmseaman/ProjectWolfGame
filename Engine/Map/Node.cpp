#include <assert.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <Creation/Create.h>
#include <Entity/Actor.h>
#include <UI/Input.h>
#include "Dir.h"
#include "Node.h"

using namespace Engine::Maps;
using namespace Engine::Entity;

int Node::nodeCount = 1;
namespace Engine {
namespace Maps {
  Node::Node(): inventory(Inventory{ "Location Inventory", 8 })
    , nodeLinks{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    , actorPtrList{}
    , name("Node") {
    for (int i = 0; i < Maps::NUM_DIRS; i++) {
      entranceDirs[i] = true;
    }
    entranceDirs[Dir::DOWN] = false; // Entrances in all dirs != down
    name += std::to_string(nodeCount);
    nodeCount++;
  }

  Node::~Node() {
    // Delete all the actors
    for (auto it = actorPtrList.begin(); it != actorPtrList.end(); ++it ) {
      delete (*it);
    }
  }

  Actor* Node::getActorPtr( int index ) {
    assert(0 <= index && index <= actorPtrList.size());
    auto it = actorPtrList.begin();
    if ( index >= actorPtrList.size() ) {
      index = actorPtrList.size();
    }
    std::advance(it, index);
    return *it;
  }

  void Node::activate() {
    for (auto it = actorPtrList.begin(); it != actorPtrList.end(); ++it ) { // Going through list of actors
      if ( (*it)->getIsLiving() || (*it)->getIsPlayer() ) // getIsPlayer() allows special behavior for players
      {
        (*it)->takeTurn();
      }
      else // If it is dead and not the player, we want to drop its inventory to the node
      {
        // Drop inventory
        (*it)->dropAllItems();
      }
    }
    moveActors(); // TODO: The map should call this after activating all nodes in map
  }

  void Node::showNavigationInfo() {
    bool noDirs{true};

    // Show navigation info for all directions.
    for (int i = 1; i < NUM_DIRS; i++) {
      if (entranceDirs[i] && nodeLinks[i] != nullptr) {
        showNavigationInfoForNode(i);
        std::cout << std::endl;
        noDirs = false;
      }
    }

    if (noDirs) {
      std::cout << "You cannot leave this area." << std::endl;
    }
  }

  void Node::showNavigationInfoForNode(int dir) {
    assert(0 < dir && dir < NUM_DIRS);
    std::cout << std::setw(COLUMN_PADDING) << std::right << dir << ": ";
    std::cout << Maps::dirName(dir) << " to " << nodeLinks[dir]->getName();
    // Check to see if the node can accept entry from this direction
    bool canGoInDir = nodeLinks[dir]->getEntranceDir(oppositeDir(dir));
    if (!canGoInDir) {
      std::cout << " <Inaccessible>";
    }
  }

  void Node::setNodeLink(int dir, Node* link) {
    this->nodeLinks[dir] = link;
  }

  void Node::addActor(Actor *actor) {
    actor->setCurrentNode(this);
    actorPtrList.insert(actorPtrList.end(), actor);
  }

  void Node::moveActors() {
  auto it = actorPtrList.begin();
  while (it != actorPtrList.end()) {
      Actor &actor = **it;
      int dir = actor.getMoveDir();
      std::list<Actor*> &otherList = nodeLinks[dir]->actorPtrList;
      // TODO: Make canMoveInDir(DIR) function
      if ((dir != Maps::STOP) && (nodeLinks[dir] != nullptr) && !nodeLinks[dir]->isWall()) {
        actor.onMove(); // Moving actor
        actor.setCurrentNode(nodeLinks[dir]);
      auto actorToMove = it;
      it++;
      // Moves
      otherList.splice(otherList.begin(), actorPtrList, actorToMove);
      } else {
        it++;
      }
  }
  }

  std::string Node::getName() {
    return name;
  }

  void Node::showActors() {
    int i(0);
    for (auto it = actorPtrList.begin(); it != actorPtrList.end(); ++it) {
      // Number the list
      std::cout << std::setw(COLUMN_PADDING) << std::left << ++i << ": ";
      // Display information about the creature.
      (*it)->displayHUDLine();
      std::cout << std::endl;
    }
  }

  int Node::getNumActors() {
    return actorPtrList.size();
  }

  void Node::setEntranceDir(int dir, bool isEntrance) {
    assert(0 <= dir && dir < Maps::NUM_DIRS);
    entranceDirs[dir] = isEntrance;
  }

  bool Node::canMoveInDir(int dir) {
    assert(0 <= dir < NUM_DIRS);
    bool nodeInDirExists = nodeLinks[dir] != nullptr;
    bool entrancesExist = false;
    if (nodeInDirExists) {
      entrancesExist = getEntranceDir(dir) &&
        nodeLinks[dir]->getEntranceDir(Maps::oppositeDir(dir));
    }

    return entrancesExist;
  }

   bool Node::getEntranceDir(int dir) {
     assert(0 <= dir < NUM_DIRS);
     return entranceDirs[dir];
   }

   bool Node::containsActor(Actor* actor) {
     bool actorFound = false;
     for (auto i = actorPtrList.begin();
      i != actorPtrList.end() && !actorFound; i++) {
        actorFound = actor == *i;
     }
     return actorFound;
   }

   Actor* Node::getNextActor(Actor* actor) {
     assert(actorPtrList.size() > 0);
     Actor* nextActor = nullptr;
     bool actorFound = false;

     // If the actorPtrList is of size one, return actor
     actorFound = actorPtrList.size() == 1;

     // Iterate to actor
     auto i = actorPtrList.begin();
     while (i != actorPtrList.end() && !actorFound && (actor != nullptr)) {
       actorFound = *i == actor;
       i++;
     }
     nextActor = i == actorPtrList.end() ? *actorPtrList.begin() : *i;

     return nextActor;
   }

   void Node::save()
   {
     startSave("Node");
     // entrance dirs?
     // TODO: toString for an array or vector
     SAVE(name);
     int numActors = getNumActors();
     SAVE(numActors);
     for (Actor* a : actorPtrList) {
       a->save();
     }

     // TODO: Entrance dirs

     
     endSave();
   }

   void Node::load()
   {
     startLoad("Node");
     LOAD(name);
     // Figure out how many actors were saved.
     int numActors = 0;
     LOAD(numActors);

     for (int i = 0; i < numActors; i++) {
       Creation::Create::loadNewActor();
     }
     
     for (int i = 0; i < NUM_DIRS; i++) {
         // LOAD(entranceDirs[i]);
         // TODO: Entrance dirs
     }


     endLoad();
   }
}
}
