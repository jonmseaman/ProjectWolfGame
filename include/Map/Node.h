#ifndef NODE_H
#define NODE_H
#include <list>
#include <string>
#include "Inventory.h"
#include "Dir.h"
class Actor;
namespace Maps
{
  class Node
  {
    public:
      static int nodeCount;
      Node();
      virtual ~Node();

      // Data Access
      Actor* getActorPtr(int index); // For getting targets
      Inventory &getInventory() { return inventory; }
      std::string getName();
      void setName(std::string name) { this->name = name; }
      void setNodeLink(int dir, Node* link);
      void setEntranceDir(int dir, bool isEntrance);
      Inventory inventory;

      // Navigation
      virtual bool isWall() { return false; }
      /**
       * This function is to figure out if moving an actor in a specific
       * direction is possible.
       * @pre 0 <= dir < numDirs
       * @return True if an actor could move from this int direction dir.
       */
      bool canMoveInDir(int dir);
      /**
       * Allows retrieval of entrance directions on nodes.
       * @param dir The direction being checked.
       * @pre 0 <= dir < numDirs
       * @return True if the node has an entrance in direction dir.
       */
      bool getEntranceDir(int dir);
      void showNavigationInfo();
      void showNavigationInfoForNode(int dir);

      // Use
      virtual void activate();
      void addActor(Actor *actor);
      void moveActors(); // Tries to move all actors which have a move flag
      void removeActor(int index);
      void showActors(); // Shows a list of actors

    protected:
      Node* nodeLinks[numDirs];
      /// The directions from which this node can be entered
      bool entranceDirs[numDirs];
      std::list<Actor*> actorPtrList;
      int getNumActors();
      std::string name;
    private:
  };
}

#endif
