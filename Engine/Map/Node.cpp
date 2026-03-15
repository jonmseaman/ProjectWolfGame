#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <Creation/Create.h>
#include <Creation/Creatable.h>
#include <Entity/Actor.h>
#include <UI/Input.h>
#include "Dir.h"
#include "Node.h"

using namespace Engine::Maps;
using namespace Engine::Entity;
using enum Engine::Maps::Dir;


std::atomic<int> Node::nodeCount = 1;
namespace Engine {
namespace Maps {

  // Special registration for default node. Allows creation with empty string or 'Node'.
  Creation::Registration __registrationNodeEmptyString("", []() -> std::unique_ptr<Node> { return std::make_unique<Node>(); });
  Creation::Registration __registrationNode("Node", []() -> std::unique_ptr<Node> { return std::make_unique<Node>(); });

  Node::Node(): inventory(Inventory{ "Location Inventory", 8 })
    , nodeLinks{}
    , actorPtrs{}
    , name("Node") {
    entranceDirs.fill(true);
    entranceDirs[dir_idx(DOWN)] = false; // Entrances in all dirs except DOWN
    name += std::to_string(nodeCount++);
  }

  Node::~Node() {}

  void Node::clearSavable() {
    // Node links and entrance dirs
    nodeLinks.fill(nullptr);
    actorPtrs.clear();
    inventory.clearSavable();
  }

  Actor* Node::getActorPtr( int index ) {
    if (index < 0 || static_cast<std::size_t>(index) > actorPtrs.size()) {
      throw std::out_of_range("getActorPtr: index out of range");
    }
    auto it = actorPtrs.begin();
    if ( static_cast<std::size_t>(index) >= actorPtrs.size() ) {
      index = static_cast<int>(actorPtrs.size());
    }
    std::advance(it, index);
    return it->get();
  }

  void Node::activate() {
    for (auto it = actorPtrs.begin(); it != actorPtrs.end(); ++it ) { // Going through list of actors
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

    for (int i = 1; i < NUM_DIRS; i++) {
      Dir d = static_cast<Dir>(i);
      if (entranceDirs[dir_idx(d)] && nodeLinks[dir_idx(d)] != nullptr) {
        showNavigationInfoForNode(d);
        std::cout << std::endl;
        noDirs = false;
      }
    }

    if (noDirs) {
      std::cout << "You cannot leave this area." << std::endl;
    }
  }

  void Node::showNavigationInfoForNode(Dir dir) {
    std::cout << std::setw(COLUMN_PADDING) << std::right << static_cast<int>(dir) << ": ";
    std::cout << Maps::dirName(dir) << " to " << nodeLinks[dir_idx(dir)]->getName();
    bool canGoInDir = nodeLinks[dir_idx(dir)]->getEntranceDir(oppositeDir(dir));
    if (!canGoInDir) {
      std::cout << " <Inaccessible>";
    }
  }

  void Node::setNodeLink(Dir dir, Node* link) {
    nodeLinks[dir_idx(dir)] = link;
  }

  void Node::addActor(std::unique_ptr<Actor> actor) {
    actor->setCurrentNode(this);
    actorPtrs.insert(actorPtrs.end(), std::move(actor));
  }

  void Node::moveActors() {
    auto it = actorPtrs.begin();
    while (it != actorPtrs.end()) {
      Actor& actor = **it;
      Dir dir = actor.getMoveDir();
      std::size_t idx = dir_idx(dir);
      if ((dir != STOP) && (nodeLinks[idx] != nullptr) && !nodeLinks[idx]->isWall()) {
        actor.onMove();
        actor.setCurrentNode(nodeLinks[idx]);
        auto actorToMove = it++;
        nodeLinks[idx]->actorPtrs.splice(nodeLinks[idx]->actorPtrs.begin(), actorPtrs, actorToMove);
      } else {
        ++it;
      }
    }
  }

  std::string Node::getName() const {
    return name;
  }

  void Node::showActors() {
    int i(0);
    for (auto it = actorPtrs.begin(); it != actorPtrs.end(); ++it) {
      // Number the list
      std::cout << std::setw(COLUMN_PADDING) << std::left << ++i << ": ";
      // Display information about the creature.
      (*it)->displayHUDLine();
      std::cout << std::endl;
    }
  }

  int Node::getNumActors() const {
    return static_cast<int>(actorPtrs.size());
  }

  void Node::setEntranceDir(Dir dir, bool isEntrance) {
    entranceDirs[dir_idx(dir)] = isEntrance;
  }

  bool Node::canMoveInDir(Dir dir) const {
    std::size_t idx = dir_idx(dir);
    if (nodeLinks[idx] == nullptr) return false;
    return getEntranceDir(dir) && nodeLinks[idx]->getEntranceDir(Maps::oppositeDir(dir));
  }

  bool Node::getEntranceDir(Dir dir) const {
    return entranceDirs[dir_idx(dir)];
  }

   bool Node::containsActor(Actor* actor) {
     return std::find_if(actorPtrs.begin(), actorPtrs.end(),
       [actor](const std::unique_ptr<Actor>& p) { return p.get() == actor; }) != actorPtrs.end();
   }

   Actor* Node::getNextActor(Actor* actor) {
     if (actorPtrs.empty()) {
       throw std::logic_error("getNextActor: node has no actors");
     }
     bool actorFound = false;

     // If the actorPtrs is of size one, return actor
     actorFound = actorPtrs.size() == 1;

     // Iterate to actor
     auto i = actorPtrs.begin();
     while (i != actorPtrs.end() && !actorFound && (actor != nullptr)) {
       actorFound = i->get() == actor;
       i++;
     }
     return i == actorPtrs.end() ? actorPtrs.begin()->get() : i->get();
   }

   void Node::save()
   {
     startSave("Node");
     // entrance dirs?
     // TODO: toString for an array or vector
     SAVE(name);
     int numActors = getNumActors();
     SAVE(numActors);
     for (const auto& a : actorPtrs) {
       a->save();
     }

     // TODO: Entrance dirs

     
     endSave();
   }

   void Node::load()
   {
     clearSavable();
     startLoad("Node");
     LOAD(name);
     // Figure out how many actors were saved.
     int numActors = 0;
     LOAD(numActors);
     for (int i = 0; i < numActors; i++) {
       this->addActor(Creation::Create::loadNewActor());  // unique_ptr passed directly
     }
     
     for (int i = 0; i < NUM_DIRS; i++) {
         // LOAD(entranceDirs[i]);
         // TODO: Entrance dirs
     }


     endLoad();
   }
}
}
