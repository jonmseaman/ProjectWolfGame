#include <iostream>
#include <assert.h>
#include "Player.h"
#include "utils.h"
#include "dLog.h"

Player::Player()
{
  setMaxHealth(100);
  setStrength(10);
  setName("Jon");
  isPlayer = true;
}

Player::~Player()
{
  //dtor
}

void Player::combatMenu()
{
  dispList({"Attack", "Targets", "Inventory"});
  int choice = getInteger(0,3);
  switch (choice)
  {
  case 0:
    flagInCombat(false);
    break;
  case 1:
    onAttack();
    flagTurnUsed(true);
    break;
  case 2:
    targetMenu();
    break;
  case 3:
    inventoryMenu(inventory);
    break;
  default:
    std::cout << "No menu item " << choice << ".\n";
    break;
  }
}
bool Player::takeTurn()
{
  flagTurnUsed(false);
  if ( getIsLiving() )
  {
    while ( !getIsTurnUsed() && getIsLiving() )
    {
      takeTurnMenu();
    }
    if (getIsTurnUsed())
    { // Don't display the turn end text when we don't actually take
      // the turn.
      std::cout << getName() << " has ended their turn." << std::endl;
    }
  }
  else
  {
    std::cout << getName() << " is dead. Continue? ";
    int choice = getInteger();
    if ( choice == 0 )
    {
      std::exit(1);
    }
  }
  return true;
}

void Player::takeTurnMenu()
{
  START:
  showHUD();
  int choice(0);
  if ( getIsInCombat() )
  {
    choice = 2; // Defaults to combat menu
  }
  else
  {
    dispList({"Move", "Combat", "Targets", "Inventory", "Search"});
    choice = getInteger(0,5);
  }
  switch (choice)
  {
  case 0:
    std::cout << "Are you sure you want to exit? [0, 1]" << std::endl;
    choice = getInteger(0,1);
    if ( choice == 0 )
    { goto START; }
    kill();
    std::exit(0);
    break;
  case 1 :
    moveMenu();
    break;
  case 2 :
    combatMenu();
    break;
  case 3:
    targetMenu();
    break;
  case 4:
    inventoryMenu(inventory);
    break;
  case 5:
    searchMenu(*(actorPData->getInventory()));
    break;
  default:
    std::cout << "Could not find menu item " << choice << std::endl;
    break;
  }
}

void Player::moveMenu()
{
  // Show choices
  actorPData->showData();
  // Get direction
  std::cout << "Enter direction: ";
  int dir = getInteger(0,Maps::numDirs-1);
  // TODO: Make sure that the player enters a possible direction
  dLog << "Player entered " << dir << " for Player::moveMenu() choice" << std::endl;
  // set flags. Movedir && turnUsed
  if ( dir != 0 )
  {
    flagForMove( dir );
    flagTurnUsed(true);
  }
}

void Player::onMove()
{
  Actor::onMove();
  std::cout << "You leave" << std::endl;
}

void Player::targetMenu()
{
  actorPData->showActors();
  int choice = getInteger();
  if (choice==0)
  { setTarget(nullptr);
    return; }
  setTarget(actorPData->getActorPtr(--choice));
}

void Player::showHUD()
{
  //TODO: Update this to show equipped weapons
  if ( !this->getIsLiving() ) { std::cout << "<Dead> "; }
  std::cout << getName() << ": " << stats.getHealth() << "/" << stats.getMaxHealth() << std::endl;
  if (targetPtr != nullptr)
  {
    if ( !targetPtr->getIsLiving() ) { std::cout << "<Dead> "; }
    std::cout << targetPtr->getName() << ": " << targetPtr->stats.getHealth()
    << "/" << targetPtr->stats.getMaxHealth() << std::endl;
  }
  else
  {
    std::cout << "No target" << std::endl;
  }
}

void Player::inventoryMenu(Inventory &inv)
{
  // Show inventory
    inv.show();
  // Let player choose item
    std::cout << "Select an item: ";
    int itemNumber = getInteger(0, inv.getSlots());
    if ( itemNumber == 0 ) return;
  // Let player choose action for item
    dispList({"Use","Examine", "Drop"});
    int actionNumber = getInteger(0,3);
    switch (actionNumber)
    {
    case 0:
      return;
    case 1: // Use
      if (inv.useItem(--itemNumber, this)) // -- because this function takes the index
      {
        onEndTurn();
      }
      else
      {
        std::cout << "Couldn't use item. \n";
      }
      break;
    case 2: // Examine
      std::cout << "No Implement. item number: " << itemNumber << std::endl;
      break;
    case 3:
      std::cout << "Dropping item.\n";
      dropItem(itemNumber-1);
      break;
    default:
      std::cout << "No case for action " << actionNumber << " for item " << itemNumber << std::endl;
      break;
    }
}

void Player::searchMenu(Inventory &inv)
{
  ITEM_SELECT:
  inv.show();
  int choice = getInteger(0, inv.getSlots());
  int itemIndex = choice-1;
  if (choice == 0) { return; }
  dispList({"Pick up", "Examine"});
  choice = getInteger(0, 2);
  switch (choice)
  {
  case 0: // Cancel menu
    goto ITEM_SELECT;
    return;
  case 1:
    // Add item to player's inventory
    if ( inventory.addItem( inv.getItem(itemIndex) ) )
    {
      std::cout << "Trying to remove item. Choice: " << choice << std::endl;
      inv.removeItem(itemIndex);
    }
    else
    {
      std::cout << "Could not pick up item.\n";
    }
    break;
  case 2:
    // Show item stats, description
    // TODO: Implement items stats, description
    break;
  default:
    std::cout << "Invalid choice " << choice << std::endl;
    break;
  }
}

//TODO: Equipment menu
