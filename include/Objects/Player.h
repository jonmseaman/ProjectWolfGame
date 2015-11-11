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
  protected:
    /**
     * This menu should allow access to all things that the player needs
     * during combat.
     */
    void combatMenu(int choice = 0); // Menu for attacking enemies
    /**
     * Converts a char of wasdqe to the corresponding travel direction
     */
    int charToDir(char charDir);
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
     */
    void onMove();
    /**
     * Allows inventory management. Allows using, showing information about
     * and dropping the item.
     */
    void inventoryMenu(Inventory &inv);
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
  private:
};

#endif // PLAYER_H
