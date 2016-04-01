#include <assert.h>
#include <iostream>
#include <string>
#include <Creation/Creatable.h>
#include "Map/Dir.h"
#include "Map/MapManager.h"
#include "Player.h"
#include <UI/Input.h>


namespace Engine {
namespace Entity {

CREATABLE_REGISTRATION(Player);

Player::Player() {
  setMaxHealth(100);
  setName("Jon");
  stats = Stats{ 5,5,5 };
  inventory = Inventory{ "Jon's Inventory", 8 };
  isPlayer = true;
}

Player::~Player() {}

void Player::combatMenu(int choice) {
  if (choice == 0) {
    dispList("====Combat====", { "Attack", "Targets", "Inventory" });
    choice = getDigit(0, 3);
  }
  switch (choice) {
    case 0:
      flagInCombat(false);
      break;
    case 1:
      processUserInput(' '); // Attack key
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
  setIsTurnUsed(false);
  if (getIsLiving()) {
    while (!getIsTurnUsed() && getIsLiving()) {
      takeTurnMenu();
    }
    if (getIsTurnUsed()) {
      std::cout << getName() << " has ended their turn." << std::endl;
    }
  } else {
    std::cout << getName() << " is dead. Continue?\n";
    char choice = getInput();
    if (choice == '0' || choice == 'n' || choice == 'N') {
      std::exit(0); // TODO: Make a global variable wanting to quit
    }
  }
}

void Player::takeTurnMenu() {
  showHUD();
  //int choice(0);
  char choice = '0';
  dispList("==============", { "Move", "Combat", "Targets", "Inventory", "Search" });
  choice = getInput(PROCESSABLE_INPUT);
  if (!processUserInput(choice)) {
    exitMenu();
  }
}

void Player::moveMenu(int dir) {
  assert(currentNode != nullptr);
  if (dir == 0) {
    std::cout << "=====Move=====" << std::endl;
    // Show choices
    currentNode->showNavigationInfo();
    // Get direction
    std::cout << "Enter direction: ";
    dir = getDigit(0, Maps::NUM_DIRS - 1);
  }
  // TODO: Make sure that the player enters a possible direction

  // set flags. Movedir && turnUsed
  if (dir != 0 && currentNode->canMoveInDir(dir)) {
    setMoveDir(dir);
  } else {
    std::cout << "Can't move in that direction." << std::endl;
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
  if (hasValidTarget()) {
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
  inv.showListOfItems();
  // Let player choose item
  std::cout << "Select an item: ";
  int itemIndex = getInteger(0, inv.getSlots());
  itemIndex--;

  if (itemIndex >= 0) {
    // Get the item,
    Item *item = inventory.at(itemIndex);
    // Show them menu for that item.
    dispList({ "Use","Examine", "Drop" });
    int actionNumber = getDigit(0, 3);
    switch (actionNumber) {
      case 1: // Use
        //item->onUse(this); // TODO: fixme. onUse --> useOn
        if (hasValidTarget()) {
          item->use(*this, *targetPtr);
        } else {
          std::cout << "You don't have a target." << std::endl;
        }
        endTurn();
        break;
      case 2: // Examine
        item->showInfo();
        break;
      case 3:
        std::cout << "Dropping item.\n";
        dropItem(itemIndex);
        break;
      default:
        break;
    }
  }
}

void Player::loadMenu() {
  std::string fileName;
  std::cout << "Load file name: ";
  std::cin >> fileName;
  std::cout << "Loading...";
  MapManager::getInstance().load(fileName);
  setIsTurnUsed();
  std::cout << " Done." << std::endl;
}

void Player::searchMenu(Inventory &inv) {
ITEM_SELECT:
  inv.showListOfItems();
  int choice = getInteger(0, inv.getSlots());
  int itemIndex = choice - 1;
  if (choice == 0) { return; } // Exit menu
  dispList({ "Pick up", "Examine" });
  choice = getInteger(0, 2);
  switch (choice) {
    case 0: // Cancel menu
      goto ITEM_SELECT;
      return;
    case 1: // Add item to player's inventory
      if (inv.isSlotEmpty(itemIndex)) {
        std::cout << "That slot is empty. Could not pick up item." << std::endl;
      } else if (!inventory.hasOpenSlot()) {
        std::cout << "Your inventory is full." << std::endl;
      } else
        if (inventory.addItem(inv.at(itemIndex))) {
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

bool Player::processUserInput(char key) {
  bool inputProcessed = true;
  switch (key) {
    // Menus
    case '`':
      takeTurnMenu();
      break;
    case '1':
      moveMenu();
      break;
    case '2':
      combatMenu();
      break;
    case '3':
      targetMenu();
      break;
    case '4':
    case 'i':
      inventoryMenu(inventory);
      break;
    case '5':
      searchMenu(currentNode->inventory);
      break;
      // Movement
    case 'w':
    case 'a':
    case 's':
    case 'd':
    case 'q':
    case 'e':
      setMoveDir(Maps::charToDir(key));
      break;
      // Attack
    case ' ':
      if (hasValidTarget()) {
        onAttack();
      } else {
        std::cout << "You don't have a target." << std::endl;
      }
      break;
    case 't':
      cycleTarget();
      break;
    case '\r':
      setIsTurnUsed();
      break;
    case '\x3f': // F5
      saveMenu();
      break;
    case '\x43': // F9
      loadMenu();
      break;
    default:
      inputProcessed = false;
      break;
  } // End switch for input processing
  return inputProcessed;
}

void Player::exitMenu() {
  std::cout << "Press 1 to exit, or something else to continue." << std::endl;
  char choice = getInput();
  if (choice == '1') {
    kill();
    std::exit(0);
  }
}

void Player::saveMenu() {
  std::string fileName;
  std::cout << "Save file name: ";
  std::cin >> fileName;
  std::cout << "Saving...";
  MapManager::getInstance().save(fileName);
  std::cout << " Done." << std::endl;
}


}
}

//TODO: Equipment menu
