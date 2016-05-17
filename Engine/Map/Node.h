#ifndef NODE_H
#define NODE_H
#include <Engine.h>
#include <list>
#include <string>
#include "Entity/Inventory.h"
#include "Dir.h"
#include "Savable.h"

namespace Engine {
namespace Entity {
class Actor;
}
namespace Maps {
class ENGINE_API Node : public File::Savable {
public:
  Node();
  virtual ~Node();
  SAVABLE_CLEAR;

  std::string getName() { return this->name; }
  void setName(std::string name) { this->name = name; }

  // The node's inventory. Contains items in the node.
  Engine::Entity::Inventory inventory;

#pragma region Actor
  bool containsActor(Engine::Entity::Actor* actor);
  Engine::Entity::Actor* getActorPtr(int index);
  Engine::Entity::Actor* getNextActor(Engine::Entity::Actor* actor);

  void addActor(Engine::Entity::Actor *actor);
  int getNumActors();
  void moveActors();
  void showActors(); // Shows a list of actors
#pragma endregion
#pragma region Gameplay

  virtual void activate();

#pragma endregion
#pragma region Navigation
  bool canMoveInDir(int dir);

  bool getEntranceDir(int dir);
  void setEntranceDir(int dir, bool isEntrance);

  void setNodeLink(int dir, Node* link);
  void showNavigationInfo();
  void showNavigationInfoForNode(int dir);
  // TODO: Make this return a data member bool. No virtual.
  virtual bool isWall() { return false; }
#pragma endregion

protected:
  // Actors contained in the node.
  std::list<Engine::Entity::Actor*> actorPtrs;

  Node* nodeLinks[NUM_DIRS];
  /// The directions from which this node can be entered
  bool entranceDirs[NUM_DIRS];
  std::string name;
  static int nodeCount;
};
}
}
#endif
