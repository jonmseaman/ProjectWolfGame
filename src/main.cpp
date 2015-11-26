/* rewrite 3 */
/// ProjectReWolf
/// A text-based RPG
#include <iostream>
#include "MapManager.h"
#include "utils.h"
#include "dLog.h"
#include "File.h"
using namespace std;

int main() {
  dLog.open("DebugLog.txt", std::fstream::out);
  MapManager &game = MapManager::getInstance();
  int choice;

  mainMenu:
  dispList("WolfGame", {"New Game", "Load*", "Options*", "Exit"});
  choice = getDigit(1, 4);
  switch (choice) {
    case 1: // New Game
      game.openMap(EMaps::MAP_CENTER_TOWN); // Opens town
      game.play(); // starts playing
      break;
    case 2: // Load
      // Load a map
      //game.play()
      break;
    case 3: // Options
      break;
    case 4: // Exit
      std::cout << "Exiting." << std::endl;
      break;
    default:
      std::cout << "Input " << choice << " is not a menu item." << std::endl;
      goto mainMenu;
      break;
  }

  dLog.close();
  return 0;
}
