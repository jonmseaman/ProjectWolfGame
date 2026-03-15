/* rewrite 3 */
/// ProjectReWolf
/// A text-based RPG
#include <iostream>
#include <Map/MapManager.h>
#include <UI/Input.h>

int main() {
  MapManager& game = MapManager::getInstance();

  while (true) {
    dispList("WolfGame", {"New Game", "Exit"});
    int choice = getDigit(1, 2);
    switch (choice) {
      case 1: // New Game
        game.openMap("CenterTown");
        game.play();
        break;
      case 2: // Exit
        std::cout << "Exiting.\n";
        return 0;
    }
  }
}
