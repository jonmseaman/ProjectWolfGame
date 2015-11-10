#include <iostream>
#include <assert.h>
#include "Actor.h"
#include "utils.h"
#include "dLog.h"

Actor::Actor(): isPlayer(false)
  , isTurnUsed(false)
  , moveDir(Maps::Dir::Stop)
  , actorPData(nullptr)
{
  dLog << "Actor ctor called" << std::endl;
}

Actor::~Actor()
{
  dLog << "Actor dtor called" << std::endl;
}

bool Actor::onInteractedWith()
{
  return 0;
}

/**
 * Allows the actor to take a turn. Default behavior is defined
 * for derived classes which do not override takeTurn()
 */
void Actor::takeTurn()
{
  dLog << "Actor takes turn" << std::endl;
  if (targetPtr == nullptr || !targetPtr->getIsLiving()) {
    actorPData->giveTarget(this);
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
int Actor::getMoveDir()
{
  return moveDir;
}

void Actor::setMoveData(Maps::NodeData* ptrMoveData)
{
  this->actorPData = ptrMoveData;
}

void Actor::flagForMove(int dir)
{
  moveDir = dir;
}

void Actor::flagTurnUsed()
{
  isTurnUsed = true;
}
void Actor::flagTurnUsed(bool val)
{
  this->isTurnUsed = val;
}

bool Actor::getIsTurnUsed()
{
  return isTurnUsed;
}

bool Actor::getIsPlayer()
{
  return isPlayer;
}

void Actor::onMove()
{
  moveDir = 0; // Reset move dir.
  combatStop();
}

bool Actor::dropItem(int slotIndex)
{
  assert ( slotIndex >= 0 && slotIndex <= inventory.getSlots() );
  if (!actorPData->getInventory()->hasOpenSlot())
  {
    inventory.deleteItem(slotIndex);
  }
  else
  {
    actorPData->getInventory()->addItem( inventory.getItem(slotIndex) );
    inventory.removeItem( slotIndex );
  }
  return true;
}

void Actor::dropAllItems()
{
  for (int i(0); i < inventory.getSlots(); i++ )
  {
    dropItem(i);
  }
}

void Actor::onEndTurn()
{
  flagTurnUsed(true);
}
