#ifndef ACTOR_H
#define ACTOR_H
#include "Creature.h"
#include "File.h"
#include "Node.h"
#include "Entity.h"


/**
 * The actor class is a creature which with behavior.
 * This should be generalized into Players, Mobs, Bosses etc
 */
class ENTITY_API Actor : public Creature
{
    // Temp stuff
  public:
    int getID() { return id; }
    void setID(int idNum) { this->id = idNum; }
    int id;
  public:
    Actor();
    virtual ~Actor();
    // Loading and Saving
    pairType toTree();
    void fromTree(const pairType& p);


    // Combat
    virtual void onAttack();
    // Inventory
    bool dropItem(int slotNumber); // Drops item to node inventory. slotNumber is index+1 in inventory
    void dropAllItems(); // Drops all items in inventory to node inventory.
    // Targeting
    /**
     * Cycles through targets in the node. If there is not an actor != this in
     * the node, the target will be removed.
     */
    void cycleTarget();
    Actor *getTarget() { return targetPtr; }
    void setTarget(Actor* actor);
    /**
     * Checks to make sure that this has a valid target.<br>
     * <b>Updates</b> targetPtr
     * @return true if target is valid
     */
    bool hasValidTarget();
    // Turns
    virtual void takeTurn(); // Allows the player to take actions. Uses turn
    virtual void endTurn(); // Whatever needs to be done at the end of a turn. Default is flagging the turn as used.
    bool getIsTurnUsed();

    // Movement
    virtual void onMove();
    /**
     * @usage Used by node to figure out which direction the
     * actor should be moved.
     * @return The direction that the actor should move
     */
    int getMoveDir();
    void setCurrentNode(Maps::Node *node);
    // Special
    bool getIsPlayer();
  protected:
    /**
     * The node that the actor is currently in.
     * Used for movement, targetting, awareness...
     */
    Maps::Node *currentNode;
    Actor* targetPtr;
    /**
     * Tries to set movement for the actor.
     * If it is possible to move in direction dir, then the turn is used.
     * @pre 0 <= dir < numDirs
     * @post Turn is used if it is possible to move in direction
     * @post Actor will be set to move after turns
     */
    void setMoveDir( int dir );
    void setIsTurnUsed(bool val = true);
    bool isPlayer = false;
  private:
    bool isTurnUsed; // Should stop allowing actions when this is true.
    int moveDir; // The direction that the map will move the player
};

#endif // ACTOR_H
