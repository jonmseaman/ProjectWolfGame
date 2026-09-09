module;
#include "EngineMacros.h"
#include "SavableMacros.h"

export module Engine:Actor;

import :Creature;
import :Dir;
import :Node;

export namespace Engine {
namespace Entity {

/**
 * The actor class is a creature which with behavior.
 * This should be generalized into Players, Mobs, Bosses etc
 */
class ENGINE_API Actor : public Creature {
public:
  Actor();
  ~Actor() override;
  SAVABLE;

  // Combat
  virtual void onAttack();
  // Inventory
  bool dropItem(int slotNumber); // Drops item to node inventory
  void dropAllItems(); // Drops all items in inventory to node inventory.
  // Targeting
  /**
   * Cycles through targets in the node. If there is not an actor != this in
   * the node, the target will be removed.
   */
  void cycleTarget();
  Actor* getTarget() const { return targetPtr; }
  void setTarget(Actor* actor);
  /**
   * Checks to make sure that this has a valid target.<br>
   * <b>Updates</b> targetPtr
   * @return true if target is valid
   */
  bool hasValidTarget();
  // Turns
  virtual void takeTurn(); // Allows the player to take actions. Uses turn
  virtual void endTurn(); // Default is flagging the turn as used.
  bool getIsTurnUsed() const;

  // Movement
  virtual void onMove();
  /**
   * @usage Used by node to figure out which direction the
   * actor should be moved.
   * @return The direction that the actor should move
   */
  Maps::Dir getMoveDir() const;
  void setCurrentNode(Maps::Node *node);
  // Special
  bool getIsPlayer() const;
protected:
  /**
   * The node that the actor is currently in.
   * Used for movement, targetting, awareness...
   */
  Maps::Node *currentNode = nullptr;
  Actor* targetPtr = nullptr;
  /**
   * Tries to set movement for the actor.
   * If it is possible to move in direction dir, then the turn is used.
   * @post Turn is used if it is possible to move in direction
   * @post Actor will be set to move after turns
   */
  void setMoveDir(Maps::Dir dir);
  void setIsTurnUsed(bool val = true);
  bool isPlayer = false;
private:
  bool isTurnUsed = false; // Should stop allowing actions when this is true.
  Maps::Dir moveDir = Maps::Dir::STOP; // Direction the map will move the player
};

}
}
