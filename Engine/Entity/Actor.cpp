#include <iostream>
#include <assert.h>
#include "Actor.h"
#include "Map/Dir.h"
#include "UI/Input.h"

using namespace Engine::Maps;

namespace Engine {
namespace Entity {

Actor::Actor() : isPlayer(false)
, isTurnUsed(false)
, moveDir(STOP) {}

Actor::~Actor() {}

void Actor::takeTurn() {
  bool shouldAttack = hasValidTarget() && targetPtr != this && targetPtr->getIsLiving();

  // Aggressive, attacks whatever isn't itself.
  if (!shouldAttack) {
    cycleTarget();
    shouldAttack = hasValidTarget() && targetPtr != this && targetPtr->getIsLiving();
  }
  if (shouldAttack) {
    onAttack();
  }
}

/**
* @usage Used by node to figure out which direction the
* actor should be moved.
* @return The direction that the actor should move
*/
int Actor::getMoveDir() {
  return moveDir;
}

void Actor::setCurrentNode(Node *node) {
  this->currentNode = node;
}

/**
* Tries to set movement for the actor.
* If it is possible to move in direction dir, then the turn is used.
* @pre 0 <= dir < NUM_DIRS
* @post Turn is used if it is possible to move in direction
* @post Actor will be set to move after turns
*/
void Actor::setMoveDir(int dir) {
  assert(currentNode != nullptr);
  assert(0 <= dir && dir < NUM_DIRS);
  moveDir = dir;
  if (currentNode->canMoveInDir(dir)) {
    setIsTurnUsed();
  }
}

void Actor::setIsTurnUsed(bool val) {
  this->isTurnUsed = val;
}

bool Actor::getIsTurnUsed() {
  return isTurnUsed;
}

bool Actor::getIsPlayer() {
  return isPlayer;
}

void Actor::onMove() {
  moveDir = 0; // Reset move dir.
  combatStop();
}

bool Actor::dropItem(int slotIndex) {
  assert(slotIndex >= 0 && slotIndex <= inventory.getSlots());
  if (!currentNode->inventory.hasOpenSlot()) {
    delete inventory.removeItem(slotIndex);
  } else {
    // Transfer item to node inventory.
    currentNode->inventory.addItem(inventory.removeItem(slotIndex));
  }
  return true;
}

void Actor::dropAllItems() {
  for (int i(0); i < inventory.getSlots(); i++) {
    dropItem(i);
  }
}

void Actor::endTurn() {
  setIsTurnUsed(true);
}

/**
* Checks to make sure that this has a valid target.<br>
* <b>Updates</b> targetPtr
* @return true if target is valid
*/
bool Actor::hasValidTarget() {
  bool targetValid = targetPtr != nullptr && currentNode->containsActor(targetPtr);
  if (!targetValid) {
    // If the target is not valid, remove it.
    targetPtr = nullptr;
  }
  return targetValid;
}

void Actor::onAttack() // TODO: Update for stats class
{ // TODO: Update for weapons
  assert(targetPtr != nullptr);
  int damage = stats.getStrength();
  // damage += damage from weapon
  // TODO: Update this for items.
  // TODO: Update combat text
  // TODO: No weapon equipped --> fists
  std::cout << getName() << " swings for " << damage << ". " << std::endl;
  targetPtr->onDamage(damage);
  setIsTurnUsed();
}

void Actor::setTarget(Actor* actor) {
  targetPtr = actor;
}

/**
* Cycles through targets in the node. If there is not an actor != this in
* the node, the target will be removed.
*/
void Actor::cycleTarget() {
  targetPtr = currentNode->getNextActor(targetPtr);
}

void Actor::save() {
  startSave("Actor");
  Creature::save();
  endSave();
}

void Actor::load() {
  startLoad("Actor");
  Creature::load();
  endLoad();
}

}
}
