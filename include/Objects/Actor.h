#ifndef ACTOR_H
#define ACTOR_H
#include "Dir.h"
#include "Creature.h"
#include "Node.h"


/**
 * The actor class is a creature which with behavior.
 * This should be generalized into Players, Mobs, Bosses etc
 */
class Actor : public Creature
{
  public:
    Actor();
    virtual ~Actor();

    bool dropItem(int slotNumber); // Drops item to node inventory. slotNumber is index+1 in inventory
    void dropAllItems(); // Drops all items in inventory to node inventory.
    virtual bool onInteractedWith(); // Allows the interaction
    virtual void takeTurn(); // Allows the player to take actions. Uses turn
    virtual void endTurn(); // Whatever needs to be done at the end of a turn. Default is flagging the turn as used.
    virtual void onMove(); // TODO: Moving should make other creatures stop targeting you.
    int getMoveDir();
    bool getIsTurnUsed();
    bool getIsPlayer();
    void setCurrentNode(Maps::Node *node);
  protected:
    /**
     * The node that the actor is currently in.
     * Used for movement, targetting, awareness...
     */
    Maps::Node *currentNode;
    // Tries to flag the actor for movement so that the map will move the
    // actor when it can
    void setMoveDir( int dir );
    void setIsTurnUsed(bool val = true);
    bool isPlayer = false;
  private:
    bool isTurnUsed; // Should stop allowing actions when this is true.
    int moveDir; // The direction that the map will move the player
};

#endif // ACTOR_H
