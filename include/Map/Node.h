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
      Actor* getActorPtr(int index); // For getting targets
      Inventory &getInventory() { return inventory; }
      std::string getName();
      void setName(std::string name) { this->name = name; }
      void setNodeLink(int dir, Node* link);
      void setEntranceDir(int dir, bool isEntrance);
      Inventory inventory;

      // Navigation
      virtual bool isWall() { return false; }
      void showNavigationInfo();

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

// Operators
std::ostream &operator<<(std::ostream &os, const Maps::Node &node);
std::istream &operator>>(std::istream &is, Maps::Node &node);

#endif
