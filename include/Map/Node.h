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
    friend std::ostream &operator<<(std::ostream &os, const Maps::Node &node);
    friend std::istream &operator>>(std::istream &is, Maps::Node &node);
    public:
      static int nodeCount;
      Node();
      virtual ~Node();

      // Data Access
      Actor* getActorPtr( int index ); // For getting targets
      Inventory &getInventory() { return inventory; }
      std::string getName();
      void setNodeLink(int dir, bool moveInDir, Node* link);

      // Navigation
      virtual bool isWall() { return false; }
      void showNavigationInfo();

      // Use
      virtual void activate();
      void addActor(Actor *actor);
      void moveActors(); // Tries to move all actors which have a move flag
      bool removeActor(int index);
      void showActors(); // Shows a list of actors

    protected:
      Inventory inventory;
      Node* nodeLinks[numDirs];
      bool canMoveInDir[numDirs];
      std::list<Actor*> actorPtrList;
      int getNumActors();
    private:
      std::string name;
  };
}

// Operators
std::ostream &operator<<(std::ostream &os, const Maps::Node &node);
std::istream &operator>>(std::istream &is, Maps::Node &node);

#endif
