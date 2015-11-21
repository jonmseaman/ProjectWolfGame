#include <assert.h>
#include <iomanip>
#include <iostream>
#include "Node.h"
#include "Actor.h"
#include "Player.h"
#include "Dir.h"
#include "utils.h"
#include "dLog.h"
int Maps::Node::nodeCount = 1;
namespace Maps {
  Node::Node(): inventory(Inventory{ "Location Inventory", 8 })
    , nodeLinks{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    , actorPtrList{}
    , name("Node") {
    for (int i = 0; i < Maps::numDirs; i++) {
      entranceDirs[i] = true;
    }
    entranceDirs[Dir::Down] = false; // Entrances in all dirs != down
    name += to_string(nodeCount);
    nodeCount++;
  }

  Node::~Node() {
    dLog << "Maps::Node::~Node() called for Node: " << name << std::endl;
	  // Delete all the actors
    for (auto it = actorPtrList.begin(); it != actorPtrList.end(); ++it ) {
      dLog << "Deleting actor: " << (*it) << " from actor list in node: " << name << std::endl;
      delete (*it);
    }
  }

  Actor* Node::getActorPtr( int index ) {
    assert ( ((index) <= actorPtrList.size()) && (index >= 0) );
    auto it = actorPtrList.begin();
    if ( index >= actorPtrList.size() ) {
      index = actorPtrList.size();
    }
    std::advance(it, index);
    return *it;
  }

  void Node::activate() {
    dLog << "Node: " << name << " activated" << std::endl;
    for (auto it = actorPtrList.begin(); it != actorPtrList.end(); ++it ) { // Going through list of actors
      dLog << "Taking turn for " << (*it)->getName() << std::endl;
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
    if (entranceDirs[Dir::North] && nodeLinks[Dir::North] != nullptr) {
      showNavigationInfoForNode(Dir::North);
      std::cout << std::endl;
      noDirs = false;
    }
    if (entranceDirs[Dir::East] && nodeLinks[Dir::East] != nullptr) {
      showNavigationInfoForNode(Dir::East);
      std::cout << std::endl;
      noDirs = false;
    }
    if (entranceDirs[Dir::West] && nodeLinks[Dir::West] != nullptr) {
      showNavigationInfoForNode(Dir::West);
      std::cout << std::endl;
      noDirs = false;
    }
    if (entranceDirs[Dir::South] && nodeLinks[Dir::South] != nullptr) {
      showNavigationInfoForNode(Dir::South);
      std::cout << std::endl;
      noDirs = false;
    }
    if (entranceDirs[Dir::Up] && nodeLinks[Dir::Up] != nullptr) {
      showNavigationInfoForNode(Dir::Up);
      std::cout << std::endl;
      noDirs = false;
    }
    if (entranceDirs[Dir::Down] && nodeLinks[Dir::Down] != nullptr) {
      showNavigationInfoForNode(Dir::Down);
	  std::cout << std::endl;
      noDirs = false;
    }
    if (noDirs == true) {
      std::cout << "You cannot leave this area." << std::endl;
    }
  }

  void Node::showNavigationInfoForNode(int dir) {
    assert(0 < dir && dir < numDirs);
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
    // Set move data for added actor
    // TODO: ?Need this? :(*(--actorPtrList.end() ))->setMoveData(this);
  }

  void Node::moveActors() {
	auto it = actorPtrList.begin();
	while (it != actorPtrList.end()) {
		  Actor &actor = **it;
		  int dir = actor.getMoveDir();
		  std::list<Actor*> &otherList = nodeLinks[dir]->actorPtrList;
		  // TODO: Make canMoveInDir(DIR) function
		  if ((dir != Maps::Stop) && (nodeLinks[dir] != nullptr) && !nodeLinks[dir]->isWall()) {
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

  /**
   * Allows setting entrance direction for nodes. Nodes can be entered and
   * exited from entrance directions.
   * @pre 0 < dir < Maps::numDirs
   * @post The node will have an entrance in dir if(isEntrance)
   */
  void Node::setEntranceDir(int dir, bool isEntrance) {
    assert(0 <= dir && dir < Maps::numDirs);
    entranceDirs[dir] = isEntrance;
  }

  bool Node::canMoveInDir(int dir) {
    assert(0 <= dir < numDirs);
    bool nodeInDirExists = nodeLinks[dir] != nullptr;
    bool entrancesExist = false;
    if (nodeInDirExists) {
      entrancesExist = getEntranceDir(dir) &&
        nodeLinks[dir]->getEntranceDir(Maps::oppositeDir(dir));
    }

    return entrancesExist;
  }

   bool Node::getEntranceDir(int dir) {
     assert(0 <= dir < numDirs);
     return entranceDirs[dir];
   }

   bool Node::contains(Actor* actor) {
     bool actorFound = false;
     for (auto i = actorPtrList.begin();
      i != actorPtrList.end() && !actorFound; i++) {
        actorFound = actor == *i;
     }
     return actorFound;
   }
}
