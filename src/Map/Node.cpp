#include <iostream>
#include <iomanip>
#include "Node.h"
#include "Actor.h"
#include "Player.h"
#include "Dir.h"
#include "utils.h"
#include "dLog.h"
#include <assert.h>
int Maps::Node::nodeCount = 1;
namespace Maps {
  Node::Node(): canMoveInDir{0,0,0,0,0,0,0}
    , inventory(Inventory{ "Location Inventory", 8 })
    , nodeLinks{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    , actorPtrList{}
    , name("Node") {
    dLog << "Maps::Node::Node() called, no def." << std::endl;
    name = "Node";
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
    moveActors();
  }

  void Node::showNavigationInfo() {
    bool noDirs{true};
    if ( canMoveInDir[Dir::North] && nodeLinks[Dir::North] != nullptr) {
      std::cout << std::setw(3) << std::right << Dir::North
      << ": " << "North to " << nodeLinks[Dir::North]->getName() << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::East] && nodeLinks[Dir::East] != nullptr) {
      std::cout << std::setw(3) << std::right << Dir::East
      << ": " << "East to " << nodeLinks[Dir::East]->getName() << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::West] && nodeLinks[Dir::West] != nullptr) {
      std::cout << std::setw(3) << std::right << Dir::West
      << ": " << "West to " << nodeLinks[Dir::West]->getName() << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::South] && nodeLinks[Dir::South] != nullptr) {
      std::cout << std::setw(3) << std::right << Dir::South
      << ": " << "South to " << nodeLinks[Dir::South]->getName() << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::Up] && nodeLinks[Dir::Up] != nullptr) {
      std::cout << std::setw(3) << std::right << Dir::Up
      << ": " << "Up to " << nodeLinks[Dir::Up]->getName() << std::endl;
      noDirs = false;
    }
    if (canMoveInDir[Dir::Down] && nodeLinks[Dir::Down] != nullptr) {
      std::cout << std::setw(3) << std::right << Dir::Down
      << ": " << "Down to " << nodeLinks[Dir::Down]->getName() << std::endl;
      noDirs = false;
    }
    if ( noDirs == true ) {
      std::cout << "You cannot leave this area." << std::endl;
    }
  }

  void Node::setNodeLink(int dir, bool moveInDir, Node* link) {
    this->nodeLinks[dir] = link;
	this->canMoveInDir[dir] = moveInDir;
    this->canMoveInDir[dir] = moveInDir;
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
		  if ( (dir != Maps::Stop) && (nodeLinks[dir] != nullptr) ) {
		    actor.onMove(); // Moving actor
		    actor.setCurrentNode(nodeLinks[dir]);
			auto actorToMove = it;
			it++;
			// Moves
			otherList.splice(otherList.begin(), actorPtrList, actorToMove);
		  }
		  else {
			  it++;
		  }
	}
  }

  std::string Node::getName() {
    return name;
  }

  void Node::showActors() {
    int i(0);
    for (std::list<Actor*>::iterator it = actorPtrList.begin(); it != actorPtrList.end(); ++it) {
      std::cout << std::setw(COLUMN_PADDING) << std::left << ++i << ": ";
        if (!(*it)->getIsLiving()) { std::cout << "<Dead> "; }
        std::cout << (*it)->getName() << " "
        << (*it)->stats.getHealth() << "/" << (*it)->stats.getMaxHealth() << std::endl;
    }
  }

  int Node::getNumActors() {
    return actorPtrList.size();
  }
}
