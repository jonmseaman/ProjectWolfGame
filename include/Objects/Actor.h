#ifndef ACTOR_H
#define ACTOR_H
#include "Dir.h"
#include "NodeData.h"
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
    friend std::ostream &operator<<(std::ostream &os, const Creature &creature);
    friend std::istream &operator>>(std::istream &is, Creature &creature);
    bool dropItem(int slotNumber); // Drops item to node inventory. slotNumber is index+1 in inventory
    void dropAllItems(); // Drops all items in inventory to node inventory.
    virtual bool onInteractedWith(); // Allows the interaction
    virtual void takeTurn(); // Allows the player to take actions. Uses turn
    virtual void onEndTurn(); // Whatever needs to be done at the end of a turn. Default is flagging the turn as used.
    virtual void onMove(); // TODO: Moving should make other creatures stop targeting you.
    int getMoveDir();
    bool getIsTurnUsed();
    bool getIsPlayer();
    void setMoveData(Maps::Node* ptrMoveData);
  protected:
    //Maps::NodeData* actorPData;
	Maps::Node *actorPData;
    // Tries to flag the actor for movement so that the map will move the
    // actor when it can
    void flagForMove( int dir );
    void flagTurnUsed();
    void flagTurnUsed(bool val);
    bool isPlayer = false;
  private:
    bool isTurnUsed; // Should stop allowing actions when this is true.
    int moveDir; // The direction that the map will move the player
};

// Operators
std::ostream &operator<<(std::ostream &os, const Creature &creature);
std::istream &operator>>(std::istream &is, Creature &creature);

#endif // ACTOR_H
