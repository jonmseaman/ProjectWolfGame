#ifndef ACTOR_H
#define ACTOR_H
#include <Engine.h>
#include "Creature.h"
#include "Map/Node.h"

using namespace Engine::Maps;

namespace Engine {
namespace Entity {
/**
 * The actor class is a creature which with behavior.
 * This should be generalized into Players, Mobs, Bosses etc
 */
class ENGINE_API Actor : public Creature {
public:
  Actor();
  virtual ~Actor();
  SAVABLE;

  // Combat
  virtual void onAttack();
  // Inventory
  bool dropItem(int slotNumber); // Drops item to node inventory. slotNumber is index+1 in inventory
  void dropAllItems(); // Drops all items in inventory to node inventory.
  // Targeting

  // Switches to next target in current node.
  void cycleTarget();
  Actor *getTarget() { return targetPtr; }
  void setTarget(Actor* actor);

  bool hasValidTarget();
  // Turns
  virtual void takeTurn(); // Allows the player to take actions. Uses turn
  virtual void endTurn(); // Whatever needs to be done at the end of a turn. Default is flagging the turn as used.
  bool getIsTurnUsed();

  // Movement
  virtual void onMove();
  int getMoveDir();
  void setCurrentNode(Node *node);
  // Special
  bool getIsPlayer();
protected:
  /**
   * The node that the actor is currently in.
   * Used for movement, targetting, awareness...
   */
  Node *currentNode;
  Actor* targetPtr;
  void setMoveDir(int dir);
  void setIsTurnUsed(bool val = true);
  bool isPlayer = false;
private:
  bool isTurnUsed; // Should stop allowing actions when this is true.
  int moveDir; // The direction that the map will move the player
};
}
}
#endif // ACTOR_H
