#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"

class Player : public Actor
{
  public:
    Player();
    virtual ~Player();

    /**
     * Shows the player's HUD.
     * Name, HP/MaxHP
     * Target name, hp, MaxHP
     * Current Location
     */
    void showHUD();
    /**
     * Allows the actor to take a turn. Default behavior is defined
     * for derived classes which do not override takeTurn()
     */
    void takeTurn();

	const std::string PROCESSABLE_INPUT = "wasdqe it012345`\r\x3f"; // \r is return
  protected:
    /**
     * This menu should allow access to all things that the player needs
     * during combat.
     */
    void combatMenu(int choice = 0); // Menu for attacking enemies
    /**
     * The moveMenu for the player. Allows the player to move to different
     * nodes.
     * @param dir If called with a non-zero dir, the player will move in
     * that direction without having to enter a direction.
     */
    void moveMenu(int dir = 0);
    /**
     * Displays a message about the player leaving.
     * Also, see Actor::onMove()
     * @pre currentNode != nullptr
     */
    void onMove();
    /**
     * Allows inventory management. Allows using, showing information about
     * and dropping the item.
     */
    void inventoryMenu(Inventory &inv);
    void saveMenu();
    /**
     * Allows interactions with inventory other than the actor's own.
     * Allows items to be moved to the player's inventory.
     */
    void searchMenu(Inventory &inv);
    /**
     * The menu opened when the player takes a turn. Allows access to other
     * menus. Alows keyboard input.
     */
    void takeTurnMenu();
    /**
     * This menu allows selection of targets.
     */
    void targetMenu();
    /**
     * This function runs a command corresponding to user input.
     * If key is not a valid input
     * @param key The button that the user pressed.
     * @return Returns true if key had a corresponding command that was runs,
     * false if there was not a corresponding command.
     */
    bool processUserInput(char key);
    /**
     * Menu for exiting the game. Asks the user to press 0 to exit.
     */
    void exitMenu();
  private:
};

#endif // PLAYER_H
