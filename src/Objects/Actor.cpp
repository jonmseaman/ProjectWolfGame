#include <iostream>
#include <assert.h>
#include "Actor.h"
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

bool Actor::onInteractedWith() {
  return 0;
}


void Actor::takeTurn() {
  dLog << "Actor takes turn" << std::endl;
  if (targetPtr == nullptr || !targetPtr->getIsLiving()) {
    // TODO: Get a target
    if (targetPtr != nullptr) {
      onAttack();
    }
  } else if (targetPtr->getIsLiving()) {
    onAttack();
  }
}

/**
 * @return The direction that the actor should move
 */
int Actor::getMoveDir() {
  return moveDir;
}

void Actor::setCurrentNode(Maps::Node *node) {
  this->currentNode = node;
}

void Actor::setMoveDir(int dir) {
  moveDir = dir;
  setIsTurnUsed();
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
  if (!currentNode->getInventory().hasOpenSlot()) {
    inventory.deleteItem(slotIndex);
  } else {
    currentNode->getInventory().addItem(inventory.getItem(slotIndex));
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
