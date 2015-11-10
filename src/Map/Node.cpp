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
namespace Maps
{
  Node::Node(): inventory(new Inventory{ "Location Inventory", 8 })
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
    for (std::list<Actor*>::iterator it = actorPtrList.begin(); it != actorPtrList.end(); ++it ) { // This loop deletes all actors
      dLog << "Deleting actor: " << (*it) << " from actor list in node: " << name << std::endl;
      delete (*it);
    }
    delete inventory; // Delete inventory
  }

  Actor* Node::getActorPtr( int index ) {
    assert ( ((index) <= actorPtrList.size()) && (index >= 0) );
    std::list<Actor*>::iterator it = actorPtrList.begin();
    if ( index >= actorPtrList.size() ) {
      index = actorPtrList.size();
    }
    std::advance(it, index);
    return *it;
  }

  void Node::activate() {
    dLog << "Node: " << name << " activated" << std::endl;
    for (std::list<Actor*>::iterator it = actorPtrList.begin(); it != actorPtrList.end(); ++it ) { // Going through list of actors
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
    if ( canMoveInDir[Dir::North] ) {
      std::cout << std::setw(3) << std::right << Dir::North
      << ": " << "North to " << arrMoveText[Dir::North] << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::East] ) {
      std::cout << std::setw(3) << std::right << Dir::East
      << ": " << "East to " << arrMoveText[Dir::East] << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::West] ) {
      std::cout << std::setw(3) << std::right << Dir::West
      << ": " << "West to " << arrMoveText[Dir::West] << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::South] ) {
      std::cout << std::setw(3) << std::right << Dir::South
      << ": " << "South to " << arrMoveText[Dir::South] << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::Up] ) {
      std::cout << std::setw(3) << std::right << Dir::Up
      << ": " << "Up to " << arrMoveText[Dir::Up] << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::Down] ) {
      std::cout << std::setw(3) << std::right << Dir::Down
      << ": " << "Down to " << arrMoveText[Dir::Down] << std::endl;
      noDirs = false;
    }
    if ( noDirs == true ) {
      std::cout << arrMoveText[Dir::Stop] << std::endl;
    }
  }

  bool Node::addActor(Actor *actor) {
    actorPtrList.insert(actorPtrList.end(), actor);
    // Set move data for added actor
    (*(--actorPtrList.end() ))->setMoveData(this);
    return true;
  }

  void Node::moveActors(\)\s\{
	auto it = actorPtrList.begin();
	while (it != actorPtrList.end()) {
		  Actor &actor = **it;
		  int dir = actor.getMoveDir();
		  std::list<Actor*> &otherList = nodeLinks[dir]->actorPtrList;
		  // TODO: Make canMoveInDir(DIR) function
		  if ( (dir != Maps::Stop) && (nodeLinks[dir] != nullptr) ) {
		    actor.onMove(); // Moving actor
		    actor.setMoveData(nodeLinks[dir]);
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

  void Node::setNodeLink(int dir, Node* node) {
    nodeLinks[dir] = node;
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

  void Node::giveTarget(Creature *creature) { // TODO: Update this. We want actors to be able to search the list of
    // TODO: and decide what kind of target they want
    // if there is only one creature in the node, just give the creature a null target
    if ( actorPtrList.size() == 1 ) {
      creature->setTarget(nullptr);
      return;
    }
    for (auto it = actorPtrList.begin(); it != actorPtrList.end(); ++it ) {
      // Make sure we don't give the creature itself as a target
      if ( (*it) != creature ) {
        creature->setTarget((*it));
        return;
      }
    }
  }

  Inventory* Node::getInventory() {
    assert(inventory != nullptr);
    return inventory;
  }
}
