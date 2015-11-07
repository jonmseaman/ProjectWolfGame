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

bool Actor::takeTurn()
{
  dLog << "Actor takes turn" << std::endl;
  if ( targetPtr == nullptr ) { actorPData->giveTarget(this); }
  if ( targetPtr->getIsLiving() ) // Only attack if the target is not dead
  {
    onAttack();
  }
  else
  {
    actorPData->giveTarget(this);
  }
  return 0;
}

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
