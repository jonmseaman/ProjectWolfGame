#include <iostream>
#include <assert.h>
#include "Actor.h"
#include "Dir.h"
#include "utils.h"
#include "dLog.h"

Actor::Actor(): isPlayer(false)
  , isTurnUsed(false)
  , moveDir(Maps::Dir::Stop) {
  dLog << "Actor ctor called" << std::endl;
}

Actor::~Actor() {
  dLog << "Actor dtor called" << std::endl;
}

void Actor::takeTurn() {
  dLog << "Actor takes turn" << std::endl;
  if (!hasValidTarget() || !targetPtr->getIsLiving()) {
    // TODO: Get a target
    if (hasValidTarget()) {
      onAttack();
    }
  } else if (targetPtr->getIsLiving()) {
    onAttack();
  }
}

int Actor::getMoveDir() {
  return moveDir;
}

void Actor::setCurrentNode(Maps::Node *node) {
  this->currentNode = node;
}

void Actor::setMoveDir(int dir) {
  assert(currentNode != nullptr);
  assert(0 <= dir && dir < Maps::numDirs);
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
  assert ( slotIndex >= 0 && slotIndex <= inventory.getSlots() );
  if (!currentNode->inventory.hasOpenSlot()) {
    inventory.deleteItem(slotIndex);
  } else {
    currentNode->inventory.addItem(inventory.getItem(slotIndex));
    inventory.removeItem( slotIndex );
  }
  return true;
}

void Actor::dropAllItems() {
  for (int i(0); i < inventory.getSlots(); i++ ) {
    dropItem(i);
  }
}

void Actor::endTurn() {
  setIsTurnUsed(true);
}

bool Actor::hasValidTarget() {
  bool targetValid = (targetPtr != nullptr)
    && (currentNode->contains(targetPtr));
  if (!targetValid) {
    // If the target is not valid, remove it.
    targetPtr = nullptr;
  }
  return targetValid;
}

void Actor::onAttack() // TODO: Update for stats class
{ // TODO: Update for weapons
  assert( targetPtr != nullptr );
  int damage = stats.getStrength();
  // damage += damage from weapon
  // TODO: Update this for items.
  // TODO: Update combat text
  // TODO: No weapon equipped --> fists
  std::cout << getName() << " swings for " << damage << ". " << std::endl;
  targetPtr->onDamage( damage );
}

void Actor::setTarget(Actor* actor) {
  targetPtr = actor;
}
