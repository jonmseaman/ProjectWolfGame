#include <iostream>
#include <stdexcept>
#include "Actor.h"
#include "Map/Dir.h"
#include "UI/Input.h"

using namespace Engine::Maps;
using enum Engine::Maps::Dir;

namespace Engine {
namespace Entity {

Actor::Actor() : isPlayer(false)
, isTurnUsed(false)
, moveDir(Dir::STOP) {}

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

Dir Actor::getMoveDir() const {
  return moveDir;
}

void Actor::setCurrentNode(Node *node) {
  this->currentNode = node;
}

void Actor::setMoveDir(Dir dir) {
  if (currentNode == nullptr) {
    throw std::logic_error("setMoveDir: actor is not in a node");
  }
  moveDir = dir;
  if (currentNode->canMoveInDir(dir)) {
    setIsTurnUsed();
  }
}

void Actor::setIsTurnUsed(bool val) {
  this->isTurnUsed = val;
}

bool Actor::getIsTurnUsed() const {
  return isTurnUsed;
}

bool Actor::getIsPlayer() const {
  return isPlayer;
}

void Actor::onMove() {
  moveDir = STOP;
  combatStop();
}

bool Actor::dropItem(int slotIndex) {
  if (slotIndex < 0 || slotIndex >= inventory.getSlots()) {
    throw std::out_of_range("dropItem: slotIndex out of range");
  }
  if (!currentNode->inventory.hasOpenSlot()) {
    inventory.removeItem(slotIndex);  // unique_ptr out of scope, item destroyed
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

bool Actor::hasValidTarget() {
  bool targetValid = targetPtr != nullptr && currentNode->containsActor(targetPtr);
  if (!targetValid) {
    // If the target is not valid, remove it.
    targetPtr = nullptr;
  }
  return targetValid;
}

void Actor::onAttack() {
  if (targetPtr == nullptr) {
    throw std::logic_error("onAttack: no target set");
  }
  int damage = stats.getStrength();
  std::cout << getName() << " swings for " << damage << ". " << std::endl;
  targetPtr->onDamage(damage);
  setIsTurnUsed();
}

void Actor::setTarget(Actor* actor) {
  targetPtr = actor;
}

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
