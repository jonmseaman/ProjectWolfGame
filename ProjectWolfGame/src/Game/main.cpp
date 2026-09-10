import std;
import Engine;

/* rewrite 3 */
/// ProjectReWolf
/// A text-based RPG

int main() {
    MapManager &game = MapManager::getInstance();

    try {
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
    } catch (const InputClosed &) {
        // Ctrl-D, or piped input that ran out. Quit instead of waiting for input
        // that is never going to arrive.
        std::cout << "\nInput closed. Exiting.\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "\nThe game stopped: " << e.what() << std::endl;
        return 1;
    }
}
