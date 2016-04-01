/* rewrite 3 */
/// ProjectReWolf
/// A text-based RPG
#include <iostream>
#include <Engine.h>
#include <Map/MapManager.h>
#include <UI/Input.h>
using namespace std;

int main() {
  MapManager &game = MapManager::getInstance();
  int choice;

  mainMenu:
  dispList("WolfGame", {"New Game", "Exit"});
  choice = getDigit(1, 2);
  switch (choice) {
    case 1: // New Game
      game.openMap(EMaps::MAP_CENTER_TOWN); // Opens town
      game.play(); // starts playing
      break;
    case 2: // Exit
      std::cout << "Exiting." << std::endl;
      break;
    default:
      std::cout << "Input " << choice << " is not a menu item." << std::endl;
      goto mainMenu;
      break;
  }

  return 0;
}
