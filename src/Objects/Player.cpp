#include <iostream>
#include <assert.h>
#include "Player.h"
#include "utils.h"
#include "dLog.h"

Player::Player() {
  setMaxHealth(100);
  setStrength(10);
  setName("Jon");
  inventory = Inventory{"Jon's Inventory", 10};
  isPlayer = true;
}

Player::~Player() {
}

void Player::combatMenu(int choice) {
  if (choice == 0) {
    dispList("====Combat====", {"Attack", "Targets", "Inventory"});
    choice = getDigit(0, 3);
  }
  //TODO: cout << "Moving " dir << endl;
  switch (choice) {
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

void Player::takeTurn() {
  flagTurnUsed(false);
  if (getIsLiving()) {
    while (!getIsTurnUsed() && getIsLiving()) {
      takeTurnMenu();
    }
    if (getIsTurnUsed()) {
      std::cout << getName() << " has ended their turn." << std::endl;
    }
  } else {
    std::cout << getName() << " is dead. Continue? ";
    int choice = getDigit();
    if (choice == 0) {
      std::exit(0);
    }
  }
}

void Player::takeTurnMenu() {
  START:
  showHUD();
  //int choice(0);
  char choice = '0';
  if (getIsInCombat()) {
    choice = '2'; // Defaults to combat menu
  } else {
    dispList("==============", {"Move", "Combat", "Targets", "Inventory", "Search"});
    choice = getInput("wasdqe 012345");
  }
  switch (choice) {
  case '0':
    std::cout << "Are you sure you want to exit? [0, 1]" << std::endl;
    choice = getDigit(0,1);
    if ( choice == 0 ) { goto START; }
    kill();
    std::exit(0);
    break;
  case '1' :
    moveMenu();
    break;
  case '2' :
    combatMenu();
    break;
  case '3':
    targetMenu();
    break;
  case '4':
    inventoryMenu(inventory);
    break;
  case '5':
    searchMenu(currentNode->getInventory());
    break;
  case 'w':
  case 'a':
  case 's':
  case 'd':
  case 'q':
  case 'e':
    moveMenu(Maps::wasdqeToDir(choice));
    break;
  case ' ':
    combatMenu(1); // TODO: Bad form, hardcoding
    break;
  default:
    std::cout << "Could not find menu item " << choice << std::endl;
    break;
  }
}

void Player::moveMenu(int dir) {
  if (dir == 0) {
    std::cout << "=====Move=====" << std::endl;
    // Show choices
    currentNode->showNavigationInfo();
    // Get direction
    std::cout << "Enter direction: ";
    dir = getDigit(0,Maps::numDirs-1);
  }
  // TODO: Make sure that the player enters a possible direction
  dLog << "Player entered " << dir << " for Player::moveMenu() choice" << std::endl;
  // set flags. Movedir && turnUsed
  if (dir != 0) {
    flagForMove(dir);
    flagTurnUsed(true);
  }
}

void Player::onMove() {
  Actor::onMove();
  std::cout << "You leave" << std::endl;
}

void Player::targetMenu() {
  currentNode->showActors();
  int choice = getInteger();
  if (choice == 0) {
    setTarget(nullptr);
  } else {
    setTarget(currentNode->getActorPtr(--choice));
  }
}

void Player::showHUD() {
  //TODO: Update this to show equipped weapons
  // Information on player
  displayHUDLine();
  std::cout << std::endl;
  // Information on target
  if (targetPtr != nullptr) {
    targetPtr->displayHUDLine();
    std::cout << std::endl;
  } else {
    std::cout << "No target" << std::endl;
  }
  // Location
  std::cout << "Location: " << currentNode->getName() << std::endl;
}

void Player::inventoryMenu(Inventory &inv) {
  // Show inventory
  inv.show();
  // Let player choose item
  std::cout << "Select an item: ";
  int itemIndex = getInteger(0, inv.getSlots());
	itemIndex--;
  // Let player choose action for item
  dispList({"Use","Examine", "Drop"});
  int actionNumber = getInteger(0,3);
  switch (actionNumber) {
    case 0:
      return;
      break;
    case 1: // Use
      if (inv.useItem(itemIndex, this)) {
        onEndTurn();
      } else {
        std::cout << "Couldn't use item. \n";
      }
      break;
    case 2: // Examine
      std::cout << "No Implement. item number: " << itemIndex << std::endl;
      break;
    case 3:
      std::cout << "Dropping item.\n";
      dropItem(itemIndex);
      break;
    default:
      std::cout << "No case for action " << actionNumber << " for item " << itemIndex << std::endl;
      break;
    }
}

void Player::searchMenu(Inventory &inv) {
  ITEM_SELECT:
  inv.show();
  int choice = getInteger(0, inv.getSlots());
  int itemIndex = choice-1;
  if (choice == 0) { return; } // Exit menu
  dispList({"Pick up", "Examine"});
  choice = getInteger(0, 2);
  switch (choice) {
  case 0: // Cancel menu
    goto ITEM_SELECT;
    return;
  case 1:
    // Add item to player's inventory
    if (inventory.addItem(inv.getItem(itemIndex))) {
      std::cout << "Trying to remove item. Choice: " << choice << std::endl;
      inv.removeItem(itemIndex);
    } else {
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
