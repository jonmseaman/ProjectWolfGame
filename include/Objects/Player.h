#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"


class Player : public Actor
{
  public:
    Player();
    virtual ~Player();
    void showHUD(); // Shows information on the player and the player's target
    void takeTurn();
  protected:
    void combatMenu(int choice = 0); // Menu for attacking enemies
    int charToDir(char charDir);
    void moveMenu(int dir = 0); // Menu for entering and leaving nodes
    void onMove(); // Whatever happens when the player moves
    void inventoryMenu(Inventory &inv); // Menu for interacting with an inventory. Used for node inventory, player's inventory
    void searchMenu(Inventory &inv); // Menu for interacting with the node's inventory
    void takeTurnMenu(); // Menu for taking one's turn
    void targetMenu(); // Menu for selecting new targets
  private:
};

#endif // PLAYER_H
